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

/* searches for the first occurrence of character ch in a given board 
   in a row-by-row fashion. */
bool get_position(char** board, 
                  char const ch, int& row, int& column);

/* returns true if the given board represents a solution 
   to the Gogen puzzle with the given list of words */
bool valid_solution(char** board, char ** words);


/* updates the board and a mask for letter ch 
   according to the some rules */
void update(char** board, char const ch, Mask& mask);


/* modifies masks one and two by intersecting each 
   with the 1-neighbourhood of the other */
void neighbourhood_intersect(Mask& one, Mask& two);


/*  attempts to find a solution to a given Gogen puzzle */
bool solve_board(char ** board, char ** words);

/* helper func which checks if a board already has ch */
bool has_char(char ** board, char ch);