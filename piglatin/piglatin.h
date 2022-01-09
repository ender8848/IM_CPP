#pragma once
#include <fstream>
#include <iostream>

/**
 *  helper func, 
 * check if a char is vowel based on pig latin rule
 * @param ch, the pass-in chararcter
 * @param position, the position of ch
 * @param length, total length of whole word
 * @return true for piglatin vowel and false if not
 */
bool isVowel(char ch, int position, int length);

/**
 * returns the position of the first “vowel” in the given word
 * @param word, a string consisted with letters
 * @return position of the first if found, -1 if not found 
 */
int findFirstVowel(char const * const word);

/** 
 * helper func
 * check if an english word is all upper case
 * @param english a string to be checked
 * @return true for all upper case, false for not
 */
bool allUpper(char const * const english);

/**
 * translate english word into piglatin word 
 * @param english, string to be translated
 * @param piglatin, transletd result string 
 */
void translateWord(char const * const english, char * piglatin);

/**
 * helper func, 
 * write a string to output ostream;
 * @param word, a string to be print
 * @param os ostream
 */
void print(char const * const word, std::ostream& os);

/**
 *  translate thw whole sentence from input stream and write to output stream
 * @param is fstream
 * @param os ostream
 */
void translateStream(std::istream& is, std::ostream& os);