#include <string>

enum ScoreModifier { NONE, DOUBLE_LETTER_SCORE, TRIPLE_LETTER_SCORE, DOUBLE_WORD_SCORE, TRIPLE_WORD_SCORE };
#define INVALID_MODIFIER -2;
// length for scoremodifier array
int const LEN = 7;
// bonus mark
int const BONUS = 50;

/* insert your function prototypes here */

/**
 * Q1 get score for a given tile
 * @param tile input char
 * @return score of the tile
 */
int tile_score(char tile);

/**
 * Q2 determine hether a given word can be made from given tiles
 * @param word input string of word to make, which is a valid English word
 * @param tiles input string of given tiles
 * @param play_tiles string containing ordered collection of tiles used
 * @return true if can make, false otherwise
*/
bool can_form_word_from_tiles(std::string const& word, 
                              std::string const& tiles, 
                              char* played_tiles);

/**
 * Q3 compute the score of a playtile according to tile score and modifier
 * @param play_tiles string containing ordered collection of tiles used
 * @param modifier the modifier used
 * @return score of the played_tiles
 */
int compute_score(char const * const played_tiles, ScoreModifier* modifier);

/**
 * Q4 return the highest word score that can be achieved from tiles
 * @param tiles string containing ordered collection of tiles used
 * @param modifier the modifier used
 * @param word output word that has the highest score
 * @return highest score 
 */
int highest_scoring_word_from_tiles(char const * const tiles, 
                                    ScoreModifier* modifier, 
                                    char* best_word);