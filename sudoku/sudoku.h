/* finished in 1/2/2022 using 90min */

#ifndef SUDOKU_H
#define SUDOKU_H

// len for board len and slen for small board len
int const LEN = 9;
int const SLEN = 3;

/* pre-defined fucntions*/
/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]);
/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]);
/* internal helper function */
void print_frame(int row);

/* internal helper function */
void print_row(const char* data, int row);

/* add your functions here */

/* Q1: check if a sudoku is complete 
* @param board, 9x9 sudoku board
* @return true if complete, false otherwise
*/
bool is_complete(char const board[][LEN]);

/* helper func for Q2 
* @param position, sudoku position such as "A3"
* @return true if position is in range A1 - I9
*/
bool is_valid_pos(char const * const position);

/* helper func for Q2 
* @param digit, a char of digit
* @return true if digit is in range 1 to 9, false otherwise
*/
bool is_valid_digit(char const digit);

/* Q2: attempts to place a digit onto a Sudoku board at a given position. 
* @param position, sudoku position such as "A3"
* @param digit, a char of digit
* @param board, 9x9 sudoku board
* @return true if succeceded, also modifies the board, false otherwise and leave board unchanged */
bool make_move(char const * const position, char const digit, char board[][LEN]);

/* Q3: outputs the two-dimensional character array
* @param filename, filename in which board will be stored
* @param board, 9x9 sudoku board
* @return true if saved successfully, false otherwise */
bool save_board(char const * const filename, char const board[][LEN]);

/* Q4: attempts to solve the Sudoku puzzle
* @param board, 9x9 sudoku board
* @return true if a solution can be found, false otherwise */
bool solve_board(char board[][LEN]);


#endif
