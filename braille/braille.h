#pragma once
#include <iostream>

/**
 * Q1 encode a char into braille type and return its length(6 or 12)
 * @param ch char to be encoded
 * @param braille output char array of braille
 * @return length of that braille, might be 6 or 12
 */
int encode_character(char const ch, char * braille);

/**
 * Q2 encode input sentence to braille type and put result in braille recursively
 * @param ch input char array 
 * @param braille output output char array of braille
 */
void encode(char const * ch, char * braille);

/**
 * Q3 put braille in a readable form to ostream 
 * in order to print out a six-len braille in 3 lines
 * This function prints out 0 3, 1 4, 2 5 of the braille. 
 * */
void print_braille(char const * ch, std::ostream& os);

/* helper func for Q4, print len units at one time, */
void print_certain_pos(char const * ch, 
                       std::ostream& os, 
                       int const * const pos, 
                       int const len);