enum MoveResult { INVALID_MOVE=-3, REDUNDANT_MOVE=-2, BLOWN_UP=-1, SOLVED_BOARD=1, VALID_MOVE=0 };

int const LEN = 9;

void load_board(const char *filename, char board[9][9]);
void display_board(const char board[9][9]);
void initialise_board(char board[9][9]);


/**
 * check if a playing board is same as real mines board,
 * @param mines, 9X9 real mine board
 * @param revealed, 9X9 player board
 * @return true if same, false otherwise
 */
bool is_complete(char const mines[][LEN], char const revealed[][LEN]);


/**
 * count number of mines around a particular square
 * @param position, a 2-len square position string
 * @param mines, 9X9 real mine board
 * @return number of mines around position
 */
int count_mines(char const * const  position, char const mines[][LEN]);


/**
 * check if the row and column coordinates are not valid or 
 * if the third character is present, but is not a ’*’.
 * @param position, a 2-len square position string
 * @return move type -1 if not valid move, 0 if uncover, 1 if flag
 */
int valid_move(char const * const  position);


/**
 * make a move, either flagged or uncover recursively
 * @param position, a 2-len square position string
 * @param mines, 9X9 real mine board
 * @param revealed, 9X9 player board
 * @return the MoveResult after a move
 */
MoveResult make_move(char const * const  position, char const mines[][LEN], char revealed[][LEN]);


/* helper func for Q4, find flag number around a cell */
int flag_num_around(char const * const  position, char const revealed[][LEN]);

/* helper func for Q4, find uncovered number around a cell */
int uncovered_num_around(char const * const  position, char const revealed[][LEN]);



/**
 * determines if a risk-free move is available in current playing board revealed.
 * @param revealed, 9X9 player board
 * @move, output string containing a safe move 
 * @return, true if a safe move can be found and false otherwise
 */
bool find_safe_move(char const revealed[][LEN], char * move);


/* bonus challenge
  works out the set of risky moves required to solve a minesweeper puzzle 
  outputs a string containing these via output parameter moves */
void solve_board(char const mines[][LEN], 
                 char revealed[][LEN], 
                 char* moves);