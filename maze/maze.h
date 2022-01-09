char const MASK = '.';
// sol stands for solution`
char const SOL = '#';

#include <string>
/* You are pre-supplied with the functions below. Add your own 
   function prototypes to the end of this file. */

/* helper functions to allocate and deallocate dynamic 2D arrays */
char **allocate_2D_array(int rows, int columns);
void deallocate_2D_array(char **m, int rows);

/* pre-supplied function to load a maze from a file */
char **load_maze(const char *filename, int &height, int &width);

/* pre-supplied function to print a maze */
void print_maze(char **m, int height, int width);


/* student functions */

/**
 * Q1 loop over a maze and find a marker's position
 * @param ch the character to be find
 * @param maze 2-D char array representing a maze 
 * @param height the height of a maze
 * @param width the width of a maze
 * @param row row of the char, if not found, set as -1
 * @param column column of the char, if not found, set as -1
 * @return true if ch can be found, false otherwise
 */ 
bool find_marker(char ch, 
                 char ** maze, 
                 int height, 
                 int width, 
                 int& row, 
                 int& column);

/**
 * helper func for Q2
 * check if a move is valid, however, it makes the move anyway.
 * @param type one of 'N' 'S' 'E' 'W'
 * @param maze 2-D char array representing a maze 
 * @param height the height of a maze
 * @param width the width of a maze
 * @param row row of the char
 * @param col column of the char
 * @return true if a move is valid, false otherwise
 */
bool valid_move(char type, 
                char** maze, 
                int height, 
                int width, 
                int& row, 
                int& col);

/**
 * Q2 check if a solution to a maze is valid using check_move func
 * @param path a string of maze solution
 * @param maze 2-D char array representing a maze 
 * @param height the height of a maze
 * @param width the width of a maze
 * @return true if a solution is valid, false otherwise
 */
bool valid_solution(char const * const path, 
                    char ** maze, 
                    int height, 
                    int width);

/**
 * helper func for Q3, check if a position is dead end
 * @param maze 2-D char array representing a maze 
 * @param height the height of a maze
 * @param width the width of a maze
 * @param row row of the char
 * @param col column of the char
 * @param target the target to be found, either 'X' or 'U'
 * @return true if dead end. false otherwise
 */
bool is_dead(char** maze, int height, int width, int row, int col, char target);

/**
 * helper func for Q3, recursively search the path, will set path to 1
 * @param 
 * @param maze 2-D char array representing a maze 
 * @param height the height of a maze
 * @param width the width of a maze
 * @param row row of the char
 * @param col column of the char
 * @param end either 'X' or 'U' 
 */
bool find_path_(char** maze, int height, int width, int row, int col, char end);

/** 
 * helper func for Q3, generate solution string according to the maze
 * @param maze 2-D char array representing a maze 
 * @param path the solution string of a maze
 * @param height the height of a maze
 * @param width the width of a maze
 * @param row row of the char
 * @param col column of the char
 */
void generate_path(char** maze, 
                   std::string& path, 
                   int height, 
                   int width, 
                   int row, 
                   int col);

/**
 * Q3, use the helper funcs to generate solution string
 * @param maze 2-D char array representing a maze 
 * @param height the height of a maze
 * @param width the width of a maze
 * @param start starting char, should be '>'
 * @param end ending char, should be 'X' or 'U'
 * @return solution string
 */
std::string find_path(char** maze, int height, int width, char start, char end);