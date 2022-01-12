#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

#include "dictionary.h"
#include "doublets.h"

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* Looks up a given word in the dictionary of approved words. 
   Returns true if the word is in the dictionary.
   Otherwise returns false. */

bool dictionary_search(const char *word) {
  static Dictionary dictionary("words.txt");
  return dictionary.search(word);
}

/* add your function definitions here */
bool valid_step(char const * current_word, 
                char const * next_word) {
   char const * current_word_ = current_word;
   char const * next_word_ = next_word;
   if (strlen(current_word_) != strlen(next_word_)) {return false;}
   if (!dictionary_search(current_word_) ||
       !dictionary_search(next_word_)) {return false;}
   int count = 0;
   for (size_t i = 0; i < strlen(current_word_); ++i) {
      if (current_word_[i] != next_word_[i]) {++count;}
   }
   if (count == 1) {return true;}
   return false;
}


bool display_chain(char const ** chain, ostream& out) {
   char const** check = chain;
   if (out.fail()) {return false;}
   int start = true;
   while (*check) {
      int dis = 0;
      while((*check)[dis]) {
         if (start || *(check+1) == NULL) {
            out << static_cast<char>(toupper((*check)[dis]));
         }
         else {
            out << static_cast<char>(tolower((*check)[dis]));
         }
         ++dis;
      }
      out << '\n';
      start = false;
      ++check;
   }
   return true;
}


bool valid_chain(char const ** chain) {
   // check chain length
   int len = 0;
   char const** check = chain;
   while (*check) {
      ++len;
      ++check;
   }
   if (len <= 1) {return false;}
   // check repetition first
   check = chain;
   set<string> words;
   while (*check) {
      string str = "";
      int dis = 0;
      while ((*check)[dis]) {
         str.push_back((*check)[dis]);
         ++dis;
      }
      if (words.count(str)) {return false;}
      else {words.insert(str);}
      ++check;
   }
   // check valid step
   check = chain;
   while (*(check+1)) {
      if (!valid_step(*check, *(check+1))) {return false;}
      ++check;
   }
   return true;
}


bool find_chain(char const * const start_word,
                char const * const target_word,
                const char** answer_chain,
                int max_steps) {
   if (!dictionary_search(start_word) ||
       !dictionary_search(target_word)) {
          return false;
   }
   if (strlen(start_word) != strlen(target_word)) {
      return false;
   }
   size_t len = strlen(start_word); 
   ifstream input("words.txt");
   vector<string> words;
   string word;
   while (input >> word) {
      if (word.length() == len) {words.push_back(word);}
   }
   string start(start_word);
   string target(target_word);
   vector<string> solution;
   vector<string> best_solution;
   bool result = find_chain_(start, target, solution, best_solution, words, max_steps);
   input.close();
   if (result == false || best_solution.size() > static_cast<size_t>(max_steps+1)) {
      answer_chain = nullptr;
      return false;
   }
   for (size_t i = 0; i < best_solution.size(); ++i) {cout << best_solution[i] << endl;}
   return true;
}


bool find_chain_(std::string const& start,
                 std::string const& target, 
                 std::vector<std::string>& solution, 
                 std::vector<std::string>& best_solution,
                 std::vector<std::string> const& dict,
                 int max_len) {
   solution.push_back(start);
   if (valid_step(start.c_str(), target.c_str())) {
      solution.push_back(target);
      if (best_solution.size() == 0) {best_solution = solution;}
      return true;
   }
   if (solution.size() == static_cast<size_t>(max_len)) {
      solution.pop_back();return false;
   }

   for (auto s: dict) {
      if (valid_step(start.c_str(), s.c_str()) && 
          find(solution.begin(), solution.end(), s) == solution.end() && 
          solution.size() <= static_cast<size_t>(max_len)) {
         if (find_chain_(s, target, solution, best_solution, dict, max_len)) {
            if (solution.size() <= static_cast<size_t>(max_len+1) && 
                solution.back() == target) {
               best_solution = solution;
               return true;
            }
            if (solution.size() <= best_solution.size() || best_solution.size() == 0) {
               best_solution = solution;
            }
         } 
      } 
   }
   solution.pop_back();
   return false;
}