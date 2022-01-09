#include "soundex.h"
#include <cstring>
#include <cctype>
#include <algorithm>
#include <string>

void encode(char const * surname, char * soundex) {
    soundex[0] = surname[0];
    char previousMap = ' ';
    int pos = 1;
    for (size_t i = 1; i < strlen(surname); ++i) {
        if (!isalpha(map(surname[i])) && pos < 4 && (map(surname[i]) != previousMap)) {
            soundex[pos++] = map(surname[i]);
        }
        previousMap = map(surname[i]);
    }
    for (size_t i = pos; i < 4; ++i) {soundex[i] = '0';}
}


char map(char ch) {
    ch = toupper(ch);
    switch (ch) {
        case 'B': case 'F': case 'P': case 'V': 
            ch = '1'; break;
        case 'C': case 'G': case 'J': case 'K': case 'Q': case 'S': case 'X': case 'Z': 
            ch = '2'; break;
        case 'D': case 'T': 
            ch = '3'; break;
        case 'L': 
            ch = '4'; break;
        case 'M': case 'N': 
            ch = '5'; break;
        case 'R': 
            ch = '6'; break;
        default : 
            break;
    }
    return ch;
}


int compare(char const * sd1, char const * sd2) {
    if (strlen(sd1) == 0 && strlen(sd2) == 0) {return 1;}
    else {
        if (*sd1 != *sd2) {return 0;}
        else {return compare(sd1 + 1, sd2 + 1);}
    }
}


int count(char const * surname, char const * sentence) {
    int count = 0;
    char sd1[5], sd2[5];
    std::string word = "";
    // split words from a sentence
    for (size_t i = 0; i < strlen(sentence); ++i) {
        if (!isalpha(sentence[i])) {
            encode(surname, sd1);
            encode(word.c_str(), sd2);
            if (compare(sd1, sd2)) {++count;}
            word = "";
        }
        else {word += sentence[i];}
    }
    return count;
}


