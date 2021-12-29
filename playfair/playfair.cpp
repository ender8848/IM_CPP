#include "playfair.h"
#include <cstring>
#include <cctype>
#include <iostream>


void prepare(char const * const input, char * const output) {
    int pos = 0;
    for (size_t i = 0; i < strlen(input); ++i) {
        if (isalnum(input[i])) {output[pos++] = toupper(input[i]);}
        else {continue;}
    }
    if (pos%2) {
        output[pos++] = 'X';
    }
    output[pos] = '\0';
}


bool occurs_before(char const * const str, char letter, int pos) {
    // whatever func uses it should ensure pos < strlen(str)
    for (int i = 0; i < pos; ++i) {
        if (str[i] == letter) {return true;}
    }
    return false;
}


void renew_coord(int * const coord) {
    if (++coord[1] >= S_LEN) {
        ++coord[0];
        coord[1] %= S_LEN;
    }
}


void grid(char const * const codeword,char square[][S_LEN]) {
    // coord for 2-d coordinate (ln,col) in square
    // (0,0) corresponds to left-up coner char
    int coord[2] = {0,0}; 
    int pos = 0;
    // add code word in square first
    while (pos < static_cast<int>(strlen(codeword))) {
        if(!occurs_before(codeword, codeword[pos], pos)) {
            square[coord[0]][coord[1]] = codeword[pos];
            renew_coord(coord);
        }
        ++pos;
    }

    // add rest characters inside square  
    for (char ch = 'A'; ch <= 'Z'; ++ch) {
        if(!occurs_before(codeword, ch, pos)) {
            square[coord[0]][coord[1]] = ch;
            renew_coord(coord);
        }
    }

    // add numbers inside square
    for (char ch = '0'; ch <= '9'; ++ch) {
        square[coord[0]][coord[1]] = ch;
        renew_coord(coord);
    }
}


int find_row(char const square[][S_LEN], char const ch) {
    for (int row = 0; row < S_LEN; ++row) {
        for (int col = 0; col < S_LEN; ++col) {
            if (square[row][col] == ch) {return row;}
        }
    }
    return -1;
}


int find_col(char const square[][S_LEN], char const ch) {
    for (int row = 0; row < S_LEN; ++row) {
        for (int col = 0; col < S_LEN; ++col) {
            if (square[row][col] == ch) {return col;}
        }
    }
    return -1;
}


void bigram(char const square[][S_LEN], 
            char const inchar1, char const inchar2, char& outchar1, char& outchar2) {
    outchar1 = square[find_row(square, inchar1)][find_col(square, inchar2)];
    outchar2 = square[find_row(square, inchar2)][find_col(square, inchar1)];
}


void encode(char const square[][S_LEN], char const * const prepared, char * const encoded) {
    if (*prepared == '\0') {
        *encoded = '\0';
        return;
    }
    bigram(square, prepared[0], prepared[1], encoded[0], encoded[1]);
    encode(square, prepared + STEP, encoded + STEP);
}


void decode(char const square[][S_LEN], char const * const encoded, char * const decoded) {
    encode(square, encoded, decoded);
}