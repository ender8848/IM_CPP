#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <algorithm>
#include <set>

using namespace std;

#include "tube.h"

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* internal helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* internal helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* internal helper function which gets the dimensions of a map */
bool get_map_dimensions(const char *filename, int &height, int &width) {
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

/* pre-supplied function to load a tube map from a file*/
char **load_map(const char *filename, int &height, int &width) {

  bool success = get_map_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];
  char space[] = " ";

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
    while ( (int) strlen(m[r]) < width )
      strcat(m[r], space);
  }
  
  return m;
}

/* pre-supplied function to print the tube map */
void print_map(char **m, int height, int width) {
  cout << setw(2) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(2) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(2) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << m[r][c];
    cout << endl;
  }
}

/* pre-supplied helper function to report the errors encountered in Question 3 */
const char *error_description(int code) {
  switch(code) {
  case ERROR_START_STATION_INVALID: 
    return "Start station invalid";
  case ERROR_ROUTE_ENDPOINT_IS_NOT_STATION:
    return "Route endpoint is not a station";
  case ERROR_LINE_HOPPING_BETWEEN_STATIONS:
    return "Line hopping between stations not possible";
  case ERROR_BACKTRACKING_BETWEEN_STATIONS:
    return "Backtracking along line between stations not possible";
  case ERROR_INVALID_DIRECTION:
    return "Invalid direction";
  case ERROR_OFF_TRACK:
    return "Route goes off track";
  case ERROR_OUT_OF_BOUNDS:
    return "Route goes off map";
  }
  return "Unknown error";
}

/* presupplied helper function for converting string to direction enum */
Direction string_to_direction(const char *token) {
  const char *strings[] = {"N", "S", "W", "E", "NE", "NW", "SE", "SW"};
  for (int n=0; n<8; n++) {
    if (!strcmp(token, strings[n])) 
      return (Direction) n;
  }
  return INVALID_DIRECTION;
}


/* add your functions here */
bool get_symbol_position(char** map, 
                         int height, 
                         int width, 
                         char target, 
                         int& r, 
                         int& c) {
  r = -1; c = -1;
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      if (map[i][j] == target) {
        r = i; c = j;
        return true;
      }
    }
  }
  return false;
}


char get_symbol_for_station_or_line(string const& name) {
  // try line first
  string str = ""; char symbol;
  ifstream input("lines.txt"); 
  while (getline(input, str, '\n')) {
    if (str.length() < 2) {continue;}
    symbol = str[0];
    str = str.substr(2);
    if (str == name) {
      input.close();
      return symbol;
    }
  }
  input.close();
  // try stations
  input.open("stations.txt");
  while (getline(input, str, '\n')) {
    if (str.length() < 2) {continue;}
    symbol = str[0];
    str = str.substr(2);
    if (str == name) {
      input.close();
      return symbol;
    }
  }
  input.close();
  return ' ';
}


bool valid_move(std::string const& move) {
  if (move == "N") {return true;}
  if (move == "S") {return true;}
  if (move == "W") {return true;}
  if (move == "E") {return true;}
  if (move == "NE") {return true;}
  if (move == "NW") {return true;}
  if (move == "SE") {return true;}
  if (move == "SW") {return true;}
  return false;
}


bool valid_route(char const * const route) {
  string route_(route);
  string move = "";
  for (auto it = route_.begin(); it != route_.end()+1; ++it) {
    if (*it == ',' || it == route_.end() ) {
      if (!valid_move(move)) {return false;}
      move = "";
    }
    else {move += *it;}
  }
  return true;
}


void make_move(string const& move, int& row, int& col) {
  if (count(move.begin(), move.end(), 'N')) {--row;}
  if (count(move.begin(), move.end(), 'S')) {++row;}
  if (count(move.begin(), move.end(), 'W')) {--col;}
  if (count(move.begin(), move.end(), 'E')) {++col;}
}


bool has_backtrace(char const * const route) {
  // get 2 adjacent move, if they result in both col and row 0 -> has back trace
  string route_(route);
  string move = "", previous_move = move;
  for (auto it = route_.begin(); it != route_.end()+1; ++it) {
    if (*it == ',' || it == route_.end()) {
      int row = 0, col = 0;
      if (move != "" && previous_move != "") {
        make_move(move, row, col);
        make_move(previous_move, row, col);
        if (row == 0 && col == 0) {return true;}
      }
      previous_move = move;
      move = "";
    }
    else {move += *it;}
  }
  return false;
}


void find_destination(char symbol, char* destination) {
  string str;
  ifstream input("stations.txt");
  while (getline(input, str, '\n')) {
    if (str.length() < 2) {continue;}
    if (str[0] == symbol) {
      strcpy(destination, str.substr(2).c_str());
      input.close();
      return;
    }
  }
  input.close();
}


int validate_route(char** map, 
                    int height, 
                    int width, 
                    std::string const& start, 
                    char* route, 
                    char* destination) {
  // use a set to store passed lines
  set<char> lines;
  // check if start station is valid
  char symbol = get_symbol_for_station_or_line(start);
  if (symbol == ' ') {return ERROR_START_STATION_INVALID;}
  // check if route is valid
  if (!valid_route(route)) {return ERROR_INVALID_DIRECTION;}
  // check if back_trace exist;
  if (has_backtrace(route)) {return ERROR_BACKTRACKING_BETWEEN_STATIONS;}
  // get the current position, store in row and col first
  string route_(route);
  string move = "";
  int row, col;
  get_symbol_position(map, height, width, symbol, row, col);
  // 3make move, store both current symbol and previous-step symbol
  char pos = map[row][col], pre_pos = pos;
  for (auto it = route_.begin(); it != route_.end() + 1; ++it) {
    if (*it == ',' || it == route_.end()) {
      pre_pos = pos;
      make_move(move, row, col);
      // out-of-bound check
      if (row < 0 || row >= height || col < 0 || col >= width) {
        return ERROR_OUT_OF_BOUNDS;
      }
      pos = map[row][col];
      if (!isalnum(pos)) {lines.insert(pos);}
      // not-in-line check
      if (pos == ' ') {return ERROR_OFF_TRACK;}
      if (pre_pos != pos && !isalnum(pos) && !isalnum(pre_pos)) {
        return ERROR_LINE_HOPPING_BETWEEN_STATIONS;
      }
      move = "";
    }
    else {move += *it;}
  }
  // end point should be a station
  if (!isalnum(map[row][col])) {return ERROR_ROUTE_ENDPOINT_IS_NOT_STATION;}
  find_destination(pos, destination);
  return lines.size() - 1;
}