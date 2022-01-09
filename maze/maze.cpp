#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <math.h>
#include "maze.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* helper function for internal use only which gets the dimensions of a maze */
bool get_maze_dimensions(const char *filename, int &height, int &width) {
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

/* pre-supplied function to load a maze from a file*/
char **load_maze(const char *filename, int &height, int &width) {

  bool success = get_maze_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
  }
  
  return m;
}

/* pre-supplied function to print a maze */
void print_maze(char **m, int height, int width) {
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
      cout << m[r][c];
    cout << endl;
  }
}


/* student functions */
/** finds the coordinates of marker char in a maze
 * @param ch char to be found
 * @param maze 2-d maze char array
 * @param height height of maze
 * @param width width of maze
 * @param row output row of char
 * @param column output column of char
 * @return true if found, false otherwise
 */
bool find_marker(char ch, 
                 char ** maze, 
                 int height, 
                 int width, 
                 int& row, 
                 int& column) {
  row = -1; column = -1;
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      if (ch == maze[i][j]) {
        row = i;
        column = j;
        return true;
      }
    }
  }
  return false;
}


bool valid_move(char type, 
                char** maze, 
                int height, 
                int width, 
                int& row, 
                int& col) {
  // valid move type check
  switch(type) {
    case 'N': --row; break;
    case 'S': ++row; break;
    case 'W': --col; break;
    case 'E': ++col; break;
    default : return false;
  }
  // out of boundary check
  if (row < 0 || row >= height || col < 0 || col >= width) {
    return false;
  }
  // barrier check, defend all characters except space, X and M
  switch(maze[row][col]) {
    case ' ': break;
    case 'X': break;
    case 'M': break;
    default : return false;
  }
  return true;
}


bool valid_solution(char const * const path, 
                    char ** maze, 
                    int height, 
                    int width) {
  int row = -1, col = -1;
  if (strlen(path) == 0) {return false;}
  if (!find_marker('>', maze, height, width, row, col)) {return false;}
  // ensure every step is valid
  for (size_t i = 0; i < strlen(path); ++i) {
    if (valid_move(path[i], maze, height, width, row, col)) {continue;}
    else {return false;}
  }
  // ensure last position is entrance
  if (maze[row][col] != 'X') {return false;}
  return true;
}


bool is_dead(char** maze, int height, int width, int row, int col, char target) {
  // check nearby 3x3 to see if there is any space or target position
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      if (abs(i) - abs(j) != 0 && // ensure only NSWE move
          row + i >= 0 && row + j < height && 
          col + i >= 0 && col + j < width  &&
          (maze[row+i][col+j] == ' ' || 
          maze[row+i][col+j] == target)) {
            return false;
      }
    }
  }
  return true;
}


bool find_path_(char** maze, int height, int width, int row, int col, char end) {
  // boundary conditions
  if (maze[row][col] == end) {
    maze[row][col] = MASK;
    return true;
  }
  if (is_dead(maze, height, width, row, col, end)) {return false;}

  maze[row][col] = MASK;
  // Try all 4 directions 
  // 1. try north
  if (valid_move('N', maze, height, width, row, col) && 
      find_path_(maze, height, width, row, col, end)) {return true;}
  else {++row;}
  // 2. try south
  if (valid_move('S', maze, height, width, row, col) && 
      find_path_(maze, height, width, row, col, end)) {return true;}
  else {--row;}
  // 3. try east
  if (valid_move('E', maze, height, width, row, col) && 
      find_path_(maze, height, width, row, col, end)) {return true;}
  else {--col;}
  // 4. try west
  if (valid_move('W', maze, height, width, row, col) && 
      find_path_(maze, height, width, row, col, end)) {return true;}
  else {++col;}
  // if all the above failed, make the position space and return false
  maze[row][col] = ' ';
  return false;
}


void generate_path(char** maze, 
                   std::string& path, 
                   int height, 
                   int width, 
                   int row, 
                   int col) {
  // check if 3x3 block has MASK
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      if (abs(i) - abs(j) != 0 && // ensure NSEW mvoe
          row + i >= 0 && row + j < height &&
          col + i >= 0 && col + j < width  &&
          maze[row+i][col+j] == MASK) {
        maze[row+i][col+j] = SOL;
        // north
        if (i == -1) {
          path.push_back('N');
          generate_path(maze, path, height, width, row-1, col);
        }
        // east
        if (j == 1) {
          path.push_back('E');
          generate_path(maze, path, height, width, row, col+1);
        }
        // south
        if (i == 1) {
          path.push_back('S');
          generate_path(maze, path, height, width, row+1, col);
        }
        // west
        if (j == -1) {
          path.push_back('W');
          generate_path(maze, path, height, width, row, col-1);
        }
      }
    }
  }
  maze[row][col] = SOL;
  return;
}


std::string find_path(char** maze, int height, int width, char start, char end) {
  int row, col;
  if (!find_marker(start, maze, height, width, row, col)) {return "no solution";}
  if (!find_path_(maze, height, width, row, col, end)) {return "no solution";}
  maze[row][col] = SOL;
  std::string path;
  generate_path(maze, path, height, width, row, col);
  return path;
}