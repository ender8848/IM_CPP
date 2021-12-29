#pragma once
/* finished in 12/29/2021 using 88min */

// SLEN for square len
int const S_LEN = 6;
int const STEP = 2;

/* produces an output string suitable for Playfair encoding 
*  from some input string - only char and num, uppcase and even lentgh 
* @param intput, input string
* @param output, output string
*/
void prepare(char const * const input, char * const output);


/* helper func, check if letter occurs before position pos 
* @param str, input string str
* @param letter, letter used to check if appeared
* @param pos an int position 
* @return true if the letter occurs in str before some position pos, false otherwise
*/
bool occurs_before(char const * const str, char letter, int pos);


/* helper func for Q2, renew 2-D cordinate of a grid 
* @param int * coord which contains (x,y)
*/
void renew_coord(int * const coord);


/* generate a encode square according to a codeword
* @param codeword, a encode string
* @param square, output 2-D char array
*/
void grid(char const * const codeword, char square[][S_LEN]);


/* helper func for Q3, find letter rol in the square
* @param square, encode grid
* @param ch, char to be found row
*/
int find_row(char const square[][S_LEN], char const ch);


/* helper func for Q3, find letter col in the square
* @param square, encode grid
* @param ch, char to be found col
*/
int find_col(char const square[][S_LEN], char const ch);


/* encode a pair of letters 
* @param square, encode grid
* @param inchar1, input letter to be encoded
* @param inchar2, input letter to be encoded
* @param outchar1, output encoded letter 
* @param outchar2, output encoded letter 
*/
void bigram(char const square[][S_LEN], 
            char const inchar1, char const inchar2, char& outchar1, char& outchar2);


/* encode a string using a grid
* @param square, the encoding grid to be used
* @param prepared, the prepared input string 
* @param encoded is an output parameter containing the encoded sentence
*/
void encode(char const square[][S_LEN], char const * const prepared, char * const encoded);


/* decode a string using a grid
* @param square, the encoding grid to be used
* @param encoded, the encoded input string
* @param decoded is an output parameter containing the decoded sentence
*/
void decode(char const square[][S_LEN], char const * const encoded, char * const decoded);