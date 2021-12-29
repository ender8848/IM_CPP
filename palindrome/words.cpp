#include "words.h"
#include <cstring>
#include <string>
#include <cctype>
#include <algorithm>

void reverse(char const * const str1, char * const str2) {
    int len = strlen(str1) - 1;
    for (int i = len; i >= 0; --i) {
        str2[len - i] = str1[i];
    }
    // must add '\0' in the end!
    str2[++len] = '\0';
}


bool isSameChar(char a, char b) {
    return toupper(a) == toupper(b);
}


int compare(char const * one, char const * two) {
    // go to the position of char first
    while (!isalpha(*one) && *one) {++one;}
    while (!isalpha(*two) && *two) {++two;}
    if (strlen(one) == 0 && strlen(two) == 0) {return 1;}
    if (strlen(one) == 0 || strlen(two) == 0) {return 0;}
    if (isSameChar(*one, *two)) {
        return compare(one + 1, two + 1);
    }
    else {
        return 0;
    }
}

void rmNonLetter(char * const st) {
    for (int i = strlen(st) -1; i >= 0; --i) {
        // check and remove if not letter
        if (!isalpha(st[i])) {
            for (size_t j = i; j < strlen(st); ++j) {
                st[j] = st[j+1];
            } 
        }
    }
}


int palindrome(char const * const st) {
    char st2[strlen(st) + 1];
    strcpy(st2, st);
    // deal with special condition - one single char and no char
    rmNonLetter(st2);
    if (strlen(st2) <= 1) {return 1;}
    // check if there is 2 adjacent same letters
    for (size_t i = 0; i < strlen(st2) - 1; ++i) {
        if (isSameChar(st2[i], st2[i+1])) {return 1;}
    }
    if (strlen(st2) == 2) {return 0;}
    // check if there there is 'aba' structure inside
    for (size_t i = 0; i < strlen(st2) - 2; ++i) {
        if (isSameChar(st2[i], st2[i+2])) {return 1;}
    }
    return 0;
}


void sortLetter(char * st) {
    size_t minPos;
    char tmp;
    for (size_t i = 0; i < strlen(st); ++i) {
        minPos = i; // biggest letter
        for (size_t j = i; j < strlen(st); ++j) {
            if (toupper(st[j]) < toupper(st[minPos])) {minPos = j;}
        }
        tmp = st[i];
        st[i] = st[minPos];
        st[minPos] = tmp;
    }
}


int anagram(const char * const st1, const char * const st2) {
    char st1copy[strlen(st1) + 1]; 
    char st2copy[strlen(st2) + 1]; 
    strcpy(st1copy, st1);
    strcpy(st2copy, st2);
    rmNonLetter(st1copy);
    rmNonLetter(st2copy);
    sortLetter(st1copy);
    sortLetter(st2copy);
    if (compare(st1copy, st2copy) == 1) {return 1;}
    return 0;
}
