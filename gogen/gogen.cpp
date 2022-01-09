#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <math.h>
#include "common.h"
#include "mask.h"
#include "gogen.h"

using namespace std;

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

/* internal helper function which removes unprintable characters like carriage returns and newlines from strings */
void filter (char *line) {
  while (*line) {
    if (!isprint(*line))
     *line = '\0';
    line++;
  }
}

/* loads a Gogen board from a file */
char **load_board(const char *filename) {
  char **board = allocate_2D_array(5, 6);
  ifstream input(filename);
  assert(input);
  char buffer[512];
  int lines = 0;
  input.getline(buffer, 512);
  while (input && lines < HEIGHT) {
    filter(buffer);
    if (strlen(buffer) != WIDTH)
      cout << "WARNING bad input = [" << buffer << "]" << endl;
    assert(strlen(buffer) == WIDTH);
    strcpy(board[lines], buffer);
    input.getline(buffer, 512);
    lines++;
  }
  input.close();
  return board;
}

/* saves a Gogen board to a file */
bool save_board(char **board, const char *filename) {
  ofstream out(filename); 
  if (!out)
    return false;
  for (int r=0; r<HEIGHT; r++) {
    for (int c=0; c<WIDTH; c++) {
      out << board[r][c];
    }
    out << endl;
  }
  bool result = out.good();
  out.close();
  return result;
}

/* internal helper function for counting number of words in a file */
int count_words(const char *filename) {
  char word[512];
  int count = 0;
  ifstream in(filename);
  while (in >> word)
    count++;
  in.close();
  return count;
}

/* loads a word list from a file into a NULL-terminated array of char *'s */
char **load_words(const char *filename) {
  int count = count_words(filename);
  ifstream in(filename);
  assert(in);
  int n=0;
  char **buffer = new char *[count+1]; // +1 because we NULL terminate 
  char word[512];
  for (; (in >> word) && n<count; n++) {
    buffer[n] = new char[strlen(word) + 1];
    strcpy(buffer[n], word);
  }
  buffer[n] = NULL;
  in.close();
  return buffer;
}

/* prints a Gogen board in appropriate format */
void print_board(char **board) {
  for (int r=0; r<HEIGHT; r++) {
    for (int c=0; c<WIDTH; c++) {
      cout << "[" << board[r][c] << "]";
      if (c < WIDTH-1)
	cout << "--";
    }
    cout <<endl;
    if (r < HEIGHT-1) {
      cout << " | \\/ | \\/ | \\/ | \\/ |" << endl;
      cout << " | /\\ | /\\ | /\\ | /\\ |" << endl;
    }
  }
}

/* prints a NULL-terminated list of words */
void print_words(char **words) {
  for (int n=0; words[n]; n++) 
    cout << words[n] << endl;
}

/* frees up the memory allocated in load_board(...) */
void delete_board(char **board) {
  deallocate_2D_array(board, HEIGHT);
}

/* frees up the memory allocated in load_words(...) */
void delete_words(char **words) {
  int count = 0;
  for (; words[count]; count++);
  deallocate_2D_array(words, count);
}

/* add your own function definitions here */


bool get_position(char** board, 
                  char const ch, 
                  int& row, 
                  int& column) {
  row = -1;column = -1;
  for (int i = 0; i < WIDTH; ++i) {
    for (int j = 0; j < HEIGHT; ++j) {
      if (board[i][j] == ch) {
        row = i;
        column = j;
        return true;
      }
    }
  }
  return false;
}


bool valid_solution(char** board, char ** words) {
  // p_pos for previous position, c_pos for current position
  int p_pos[2], c_pos[2];
  int i = 0;
  while(words[i] != NULL) {
    for (size_t j = 0; j < strlen(words[i]); ++j) {
      // get previous and current position
      if (j == 0) {
        get_position(board, words[i][j], p_pos[0], p_pos[1]);
        get_position(board, words[i][j], c_pos[0], c_pos[1]);
      }
      else {
        p_pos[0] = c_pos[0];
        p_pos[1] = c_pos[1];
        get_position(board, words[i][j], c_pos[0], c_pos[1]);
      }
      if (abs(p_pos[0] - c_pos[0]) > 1 ||
          abs(p_pos[1] - c_pos[1]) > 1 ||
          c_pos[0] == -1 ||
          c_pos[1] == -1) {return false;}
    }
    ++i;
  }
  
  return true;
}


void update(char** board, char const ch, Mask& mask) {
  int pos[2];  
  // if ch in board, set all mask to false except for that one
  if (get_position(board, ch, pos[0], pos[1])) {
    mask.set_all(false);
    mask[pos[0]][pos[1]] = true;
    return;
  }
  // if ch not in board, flip all cell 
  // unless there is only one masked cell (1 true)
  if (mask.count() == 1) {
    mask.get_position(true, pos[0], pos[1]);
    board[pos[0]][pos[1]] = ch;
  } 
  else {
    for (int i = 0; i < WIDTH; ++i) {
      for (int j = 0; j < HEIGHT; ++j) {
        if (board[i][j] == '.') {mask[i][j] = true;}
        else {mask[i][j] = false;}
      }
    }
  }
}


void neighbourhood_intersect(Mask& one, Mask& two) {
  Mask tmp = one;
  one.intersect_with(two.neighbourhood());
  two.intersect_with(tmp.neighbourhood());
}


bool solve_board(char ** board, char ** words) {
  // initialize all masks, m_idx for mask index
  int pos[2];
  Mask mask[NUM]; int m_idx[2];
  for (int i = 0; i < NUM; ++i) {update(board, i + 'A', mask[i]);}
  // use all words
  for (size_t c_word = 0; words[c_word] != NULL; ++c_word) {
    // intersect for consecutive 2 characters of each word
    for (size_t pos = 0; pos < strlen(words[c_word])-1; ++pos) {
      m_idx[0] = words[c_word][pos] - 'A';
      m_idx[1] = words[c_word][pos+1] - 'A';
      neighbourhood_intersect(mask[m_idx[0]], mask[m_idx[1]]);
    }
  }

  // boundary condition
  for (int i = 0; i < NUM; ++i) {
    if (mask[i].count() == 0) {return false;}
  }
  // only one solution recursive condition 
  for (int i = 0; i < NUM; ++i) {
    if (has_char(board, i + 'A' )) {continue;}
    mask[i].get_position(true, pos[0], pos[1]);
    if (mask[i].count() == 1 && board[pos[0]][pos[1]] == '.') {
      board[pos[0]][pos[1]] = i + 'A';
      if (!solve_board(board, words)) {board[pos[0]][pos[1]] = '.';}
      else {break;}
    }
  }

  // more solution recursive condition,
  // guess one position row by row, col by col, starting from A
  for (int i = 0; i < NUM; ++i) {
    if (has_char(board, i +'A' )) {continue;}
    for (int row = 0; row < HEIGHT; ++row) {
      for (int col = 0; col < WIDTH; ++col) {
        if (mask[i].count() > 1 && mask[i][row][col]) {
          board[row][col] = i + 'A';
          if (!solve_board(board, words)) {board[row][col] = '.';}
          else {break;}
        }
      }
    }
  }
  for (int i = 0; i < NUM; ++i) {update(board, i + 'A', mask[i]);}
  for (int i = 0; i < NUM; ++i) {
    if (mask[i].count() != 1) {return false;}
  }
  return true;
}


bool has_char(char ** board, char ch) {
  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      if (board[i][j] == ch) {return true;}
    }
  }
  return false;
}