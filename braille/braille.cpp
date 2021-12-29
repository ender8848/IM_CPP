#include "braille.h"
#include <cstring>
#include <cctype>

int const UNITLEN = 6;

int encode_character(char const ch, char * braille) {
    if (ch >= 'A' && ch <= 'Z') {
        strcpy(braille, ".....O");
        return UNITLEN + encode_character(ch + 'a' - 'A', braille + UNITLEN);
    }

    if (ch >= '1' && ch <= '9') {
        strcpy(braille, "..OOOO");
        return UNITLEN + encode_character(ch - '1' + 'a', braille + UNITLEN);
    }

    if (ch == '0') {
        strcpy(braille, "..OOOO");
        return UNITLEN + encode_character('j', braille + UNITLEN);
    }

    switch (ch) {
        case 'a': strcpy(braille, "O....."); break;
        case 'b': strcpy(braille, "OO...."); break;
        case 'c': strcpy(braille, "O..O.."); break;
        case 'd': strcpy(braille, "O..OO."); break;
        case 'e': strcpy(braille, "O...O."); break;
        case 'f': strcpy(braille, "O...O."); break;
        case 'g': strcpy(braille, "OO.OO."); break;
        case 'h': strcpy(braille, "OO..O."); break;
        case 'i': strcpy(braille, ".O.O.."); break;
        case 'j': strcpy(braille, ".O.OO."); break;
        case 'k': strcpy(braille, "O.O..."); break;
        case 'l': strcpy(braille, "OOO..."); break;
        case 'm': strcpy(braille, "O.OO.."); break;
        case 'n': strcpy(braille, "O.OOO."); break;
        case 'o': strcpy(braille, "O.O.O."); break;
        case 'p': strcpy(braille, "OOOO.."); break;
        case 'q': strcpy(braille, "OOOOO."); break;
        case 'r': strcpy(braille, "OOO.O."); break;
        case 's': strcpy(braille, ".OOO.."); break;
        case 't': strcpy(braille, ".OOOO."); break;
        case 'u': strcpy(braille, "O.O..O"); break;
        case 'v': strcpy(braille, "OOO..O"); break;
        case 'w': strcpy(braille, ".O.OOO"); break;
        case 'x': strcpy(braille, "O.OO.O"); break;
        case 'y': strcpy(braille, "O.OOOO"); break;
        case 'z': strcpy(braille, "O.O.OO"); break;
        case '.': strcpy(braille, ".O..OO"); break;
        case ',': strcpy(braille, ".O...."); break;
        case ';': strcpy(braille, ".OO..."); break;
        case '-': strcpy(braille, "..O..O"); break;
        case '!': strcpy(braille, ".OO.O."); break;
        case '?': strcpy(braille, ".OO..O"); break;
        case '(':
        case ')': strcpy(braille, ".OO.OO"); break;
        default : break;
    }
    braille[UNITLEN] = '\0';
    return UNITLEN;
}


void encode(char const * ch, char * braille) {
    if (*ch == '\0') {
        *braille = '\0';
        return;
    }
    int step = encode_character(*ch, braille);
    encode(ch + 1, braille + step);
}


void print_braille(char const * ch, std::ostream& os) {
    int len = 2;
    int pos[len] = {0,3};
    print_certain_pos(ch, os, pos, len);
    os << '\n';
    pos[0] = 1; pos[1] = 4;
    print_certain_pos(ch, os, pos, len);
    os << '\n';
    pos[0] = 2; pos[1] = 5;
    print_certain_pos(ch, os, pos, len);
    os << '\n';
}


void print_certain_pos(char const * ch, std::ostream& os, int const * const pos, int const len) {
    if (*ch == '\0') {return;}
    char braille[2 * UNITLEN + 1];
    if (encode_character(*ch, braille) == UNITLEN) {
        for (int i = 0; i < len; ++i) {
            os << braille[pos[i]];
        }
        os << " ";
    }
    else {
        for (int i = 0; i < len; ++i) {
            os << braille[pos[i]];
        }
        os << " ";
        for (int i = 0; i < len; ++i) {
            os << braille[pos[i] + UNITLEN];
        }
        os << " ";
    }
    print_certain_pos(ch + 1, os, pos, len);
}