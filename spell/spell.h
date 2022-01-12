#pragma once
#include <string>
#include <vector>

/* you may assume a maximum word length of 512 characters*/
#define MAX_LENGTH 512

/* insert your function prototypes here */

/**
 * Q1 return number of times the target word appears in the corpus
 * @param target word to find
 * @return the time of occurence
 */
int frequency(std::string const& target);

/**
 * helper funcs for Q1, retrieved from rhyme_scheme exam
 * get word at a certain position
 */
bool get_word(const char *input_line, int word_number, char *output_word);

/** 
 * Q2 calculate edit distance between input character strings a and b 
 * @param a const ref string a
 * @param b const ref string b
 * @return distance between them
 */
int edit_distance(char const * const a, char const * const b);

/* helper func for q2 */
void update(char const * const a, char const * const b, int i, int j, std::vector<std::vector<int>>& dp);
void print_data(std::vector<std::vector<int>> const& data);


/**
 * Q3 suggests a spell checked variant of a word
 * @param word input word
 * @param fixed output word if need change
 * @return true if correction is needed false otherwise
 */
bool spell_correct(char const * const word, char* fixed);