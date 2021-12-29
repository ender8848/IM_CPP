/* finished in 12/29/2021 using 98min */

#ifndef CORRECT_H
#define CORRECT_H

void ascii_to_binary(char letter, char *output);
char binary_to_ascii(char *binary);

/* converts input characters string into a corresponding stream of bits 
* @param str, input string
* @param binary, output bits string
*/
void text_to_binary(char const * const str, char * const binary);

/* converts a stream of bits into characters string 
* @param binary, input bits string
* @param str, output string
*/
void binary_to_text(char const * const binary, char * const str);

/* add correction digits in data
* @param data, input bits string 
* @param corrected, output bits string containing correcting bits
*/
void add_error_correction(char const * const data, char * const corrected);

/* decode from a bit string containing correcting bits, 
*  correct it if there are errors, return error numbers
* @param reveived, input bits string containing correcting bits
* @param docoded,  input bits string containing only data
* @return number of errors detected
*/
int decode(char const * const received, char * const decoded);


#endif