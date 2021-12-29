#pragma once

/* reverse str1 and put result in str2 */
void reverse(char const * const str1, char * const str2);

/* check if 2 chars are the same regardless of case */
bool isSameChar(char a, char b);

/* compare 2 strings regardless of punctuations and letter case 
   return 1 if similar, 0 if not */
int compare(char const * one, char const * two);

/* count how many letters in a sentence */
void rmNonLetter(char * const st);

/* check if a string is palindrome, return 1 if it is, 0 if not */
int palindrome(char const * const st); 

/* sort a string in ascending order */
void sortLetter(char * st);

/* check if a string is anagram, return 1 if it is, 0 if not */
int anagram(const char * const st1, const char * const st2);
