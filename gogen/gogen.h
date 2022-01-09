/* finished in 12/31/2021 using 148min */

/*  Pre-supplied functions for loading and printing board and word list */

char **load_board(const char *filename);
bool save_board(char **board, const char *filename);
void print_board(char **board);

char **load_words(const char *filename);
void print_words(char **words);

void delete_board(char **board);
void delete_words(char **words);

/* -----------8<-------------8<------------8<--------------8<------------ */

/* add your function prototypes here */

/**
 * Q1 searches for the first occurrence of character ch
 * in a given board in a row-by-row fashion. 
 * @param board a 5x5 char board
 * @param ch char to find
 * @param row output row of ch
 * @param column output row of ch
 * @return true if can find, false otherwise
 */
bool get_position(char** board, 
                  char const ch, 
                  int& row, 
                  int& column);

/**
 * Q2 returns true if the given board represents a solution 
 * to the Gogen puzzle with the given list of words
 * @param board a 5x5 char board
 * @param words words used to check if a board is a solution
 * @return true if is a solution, false otherwise
 */
bool valid_solution(char** board, char ** words);


/**
 * Q3a updates the board and a mask for letter ch 
 * according to the some rules
 * @param board a 5x5 char board
 * @param ch the char mask array represents
 * @param mask mask array used to calculate
 */
void update(char** board, char const ch, Mask& mask);


/**
 * Q3b modifies masks one and two by intersecting each 
 * with the 1-neighbourhood of the other
 * @param one first mask array to intersect
 * @param two second mask array to intersect
 */
void neighbourhood_intersect(Mask& one, Mask& two);


/* attempts to find a solution to a given Gogen puzzle */
bool solve_board(char ** board, char ** words);

/* helper func for q4 - checksif a board already has ch */
bool has_char(char ** board, char ch);