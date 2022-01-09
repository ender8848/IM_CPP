#include <iostream>
#include <cstring>
using namespace std;

int const BITSLEN = 8;
int const DATALEN = 4;
int const CORRECTLEN = 7;
// D for data bits and C for correcting bits
int const D1 = 2, D2 = 4, D3 = 5, D4 = 6, C1 = 0, C2 = 1, C3 = 3;


/* You are supplied with two helper functions */

/* converts a character into a binary string representation */
void ascii_to_binary(char ch, char *binary);

/* converts a binary string representation into a character */
char binary_to_ascii(char *binary);

void ascii_to_binary(char ch, char *binary) {
  for (int n = 128; n; n >>= 1) 
    *binary++ = (ch & n) ? '1' : '0';
  *binary = '\0';
}

char binary_to_ascii(char *binary) {
  int ch = 0;
  for (int n=0, slide=128; n<8; n++, slide >>= 1) {
    if (binary[n] == '1')
      ch = ch | slide;
  }
  return ch;
}

/* now add your own functions here */
void text_to_binary(char const * const str, char * const binary) {
    // no need to add '\0' coz ascii_to_binary does that work
    if (*str == '\0') {return;}
    ascii_to_binary(*str, binary);
    text_to_binary(str+1, binary + BITSLEN);
}


void binary_to_text(char const * const binary, char * const str) {
    if (*binary == '\0') {
        *str = '\0';
        return;
        }
    // copy 8 digit of binary
    char binary_copy[BITSLEN + 1];
    strncpy(binary_copy, binary, BITSLEN);
    *str = binary_to_ascii(binary_copy);
    binary_to_text(binary + BITSLEN, str+1);
}


void add_error_correction(char const * const data, char * const corrected) {
    if (*data == '\0') {
        *corrected = '\0';
        return;
    }
    // not sure how to avoid magic numbers here
    char c1 = (data[0] + data[1] + data[3])%2 + '0';
    char c2 = (data[0] + data[2] + data[3])%2 + '0';
    char c3 = (data[1] + data[2] + data[3])%2 + '0';
    corrected[C1] = c1; corrected[C2] = c2; corrected[C3] = c3;
    corrected[D1] = data[0]; corrected[D2] = data[1]; 
    corrected[D3] = data[2]; corrected[D4] = data[3];
    add_error_correction(data + DATALEN, corrected + CORRECTLEN);
}


int decode(char const * const received, char * const decoded) {
    int is_wrong = 0;
    if (*received == '\0') {
        *decoded = '\0';
        return 0;
    }
    // r_copy stands for received copy, only copy 8 length 
    char r_copy[CORRECTLEN + 1];
    strncpy(r_copy, received, CORRECTLEN);
    // not sure how to avoid magic numbers here
    int p1 = (r_copy[C3] + r_copy[D2] + r_copy[D3] + r_copy[D4] - DATALEN*'0')%2;
    int p2 = (r_copy[C2] + r_copy[D1] + r_copy[D3] + r_copy[D4] - DATALEN*'0')%2;
    int p3 = (r_copy[C1] + r_copy[D1] + r_copy[D2] + r_copy[D4] - DATALEN*'0')%2;

    if (p1 || p2 || p3) {
        int wrong_pos = p1 * 4 + p2 * 2 + p3;
        if (r_copy[wrong_pos-1] == '1') {
            r_copy[wrong_pos-1] = '0';
        }
        else {r_copy[wrong_pos-1] = '1';}
        is_wrong = 1;
    }
    decoded[0] = r_copy[D1]; decoded[1] = r_copy[D2];
    decoded[2] = r_copy[D3]; decoded[3] = r_copy[D4];
    return is_wrong + decode(received + CORRECTLEN, decoded + DATALEN);
}