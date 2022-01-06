#pragma once
#include <string>

const int SCENE_HEIGHT=24, SCENE_WIDTH=72;
size_t const BOATSIZE = 2;
size_t const BANKSIZE = 3;
size_t const HEIGHT = 6;
size_t const DIS = 3;



enum Status {VALID_GOAL_STATE=2, VALID_NONGOAL_STATE=1,ERROR_INVALID_CANNIBAL_COUNT=-1, ERROR_INVALID_MISSIONARY_COUNT=-2, ERROR_INVALID_MOVE=-3, ERROR_MISSIONARIES_EATEN=-4, ERROR_INPUT_STREAM_ERROR=-5, ERROR_BONUS_NO_SOLUTION=-6};

/* pre-supplied helper fucntions */
/* internal helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns);

/* internal helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows);

/* pre-supplied function which creates an empty ASCII-art scene */
char **create_scene();

/* pre-supplied function which frees up memory allocated for an ASCII-art scene */
void destroy_scene(char **scene);

/* pre-supplied function which displays an ASCII-art scene */
void print_scene(char **scene);

/* helper function which removes carriage returns and newlines from strings */
void filter(char *line);

/* pre-supplied function which inserts an ASCII-art drawing stored in a file
   into a given ASCII-art scene starting at coordinates (row,col)  */
bool add_to_scene(char **scene, int row, int col, const char *filename);

/* pre-supplied helper function to report the status codes encountered in Question 3 */
const char *status_description(int code);




/* insert your functions here */
/**
 * helper func for q1, draw person on boat according to 
 * @param scene a 2-d char array of art scene
 * @param row drawing row 
 * @param clo drawing col
 * @param boat string representing people in a boat
 * */
void draw_person_on_boat(char** scene, size_t row, size_t col, std::string const& boat);

/**
 * Q1 make the river scene according to left and boat people
 * @param left string representing left-side people
 * @param boat string representing boat people
 * @return scene pointer 
 */
char** make_river_scene(std::string const& left, std::string const& boat);

/**
 * helper func for Q2, check if a move is valid 
 * @param left string representing left-side people
 * @param targets string representing boat people
 * @param status, result containing the status of a move if invalid
 * @return true if valid move, false otherwise
 */
bool valid_move(std::string left, std::string const& targets, Status& status);

/**
 *  Q2, perform crossing and return status
 * @param left string representing left-side people
 * @param targets string representing boat people
 * @return status after a crossing
 */
Status perform_crossing(char* left, std::string const& targets);

/**
 * Q3 and interactive game
 * @return status after a game
 */
Status play_game();