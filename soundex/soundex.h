# pragma once

/* encode surname and put result in soundex */
void encode(char const * const surname, char * const soundex);
/* map a char into another or do nothing */
char map(char ch);
/* compare if 2 string is the same recursively */
int compare(char const * sd1, char const * sd2);
/* count num of word that has same soundex as surname in a sentence */
int count(char const * surname, char const * sentence);