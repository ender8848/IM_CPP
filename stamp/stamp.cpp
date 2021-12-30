#include <iostream>
#include <openssl/sha.h>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <string>
#include "stamp.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

// helper function for internal use only
// transforms raw binary hash value into human-friendly hexademical form
void convert_hash(const unsigned char *str, char *output, int hash_length) {
  char append[16];
  strcpy (output, "");
  for (int n=0; n<hash_length; n++) {
    sprintf(append,"%02x",str[n]);
    strcat(output, append);
  }
}

// pre-supplied helper function
// generates the SHA1 hash of input string text into output parameter digest
// ********************** IMPORTANT **************************
// ---> remember to include -lcrypto in your linking step <---
// ---> so that the definition of the function SHA1 is    <---
// ---> included in your program                          <---
// ***********************************************************
void text_to_SHA1_digest(const char *text, char *digest) {
  unsigned char hash[SHA_DIGEST_LENGTH];
  SHA1( (const unsigned char *) text, strlen(text), hash);
  convert_hash(hash, digest, SHA_DIGEST_LENGTH);
}

/* add your function definitions here */
int leading_zeros(char const * const digest) {
  int count = 0;

  for (size_t i = 0; i < strlen(digest); ++i) {
    if (digest[i] == '0') {
      ++count;
    }
    else {break;}
  }

  for (size_t i = 0; i < strlen(digest); ++i) {
    if (!isxdigit(digest[i])) {return -1;}
  }

  return count;
}


bool file_to_SHA1_digest(char const * const filename, char * const digest) {
  ifstream input(filename);
  if (input.fail()) {
    strcpy(digest, "error");
    return false;
    }

  char ch;
  char st[MAXLEN];
  int pos = 0;
  while(input.get(ch)) {
    st[pos++] = ch;
  }
  st[pos] = '\0';

  text_to_SHA1_digest(st, digest);
  input.close();
  return true;
}


bool make_header(char const * const recipient, char const * const filename, 
                 char * const header) {
  int pos = 0;
  string s;
  int suffix = 0;
  strcpy(header,recipient);
  pos += strlen(recipient);
  header[pos++] = ':';
  ifstream input(filename);
  if (!file_to_SHA1_digest(filename, header + strlen(recipient) + 1)) {
    return false;
  }
  pos += HASHLEN;
  header[pos++] = ':';
  s = std::to_string(suffix);
  strcpy(header + pos, s.c_str());

  char digest[HASHLEN+1];
  text_to_SHA1_digest(header, digest);
  while (leading_zeros(digest) != 5) {
    ++suffix;
    s = std::to_string(suffix);
    strcpy(header + pos, s.c_str());
    text_to_SHA1_digest(header, digest);
  }
  return true;
}


bool is_valid_header(char const * const header) {
  int colon_num = 0;
  for (size_t i = 0; i < strlen(header); ++i) {
    if(header[i] == ':') {++colon_num;}
  }
  if (colon_num != 2) {return false;}
  return true;
}


bool is_same_recipient(char const * const email_address, 
                       char const * const header) {
  char email[LEN];
  for (size_t i = 0; i < strlen(header); ++i) {
    if (header[i] == ':') {
      email[i] = '\0';
      break;
    }
    else {email[i] = header[i];}
  }
  if (strcmp(email, email_address) == 0) {return true;}
  return false;
}


bool is_right_digest(char const * const filename, char const * const header) {
  char  check_digest[HASHLEN + 1];
  char header_digest[HASHLEN + 1];
  bool in_digest = false;
  int pos = 0;
  for (size_t i = 0; i < strlen(header); ++i) {
    if (header[i] == ':') {
      in_digest = !in_digest;
      }
    if (in_digest) {header_digest[pos++] = header[i+1];}
  }
  header_digest[HASHLEN] = '\0';
  if (!file_to_SHA1_digest(filename, check_digest)) {return false;}
  if (strcmp(check_digest, header_digest) == 0) {return true;}
  return false;
}


MessageStatus check_header(char const * const email_address, 
                           char const * const header, 
                           char const * const filename) {
  // sequence valid header -> recipient -> message digest -> counter
  if (!is_valid_header(header)) {return INVALID_HEADER;}
  if (!is_same_recipient(email_address, header)) {return WRONG_RECIPIENT;}
  if (!is_right_digest(filename, header)) {return INVALID_MESSAGE_DIGEST;}
  char digest[HASHLEN+1];
  text_to_SHA1_digest(header, digest);
  if (leading_zeros(digest) != 5) {return INVALID_HEADER_DIGEST;}
  return VALID_EMAIL;
}