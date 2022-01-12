#pragma once
#include <fstream>
#include <vector>
#include <string>

int const MAX_LENGTH = 512;

/*  This pre-supplied function looks up a given word in the dictionary
    of approved words. It is assumed that the input word is in uppercase.
    The function returns true if the word is in the dictionary.
    Otherwise returns false. */

bool dictionary_search(const char *word);

/* add your function prototypes here */

/**
 * Q1, check if from current word to next word is a valid step
 * @param current_word, current word const string
 * @param next_word, next word const string
 * @return true if valid, false otherwise
 */
bool valid_step(char const * current_word, 
                char const * next_word);

/**
 * Q2, writes a given chain to an output stream
 * @param chain a cstring array end with NULL
 * @param out output stream
 * @return true if out is good, false otherwise
 */
bool display_chain(char const ** chain, ostream& out);

/**
 * Q3, check if a chain is a valid
 * @param chain a cstring array end with NULL
 * @return true is valid, false otherwise
 */
bool valid_chain(char const ** chain);

/**
 * Q4 
 * find a valid chain beginning with start word 
 * and ending with target word in up to max steps.
 * @param start_word start word const string
 * @param target_word target_word to find 
 * @param answer_chain the final answer
 * @param max_steps max steps can use 
 */
bool find_chain(char const * const start_word, 
                char const * const target_word, 
                const char** answer_chain, 
                int max_steps);

/* helper func for Q4, a recursive function */
bool find_chain_(std::string const& start,
                 std::string const& target, 
                 std::vector<std::string>& solution, 
                 std::vector<std::string>& best_solution,
                 std::vector<std::string> const& dict,
                 int max_len);