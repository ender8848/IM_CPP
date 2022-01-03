#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>
#include <map>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>

using namespace std;

#include "sonnet.h"

/* PRE-SUPPLIED HELPER FUNCTIONS START HERE */

/* NOTE: It is much more important to understand the interface to and
   the "black-box" operation of these functions (in terms of inputs and
   outputs) than it is to understand the details of their inner working. */

/* get_word(...) retrieves a word from the input string input_line
   based on its word number. If the word number is valid, the function
   places an uppercase version of the word in the output parameter
   output_word, and the function returns true. Otherwise the function
   returns false. */

bool get_word(const char *input_line, int word_number, char *output_word) {
  char *output_start = output_word;
  int words = 0;

  if (word_number < 1) {
    *output_word = '\0';
    return false;
  }
  
  do {
    while (*input_line && !isalnum(*input_line))
      input_line++;

    if (*input_line == '\0')
      break;

    output_word = output_start;
    while (*input_line && (isalnum(*input_line) || *input_line=='\'')) {
      *output_word = toupper(*input_line);
      output_word++;
      input_line++;
    }
    *output_word = '\0';

    if (++words == word_number)
      return true;

  } while (*input_line);

  *output_start = '\0';
  return false;
}

/* char rhyming_letter(const char *ending) generates the rhyme scheme
   letter (starting with 'a') that corresponds to a given line ending
   (specified as the parameter). The function remembers its state
   between calls using an internal lookup table, such that subsequents
   calls with different endings will generate new letters.  The state
   can be reset (e.g. to start issuing rhyme scheme letters for a new
   poem) by calling rhyming_letter(RESET). */

char rhyming_letter(const char *ending) {

  // the next rhyming letter to be issued (persists between calls)
  static char next = 'a';
  // the table which maps endings to letters (persists between calls)
  static map<string, char> lookup;

  // providing a way to reset the table between poems
  if (ending == RESET) {
    lookup.clear();
    next = 'a';
    return '\0';
  }

  string end(ending);

  // if the ending doesn't exist, add it, and issue a new letter
  if (lookup.count(end) == 0) {
    lookup[end]=next;
    assert(next <= 'z');
    return next++;
  }

  // otherwise return the letter corresponding to the existing ending
  return lookup[end];
}

/* START WRITING YOUR FUNCTION BODIES HERE */

int count_words(string const& words) {
  string word = "";
  int count = 0;
  for (auto it = words.begin(); it != words.end(); ++it) {
    if (is_punct(*it)) {
      if (word.length() > 0) {++count;}
      word = "";
    }
    else {word.push_back(*it);}
  }
  // most sentence does not end with a space, need this line to count last word
  if (word.length() > 0) {++count;}
  return count;
}

bool is_punct(char ch) {
  switch(ch) {
    case ' ': return true;
    case ',': return true;
    case '.': return true;
    case '?': return true;
    case '!': return true;
    case ';': return true;
    case ':': return true;
    case '"': return true;
    case '-': return true;
    default : break;
  }
  return false;
}


bool find_phonetic_ending(std::string const& word, 
                          char * const phonetic_ending) {
  string st;
  int pos = 0;
  ifstream input("dictionary.txt");
  while (input >> st) {
    if (st == word) {break;}
  }

  if (input.eof()) {
    input.close();
    return false;
  }

  getline(input, st, '\n');
  for (auto it = st.end(); it != st.begin(); --it) {
    if (is_vowel(*it)) {
      while (it != st.end()) {
        if (isupper(*it)) {
          phonetic_ending[pos++] = *it;
        }
        ++it;
      }
      phonetic_ending[pos] = '\0';
      break;
    }
  }
  input.close();
  return true;
}


bool is_vowel(char const ch) {
  switch(ch) {
    case 'A': return true;
    case 'E': return true;
    case 'I': return true;
    case 'O': return true;
    case 'U': return true;
    default : break;
  }
  return false;
}


bool find_rhyme_scheme(string const& filename, char * const scheme) {
  ifstream input(filename);
  if (input.fail()) {return false;}
  rhyming_letter(RESET);
  char word[50];
  int pos = 0;
  string st;
  while (getline(input, st, '\n')) {
    get_word(st.c_str(), count_words(st), word);
    if (find_phonetic_ending(word, word)) {
      scheme[pos++] = rhyming_letter(word);
    }
    else {return false;}
  }
  scheme[pos] = '\0';
  return true;
}


string identify_sonnet(string const& filename) {
  char scheme[512];
  scheme[0] = '\0';
  if (!find_rhyme_scheme(filename, scheme)) {
    return "";
  }
  if (!strcmp(scheme, "ababcdcdefefgg")) {return "shakespeare";}
  if (!strcmp(scheme, "abbaabbacdcdcd")) {return "petrarch";}
  if (!strcmp(scheme, "ababbcbccdcdee")) {return "spenser";}
  return "Unknown";
}

