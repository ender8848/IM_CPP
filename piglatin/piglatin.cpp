#include "piglatin.h"
#include <cctype>
#include <cstring>

int const MAXLEN = 64;

bool isVowel(char ch, int position, int length) {
    bool result = false;
    switch (tolower(ch)) {
        case 'a': result = true; break;
        case 'e': result = true; break;
        case 'i': result = true; break;
        case 'o': result = true; break;
        case 'u': result = true; break;
        default : result = false;
    }
    if (ch == 'y' && position > 0 && position < length - 1) {return true;}
    return result;
}


int findFirstVowel(char const * const word) {
    int pos = -1;
    int len = static_cast<int>(strlen(word));
    for (int i = 0; i < len; ++i) {
        if (isVowel(word[i], i, len)) {
            pos = i;
            break;
        }
    }
    return pos;
}


bool allUpper(char const * const english) {
    for (size_t i = 0; i < strlen(english); ++i) {
        if (islower(english[i])) {return false;}
    }
    return true;
}


void translateWord(char const * const english, char * piglatin) {
    // no content
    if (strlen(english) == 0) {
        piglatin[0] = '\0';
        return;
    }
    // has content, tackle sequence fstNum -> fstUpcase -> vowel
    if (!isalpha(english[0])) {
        strcpy(piglatin, english);
        return;
    }
    bool fstUp = false;
    if (isupper(english[0]) && !allUpper(english)) {
        fstUp = true;
    }

    int vwlPos = findFirstVowel(english);
    if (vwlPos == 0) {
        strcpy(piglatin, english);
        strcpy(piglatin + strlen(english), "way");
    }
    else if (vwlPos != -1) {
        strcpy(piglatin, english + vwlPos);
        strcpy(piglatin + strlen(piglatin), english);
        strcpy(piglatin + strlen(english), "ay");
    }
    else {
        strcpy(piglatin, english);
        strcpy(piglatin + strlen(english), "ay");
    }

    if (fstUp) {
        for (size_t i = 0; i < strlen(piglatin); ++i) {
            piglatin[i] = tolower(piglatin[i]);
        }
        piglatin[0] = toupper(piglatin[0]);
    }
}


void print(char const * const word, std::ostream& os) {
    int i = 0;
    if (strlen(word)) {
        while (word[i]) {os << word[i++];}
    }
}


void translateStream(std::istream& is, std::ostream& os) {
    int pos = 0;
    char english[MAXLEN];
    char piglatin[MAXLEN];
    char ch;
    // '.' mark in cin will end the loop
    while (is.get(ch)) {
        if (!isalnum(ch)) {
            english[pos] = '\0';
            pos = 0;
            translateWord(english, piglatin);
            print(piglatin, os);
            if (ch == '.') {
                os << "\noutput terminated due to end mark '.'";
                break;
            }
            os << ch;
            translateStream(is, os);
            return;
        }
        else {english[pos++] = ch;}
    }
}

