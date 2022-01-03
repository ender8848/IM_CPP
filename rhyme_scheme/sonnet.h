/* finished in 1/3/2022 again using 90min*/
#pragma once
#include <string>

// RESET is a constant used by function rhyming_letter(...)
#define RESET NULL

/* get_word(...) retrieves a word from the input string input_line
   based on its word number. If the word number is valid, the function
   places an uppercase version of the word in the output parameter
   output_word, and the function returns true. Otherwise the function
   returns false. */

bool get_word(const char *input_line, int number, char *output_word);

/* char rhyming_letter(const char *ending) generates the rhyme scheme
   letter (starting with 'a') that corresponds to a given line ending
   (specified as the parameter). The function remembers its state
   between calls using an internal lookup table, such that subsequents
   calls with different endings will generate new letters.  The state
   can be reset (e.g. to start issuing rhyme scheme letters for a new
   poem) by calling rhyming_letter(RESET). */

char rhyming_letter(const char *ending);

/**
 * count the number of words in a given input string
 * @param words the input string 
 * @return number of words
 */
int count_words(std::string const& words);

/**
 * helper func that check if a char is a certain punct 
 * that separates two words
 * @param punt a char to be check
 * @return true if it is a punct, false otherwise
 */
bool is_punct(char ch);

/**
 * use the phonetic dictionary to construct the phonetic ending
 * for the (uppercase) word
 * @param word the input word
 * @param phonetic_ending, the char array to store the result
 * @return true if word is in dictionary
 */
bool find_phonetic_ending(std::string const& word, 
                          char * const phonetic_ending);

/**
 * checks if a char is AEIOU
 * @param ch the char to be checked
 * @return true if is vowel false otherwise
 */
bool is_vowel(char const ch);

/**
 * find rhyme scheme of a pontry in 
 * @param filename file name in which content should be read
 * @param scheme in which rhyme scheme will be stored
 * @return true if file can be opened, false otherwise
 */
bool find_rhyme_scheme(string const& filename, char * const scheme);

/**
 * identify style of a sonnet
 * @param filename file name in which content should be read
 * @return the sonnet type
 */
std::string identify_sonnet(std::string const& filename);