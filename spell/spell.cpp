#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include "spell.h"
#include <map>

using namespace std;

/* insert your function definitions here */
int frequency (string const& target) {
    ifstream input("words.dat");
    string str;
    char word[MAX_LENGTH];
    
    while (getline(input, str, '\n')) {
        get_word(str.c_str(), 2, word);
        if (!strcmp(word, target.c_str())) {
            get_word(str.c_str(), 1, word);
            string str_(word);
            return stoi(str_);
        }
    }
    return 0;
}


bool get_word(const char *input_line, int word_number, char *output_word) {
    char *output_start = output_word;
    int words = 0;

    if (word_number < 1) {
        *output_word = '\0';
        return false;
    }
  
    do {
        while (*input_line && !isalnum(*input_line)){input_line++;}

        if (*input_line == '\0') {break;}

        output_word = output_start;
        while (*input_line && (isalnum(*input_line) || *input_line=='\'')) {
            *output_word = *input_line;
            output_word++;
            input_line++;
        }
        *output_word = '\0';

        if (++words == word_number) {return true;}

    } while (*input_line);

    *output_start = '\0';
    return false;
}


int edit_distance(char const * const a, char const * const b) {
    int row = strlen(a);
    int col = strlen(b);
    vector<vector<int>> dp(row+1, vector<int>(col+1));
    for (int i = 0; i <= row; ++i) {dp[i][0] = i;}
    for (int j = 0; j <= col; ++j) {dp[0][j] = j;}

    for (int i = 1; i <= row; ++i) {
        for (int j = 1; j <= col; ++j) {
            update(a, b, i, j, dp);
        }
    }
    return dp[row][col];
}


void update(char const * const a, char const * const b, int i, int j, std::vector<std::vector<int>>& dp) {
    if (i > 1 && j > 1 && a[i-1] == b[j-2] && a[i-2] == b[j-1]) {
        int value1 = dp[i-1][j] + 1;
        int value2 = dp[i][j-1] + 1;
        int value3 = dp[i-1][j-1] + ((a[i-1] == b[j-1]) ? 0:1);
        int value4 = dp[i-2][j-2] + 1;
        dp[i][j] = min({value1, value2, value3, value4});
    }
    else {
        int value1 = dp[i-1][j] + 1;
        int value2 = dp[i][j-1] + 1;
        int value3 = dp[i-1][j-1] + ((a[i-1] == b[j-1]) ? 0:1);
        dp[i][j] = min({value1, value2, value3});
    }
}

void print_data(vector<vector<int>> const& data) {
    for (auto v: data) {
        for (auto d: v) {cout.width(3); cout << d;}
        cout << endl;
    }
    cout << endl;
}


bool spell_correct(char const * const word, char* fixed) {
    string check1 = "", check2 = "";
    int c1=0, c2=0;
    ifstream input("words.dat");
    string word_(word);
    string str;
    char check[MAX_LENGTH];

    while (getline(input, str, '\n')) {
        if (get_word(str.c_str(), 2, check)) {
            if (edit_distance(check, word) == 0) {
                strcpy(fixed, word);
                return false;
            }
            if (edit_distance(check, word) == 1) {
                string similar_word(check);
                if (frequency(similar_word) > c1) {
                    c1 = frequency(similar_word);
                    check1 = similar_word;
                }
            }
            if (edit_distance(check, word) == 2) {
                string similar_word(check);
                if (frequency(similar_word) > c2) {
                    c2 = frequency(similar_word);
                    check2 = similar_word;
                }
            }
        }
    }
    if (c1) {
        strcpy(fixed, check1.c_str());
        return true;
    }
    if (c2) {
        strcpy(fixed, check2.c_str());
        return true;
    }
    strcpy(fixed, word);
    return false;
}

