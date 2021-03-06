#include <iostream>
#include <fstream>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "minesweeper.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load mine positions from a file */
void load_board(const char *filename, char board[9][9]) {

  cout << "Loading board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || buffer[n] == '*' || buffer[n] == ' ' || buffer[n] == '?' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}

/* internal helper function */
void print_row(const char *data, int row) {
  cout << (char) ('A' + row) << "|";
  for (int i=0; i<9; i++) 
    cout << ( (data[i]=='.') ? ' ' : data[i]);
  cout << "|" << endl;
}

/* pre-supplied function to display a minesweeper board */
void display_board(const char board[9][9]) {
  cout << "  ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r);
  cout <<  endl;
  cout << " +---------+" << endl;
  for (int r=0; r<9; r++) 
    print_row(board[r],r);
  cout << " +---------+" << endl;
}

/* pre-supplied function to initialise playing board */ 
void initialise_board(char board[9][9]) {
  for (int r=0; r<9; r++)
    for (int c=0; c<9; c++)
      board[r][c] = '?';
}

/* add your functions here */
bool is_complete(char const mines[][LEN], char const revealed[][LEN]) {
    for (int i = 0; i < LEN; ++i) {
        for (int j = 0; j < LEN; ++j) {
            if ((mines[i][j] == '*' && revealed[i][j] != '*') ||
                (mines[i][j] != '*' && revealed[i][j] == '*')) {return false;}
        }
    }
    return true;
}


int count_mines(char const * const  position, char const mines[][LEN]) {
    int count = 0, pos[2];
    pos[0] = position[0] - 'A';
    pos[1] = position[1] - '1';
    // i, j for displacement(-1,0,1) in row and col
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (pos[0] + i >= 0 && pos[0] + i < LEN &&
                pos[1] + j >= 0 && pos[1] + j < LEN &&
                (i || j) && 
                mines[pos[0] + i][pos[1] + j] == '*') {++count;}
        }
    }
    return count;
}


int valid_move (char const * const  position) {
    size_t len = strlen(position);
    if (len <2 || len > 3) {return -1;}
    if (position[0] < 'A' || position[0] > 'I' ||
        position[1] < '1' || position[1] > '9') {return -1;}
    if (len == 2) {return 0;}
    else {
        if (position[2] != '*') {return -1;}
    }
    return 1;
}


MoveResult make_move(char const * const  position, char const mines[][LEN], char revealed[][LEN]) {
    bool flag = false;
    // MoveResult result;
    if (valid_move(position) == -1) {return INVALID_MOVE;}
    else if (valid_move(position) == 1) {flag = true;}
    else {}

    if (revealed[position[0] - 'A'][position[1] - '1'] != '?') {return REDUNDANT_MOVE;}
    // flag is considered first coz it does not recursive move;
    if (flag) {
        revealed[position[0] - 'A'][position[1] - '1'] = '*';
        return VALID_MOVE;
    }
    // deal with uncover situation, need to consider recursion
    if (mines[position[0] - 'A'][position[1] - '1'] == '*') {return BLOWN_UP;}
    // if empty, mark empty and do WASD move recursively
    if (count_mines(position, mines)) {
        revealed[position[0] - 'A'][position[1] - '1'] = count_mines(position, mines) + '0';
    }
    else {
        // if there is no mine around, do make_move to 4 directions recursively
        revealed[position[0] - 'A'][position[1] - '1'] = ' ';
        char new_pos[strlen(position) + 1];
        strcpy(new_pos, position);
        ++new_pos[0];
        if (revealed[position[0] - 'A'][position[1] - '1'] != '?') {make_move(new_pos, mines, revealed);}
        ++new_pos[1];
        if (revealed[position[0] - 'A'][position[1] - '1'] != '?') {make_move(new_pos, mines, revealed);}
        --new_pos[0];
        if (revealed[position[0] - 'A'][position[1] - '1'] != '?') {make_move(new_pos, mines, revealed);}
        --new_pos[0];
        if (revealed[position[0] - 'A'][position[1] - '1'] != '?') {make_move(new_pos, mines, revealed);}
        --new_pos[1];
        if (revealed[position[0] - 'A'][position[1] - '1'] != '?') {make_move(new_pos, mines, revealed);}
        --new_pos[1];
        if (revealed[position[0] - 'A'][position[1] - '1'] != '?') {make_move(new_pos, mines, revealed);}
        ++new_pos[0];
        if (revealed[position[0] - 'A'][position[1] - '1'] != '?') {make_move(new_pos, mines, revealed);}
        ++new_pos[0];
        if (revealed[position[0] - 'A'][position[1] - '1'] != '?') {make_move(new_pos, mines, revealed);}
    }
    if (is_complete(mines, revealed)) {return SOLVED_BOARD;}
    return VALID_MOVE;
}


int flag_num_around(char const * const  position, char const revealed[][LEN]) {
    int count = 0, pos[2];
    pos[0] = position[0] - 'A';
    pos[1] = position[1] - '1';
    // i, j for displacement(-1,0,1) in row and col
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (pos[0] + i >= 0 && pos[0] + i < LEN &&
                pos[1] + j >= 0 && pos[1] + j < LEN &&
                (i || j) && 
                revealed[pos[0] + i][pos[1] + j] == '*') {++count;}
        }
    }
    return count;
}


int uncovered_num_around(char const * const  position, char const revealed[][LEN]) {
    int count = 0, pos[2];
    pos[0] = position[0] - 'A';
    pos[1] = position[1] - '1';
    // i, j for displacement(-1,0,1) in row and col
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (pos[0] + i >= 0 && pos[0] + i < LEN &&
                pos[1] + j >= 0 && pos[1] + j < LEN &&
                (i || j) && 
                revealed[pos[0] + i][pos[1] + j] == '?') {++count;}
        }
    }
    return count;
}



bool find_safe_move(char const revealed[][LEN], char * move) {
    int move_pos = 0;
    move[0] = '\0';
    char pos[3]; 
    pos[2] = '\0';

    for (int row = 0; row < LEN; ++row) {
        for (int col = 0; col < LEN; ++col) {
            // for all cell around a position
            // firstly check its surrounding 3x3 blocks
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    if (row + i >= 0 && row + i < LEN &&
                        col + j >= 0 && col + j < LEN &&
                        (i || j)) {
                        pos[0] = 'A' + row + i;
                        pos[1] = '1' + col + j;
                        // make sure uncovered
                        if (revealed[row][col] == '?') {
                            // safe uncover
                            // if (revealed[row+i][col+j] == ' ') {
                            //     move[move_pos++] = row + 'A';
                            //     move[move_pos++] = col + '1';
                            //     move[move_pos] = '\0';
                            // }
                            // safe uncover
                            if (revealed[row+i][col+j] >= '1' && 
                                revealed[row+i][col+j] <= '8' && 
                                flag_num_around(pos, revealed) == revealed[row+i][col+j]-'0') {
                                move[move_pos++] = row + 'A';
                                move[move_pos++] = col + '1';
                                move[move_pos] = '\0';
                                return true;
                            }
                            // safe flag
                            if (revealed[row+i][col+j] >= '1' && 
                                revealed[row+i][col+j] <= '8' && 
                                uncovered_num_around(pos, revealed) + flag_num_around(pos, revealed) == revealed[row+i][col+j] - '0') {
                                move[move_pos++] = row + 'A';
                                move[move_pos++] = col + '1';
                                move[move_pos++] = '*';
                                move[move_pos] = '\0';
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}


void solve_board(char const mines[][LEN], 
                 char revealed[][LEN], 
                 char* moves) {
    
    int pos = 6;
    strcpy(moves, "F1 ");
    make_move("F1", mines, revealed);
    strcpy(moves+3, "F9 ");
    make_move("F9", mines, revealed);
    char moves_[512];
    display_board(revealed);
    while (find_safe_move(revealed, moves_)) {
        // cout << moves_ << endl;
        make_move(moves_, mines, revealed);
        // display_board(revealed);
    }
    if(is_complete(mines, revealed)) {return;}
    else {
        for (int i = 0; i < LEN; ++i) {
            for (int j = 0; j < LEN; ++j) {
                if (revealed[i][j] == '?') {
                    moves[pos++] = i + 'A';
                    moves[pos++] = j + '1';
                    moves[pos++] = ' ';
                    moves[pos] = '\0';
                }
            }
        }
    }
}