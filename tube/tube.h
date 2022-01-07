/* finished in 1/7/2022 using 105min */

#include <string>

enum Direction {N, S, W, E, NE, NW, SE, SW, INVALID_DIRECTION};

/* error codes for Question 3 */
#define ERROR_START_STATION_INVALID -1 
#define ERROR_ROUTE_ENDPOINT_IS_NOT_STATION -2
#define ERROR_LINE_HOPPING_BETWEEN_STATIONS -3
#define ERROR_BACKTRACKING_BETWEEN_STATIONS -4
#define ERROR_INVALID_DIRECTION -5
#define ERROR_OFF_TRACK -6
#define ERROR_OUT_OF_BOUNDS -7

/* pre-supplied function to load a tube map from a file*/
char **load_map(const char *filename, int &height, int &width);

/* pre-supplied function to print the tube map */
void print_map(char **m, int height, int width);

/* pre-supplied helper function to describe errors for Question 3 */
const char *error_description(int code);

/* presupplied helper function for converting string to Direction enum */
Direction string_to_direction(const char *token);


/* add your functions here */

/**
 * Q1 find the position of target in a map
 * @param map 2-d char array representing tube map
 * @param height row num of map
 * @param width col num of map
 * @param target char to be Found
 * @param r row position of target, set to -1 if not found
 * @param c col position of target, set to -1 if not found
 * @return true if found, false otherwise
 */
bool get_symbol_position(char** map, 
                         int height, 
                         int width, 
                         char target, 
                         int& r, 
                         int& c);


/**
 * Q2 get symbol for station or line
 * @param name a const string name of station of line
 * @return the symbol representing the station or line
 */
char get_symbol_for_station_or_line(std::string const& name);


/* some helper funcs for Q3, name indicates their usage */
bool valid_move(std::string const& move);
bool valid_route(char const * const route);
void make_move(std::string const& move, int& row, int& col);
bool has_backtrace(char const * const route);
void find_destination(char symbol, char* destination);


/**
 * Q3 determines if the route is valid according to some rules
 * @param map 2-d char array representing tube map
 * @param height row num of map
 * @param width col num of map
 * @param start starting position
 * @param route a string route, should be made from direction types
 * @param destination stores the destination station
 * @return number of line changes if valid condition, erro value otherwise
 */
int validate_route(char** map, 
                    int height, 
                    int width, 
                    std::string const& start, 
                    char* route, 
                    char* destination);