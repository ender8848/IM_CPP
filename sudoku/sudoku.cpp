#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include "sudoku.h"
using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in) {
    cout << "Failed!\n";
  }
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}


/* internal helper function */
void print_frame(int row) {
  if (!(row % 3)) {
    cout << "  +===========+===========+===========+\n";
  } else {
    cout << "  +---+---+---+---+---+---+---+---+---+\n";
  }
}


/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|\n";
}


/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) {
    cout << (char) ('1'+r) << "   ";
  }
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}


/* add your functions here */
bool is_complete(char const board[][LEN]) {
	for (int i = 0; i < LEN; ++i) {
		for (int j = 0; j < LEN; ++j) {
			if (!isdigit(board[i][j])) {return false;}
		}
	}
	return true;
}


bool is_valid_pos(char const * const position) {
	if (position[0] < 'A' || position[0] > 'I' ||
		position[1] < '1' || position[1] > '9') {return false;}
	return true;
}


bool is_valid_digit(char const digit) {
	if (digit < '1' || digit > '9') {return false;}
	return true;
}


bool make_move(char const * const position, char const digit, char board[][LEN]) {
	// check if position in board or digit is in range (1,9)
	if (!is_valid_pos(position) || !is_valid_digit(digit)) {return false;}
	// check if a position already has a digit
	int pos[2] = {position[0]-'A', position[1] - '1'};
	if (is_valid_digit(board[pos[0]][pos[1]])) {return false;}
	// check repetition in row
	for (int col = 0; col < LEN; ++col) {
		if (col != pos[1] && board[pos[0]][col] == digit) {return false;}
	}
	// check repetition in col
	for (int row = 0; row < LEN; ++row) {
		if (row != pos[0] && board[row][pos[1]] == digit) {return false;}
	}
	// check repetition in 3x3 small board;
	int row_start = pos[0] - pos[0]%3, col_start = pos[1] - pos[1]%3;
	for (int i = 0; i < SLEN; ++i) {
		for (int j = 0; j < SLEN; ++j) {
			if (!(row_start + i == pos[0] && col_start + j == pos[1]) &&
				board[row_start + i][col_start + j] == digit) {
					return false;
				}
		}
	}
	// put digit into a position of board
	board[pos[0]][pos[1]] = digit;
	return true;
}


bool save_board(char const * const filename, char const board[][LEN]) {
	ofstream output(filename);
	if (output.fail()) {return false;}
	for (int i = 0; i < LEN; ++i) {
		for (int j = 0; j < LEN; ++j) {
			output.put(board[i][j]);
		}
		output.put('\n');
	}
	output.close();
	return true;
}


bool solve_board(char board[][LEN]) {
	// boundary condition, return true if board is complete
	if (is_complete(board)) {
		return true;
	}
	char pos[2]; 
	for (int i = 0; i < LEN; ++i) {
		for (int j = 0; j < LEN; ++j) {
			pos[0] = i + 'A';
			pos[1] = j + '1';
			for (char digit = '1' ; digit <= '9'; ++digit) {
				if (make_move(pos, digit, board)) {
					if (!solve_board(board)) {board[i][j] = '.';}
					else {return true;}
				}
			}
			// boundary condition
			// return false if a position cannot find a valid digit
			if (board[i][j] == '.') {return false;}
		}
	}
	return false;
}
