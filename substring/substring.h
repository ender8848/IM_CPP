# pragma once

/* calculate string length, similar to cstring */
int strlen2(char const * constst);
/* check if string prefix stp is prefix of st */
bool is_prefix(char const * const stp, char const * const st);
/* empty str -> 0, not found -> -1, found -> position */
int substring_position(char const * const sub, char const * const st);
/* guarantee return , if <0 -> -2, if >= 0 -> original number */
int gReturn(int num);
/* m for match string and s for string that might contain m */
int substring_position2(char const * const m, char const * const s);