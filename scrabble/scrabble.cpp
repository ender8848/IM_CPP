#include <iostream>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>
#include "scrabble.h"
#include <algorithm>

using namespace std;

/* insert your function definitions here */

int tile_score(char tile) {
    tile = toupper(tile);
    switch(tile) {
        case 'A': 
        case 'E': 
        case 'I': 
        case 'L': 
        case 'N': 
        case 'O': 
        case 'R': 
        case 'S': 
        case 'T': 
        case 'U': return 1;
        case 'D': 
        case 'G': return 2;
        case 'B': 
        case 'C': 
        case 'M':
        case 'P': return 3;
        case 'F': 
        case 'H': 
        case 'V': 
        case 'W': 
        case 'Y': return 4;
        case 'K': return 5;
        case 'J': 
        case 'X': return 8;
        case 'Q': 
        case 'Z': return 10;
        case ' ': 
        case '?': return 0;
        default : break;
    }
    return -1;
}

bool can_form_word_from_tiles(std::string const& word, 
                              std::string const& tiles, 
                              char* played_tiles) {
    string word_ = word, tiles_ = tiles;
    if (word.size() == 0) {
        *played_tiles = '\0';
        return true;
    }
    auto it = find(tiles_.begin(), tiles_.end(), word_[0]);
    auto space = find(tiles_.begin(), tiles_.end(), ' ');
    auto question = find(tiles_.begin(), tiles_.end(), '?');

    if (it != tiles_.end()) {
        word_ = word.substr(1);
        *played_tiles = *it;
        tiles_.erase(it);
        return can_form_word_from_tiles(word_, tiles_, ++played_tiles);
    }
    else if (space != tiles_.end()) {
        word_ = word.substr(1);
        *played_tiles = *space;
        tiles_.erase(space);
        return can_form_word_from_tiles(word_, tiles_, ++played_tiles);
    }
    else if (question != tiles_.end()) {
        word_ = word.substr(1);
        *played_tiles = *question;
        tiles_.erase(question);
        return can_form_word_from_tiles(word_, tiles_, ++played_tiles);
    }
    else {return false;}
}

int compute_score(char const * const played_tiles, ScoreModifier* modifier) {
    int score = 0;
    int multiplier = 1;
    int i = 0;
    for (; i < static_cast<int>(strlen(played_tiles)); ++i) {
        if (modifier[i] == NONE) {
            score += tile_score(played_tiles[i]);
        }
        else if (modifier[i] == DOUBLE_LETTER_SCORE) {
            score += tile_score(played_tiles[i])*2;
        }
        else if (modifier[i] == TRIPLE_LETTER_SCORE) {
            score += tile_score(played_tiles[i])*3;
        }
        else if (modifier[i] == DOUBLE_WORD_SCORE) {
            score += tile_score(played_tiles[i]);
            multiplier = 2;
        }
        else if (modifier[i] == TRIPLE_WORD_SCORE) {
            score += tile_score(played_tiles[i]);
            multiplier = 3;
        }
        else {return INVALID_MODIFIER;}
    }
    score *= multiplier;
    if (i == LEN) {score += 50;}
    return score;
}


int highest_scoring_word_from_tiles(char const * const tiles, 
                                    ScoreModifier* modifier, 
                                    char* best_word) {
    int h_score = 0, score;
    char play_tiles[50];
    string word;
    ifstream input("words.txt");
    while (input >> word) {
        if (word.size() > 7) {continue;}
        string tiles_(tiles);
        if (can_form_word_from_tiles(word, tiles_, play_tiles)) {
            score = compute_score(play_tiles, modifier);
            if (score > h_score) {
                h_score = score;
                strcpy(best_word, play_tiles);
            }
        }
    }
    input.close();
    return h_score;
}