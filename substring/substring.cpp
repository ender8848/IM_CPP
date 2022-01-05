#include "substring.h"
#include <cstring>

int strlen2(char const * const st) {
    int len = 0;
    while (*(st + len)) {++len;}
    return len;
}


bool is_prefix(char const * const stp, char const * const st) {
    if (strlen2(stp) > strlen2(st)) {return false;}
    // It is substring_position's concern to ensure pass-in stp has a length > 0
    if (*stp == '\0') {return true;}
    if (*stp == *st) {
        return is_prefix(stp + 1, st + 1);
    }
    else {return false;}
    return false;
}


int substring_position(char const * const sub, char const * const st) {
    // defend empty substring
    if (strlen2(sub) == 0) {return 0;}
    if (strlen2(st) < strlen2(sub)) {return -1;}

    if (is_prefix(sub, st)) {return 0;}
    else if (strlen2(st) > strlen2(sub)) {
        return substring_position(sub, st+1) == -1 ? -1 : 1 + substring_position(sub, st + 1);
    }
    else {return -2;} 
}


/* below is challenge for fun */
int substring_position2(char const * const m, char const * const s) {
    return m?(strstr(s,m)?strstr(s,m)-s:-1):0;
}