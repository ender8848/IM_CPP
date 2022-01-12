#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
#include "laser.h"

using namespace std;

/* pre-supplied helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **array = new char *[rows];
  assert(array);
  for (int r=0; r<rows; r++) {
    array[r] = new char[columns];
    assert(array[r]);
  }
  return array;
}

/* pre-supplied helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **array, int rows) {
  for (int r=0; r<rows; r++)
    delete [] array[r];
  delete [] array;
}

/* internal helper function which gets the dimensions of a board */
bool get_board_dimensions(const char *filename, int &height, int &width) {
  char line[512];
  
  ifstream input(filename);

  height = width = 0;

  input.getline(line,512);  
  while (input) {
    if ( (int) strlen(line) > width)
      width = strlen(line);
    height++;
    input.getline(line,512);  
  }

  if (height > 0)
    return true;
  return false;
}

/* internal helper function which removes carriage returns and newlines from end of strings */
void filter (char *line) {
  while (*line) {
    if (!isprint(*line))
     *line = '\0';
    line++;
  }
}

/* pre-supplied function to load a board from a file*/
char **load_board(const char *filename, int &height, int &width) {

  bool success = get_board_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **board = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    filter(line);
    strcpy(board[r], line);
  }
  
  return board;
}

/* pre-supplied function to print a board */
void print_board(char **board, int height, int width) {
  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(4) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << board[r][c];
    cout << endl;
  }
}

/* add your own function definitions here */

bool find_laser(char ** board, int height, int width, int& row) {
  row = -1;
  if (height <= 0 ) {return false;}
  for (int i = 0; i < height; ++i) {
    if (board[i][0] == '>') {
      row = i;
      return true;
    }
  }
  return false;
}


char mirror_label(char** board, int height, int width, int row, int column) {
  // defend possible errors
  if (height <= 0 || width <= 0) {return '\0';}
  if (row >= height || column >= width) {return '\0';}

  if (board[row][column] == '\\'  ||
      board[row][column] == '/') {
    // when find a mirror, search nearby cell around and return the letter
    for (int i = -1; i <= 1; ++i) {
      for (int j = -1; j <= 1; ++j) {
        if ( (j||i) && isupper(board[row+i][column+j])) {
          return board[row+i][column+j];
        }
      }
    }
  }
  return '\0';
}


bool shoot(char** board, 
           int height, 
           int width, 
           char* message, 
           int& last_row, 
           int& last_col) {
  // 1. find starting point
  int pos = 0;
  *message = '\0';
  last_col = 0;
  if (!find_laser(board, height, width, last_row)) {return false;}
  // 2. move step by step when not in the end
  Direction direction = EAST;
  while (board[last_row][last_col] != '@') {
    if (!move_step(board, height, width, direction, last_row, last_col)) {
      return false;
    }
    char label = mirror_label(board, height, width, last_row, last_col);
    if (label != '\0') {
      message[pos++] = label;
      message[pos] = '\0';
    }
    if (board[last_row][last_col] == '@') {return true;}
  }
  return true;
}


bool move_step(char** board, 
               int height, 
               int width, 
               Direction& dir, 
               int& row, 
               int& col) {
  // 1. move one step using current direction 
  if (dir == NORTH) {--row;}
  if (dir == SOUTH) {++row;}
  if (dir == WEST) {--col;}
  if (dir == EAST) {++col;}
  // 2. check if boundary 
  if (board[row][col] == '#') {return false;}
  // 3. check if direction switch
  if (board[row][col] == '/' || board[row][col] == '\\') {
    change_direction(dir, board[row][col]);
    return true;
  }
  // 4. identify current drawing unit
  char draw;
  if (dir == WEST || dir == EAST) {draw = '-';}
  if (dir == NORTH || dir == SOUTH) {draw = '|';}
  // 5. if current poisition is space, draw, 
  // if dirrerent draw, change into +
  // if same draw or letter or +, simply return
  if (board[row][col] == ' ') {
    board[row][col] = draw;
    return true;
  }
  if ((board[row][col] == '-' || board[row][col] == '|') && 
       board[row][col] != draw){
    board[row][col] = '+';
    return true;
  }
  if (isupper(board[row][col]) ||
      board[row][col] == draw ||
      board[row][col] == '+'){
    return true;
  }
  // 6. if meet ? by default return false
  if (board[row][col] == '?'){return false;}
  return false;
}


void change_direction(Direction& dir, char change) {
  if (change == '\\') {
    switch (dir) {
      case NORTH: dir = WEST; return;
      case WEST: dir = NORTH; return;
      case SOUTH: dir = EAST; return;
      case EAST: dir = SOUTH; return;
      default: return;
    }
  }
  if (change == '/') {
    switch (dir) {
      case NORTH: dir = EAST; return;
      case EAST: dir = NORTH; return;
      case SOUTH: dir = WEST; return;
      case WEST: dir = SOUTH; return;
      default: return;
    }
  }
}


bool solve(char** board, int height, int width, char const* target) {
  char message[MAXLEN];
  int last_row, last_col;
  shoot(board, height, width, message, last_row, last_col);
  if (!strcmp(message, target)) {
    return true;
  }
  if (shoot(board, height, width, message, last_row, last_col) && 
      !strcmp(message, target)) {
    return true;
  }
  if (board[last_row][last_col] != '?') {
    return false;
  }

  // copy the board and do recursion
  char** board_ = new char*[height];
  for (int i = 0; i < height; ++i) {
    board_[i] = new char[width];
  }
  int row = last_row; int col = last_col;
  copy_board(board_, board, height, width);
  // try 3 different ways
  if (board[last_row][last_col] == '?') {
    last_row = row; last_col = col;
    board_[last_row][last_col] = '/';
    if (solve(board_, height, width, target)) {    
      copy_board(board, board_, height, width);
      for (int i = 0; i < height; ++i) {delete [] board_[i];}
      return true;
    }
    else {copy_board(board_, board, height, width);}
    last_row = row; last_col = col;
    board_[last_row][last_col] = '\\';
    if (solve(board_, height, width, target)) {    
      copy_board(board, board_, height, width);
      for (int i = 0; i < height; ++i) {delete [] board_[i] ;}
      return true;
    }
    else {copy_board(board_, board, height, width);}
    last_row = row; last_col = col;
    board_[last_row][last_col] = ' ';
    if (solve(board_, height, width, target)) {    
      copy_board(board, board_, height, width);
      for (int i = 0; i < height; ++i) {delete [] board_[i];}
      return true;
    }
    else {copy_board(board_, board, height, width);}
  }
  copy_board(board_, board, height, width);
  for (int i = 0; i < height; ++i) {delete [] board_[i];}
  
  return false;
}


void copy_board(char** destination, char** source, int height, int width) {
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      destination[i][j] = source[i][j];
    }
  }
}