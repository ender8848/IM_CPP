#pragma once
#include <iostream>

/* encode a char into braille type and return its length(6 or 12) */
int encode_character(char const ch, char * braille);
/* encode a input sentence to braille type and put result in braille */
void encode(char const * ch, char * braille);
/* put braille in a readable form to ostream */
void print_braille(char const * ch, std::ostream& os);
/* helper functions, print len units at one time, */
void print_certain_pos(char const * ch, std::ostream& os, int const * const pos, int const len);