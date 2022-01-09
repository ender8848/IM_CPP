/**
 * These are helper functions from cpp exercises of previous-year exams
 * They are implemented directly in this .h file only for convenience. 
 */
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

/**
 * Q2 in palindrome,
 * compare 2 strings regardless of punctuations and case 
 * return 1 if similar, 0 if not
 */
int compare(char const * one, char const * two);

/**
 * helper func for Q2 in playfair
 * check if letter occurs before pos in str
 */
bool occurs_before(char const * const str, char letter, int pos);

/* get_word(...) retrieves a word from the input string input_line
   based on its word number. If the word number is valid, the function
   places an uppercase version of the word in the output parameter
   output_word, and the function returns true. Otherwise the function
   returns false. */
bool get_word(const char *input_line, int number, char *output_word);

/* count word num using get_word function */
int count_words(char const * words);


int main() {
    cout << "======== test for compare func ========" << endl;
    cout << "The strings 'this, and THAT......' and 'THIS and THAT!!!' are ";
    if (!compare("this, and THAT......", "THIS and THAT!!!")) {cout << "NOT ";}
    cout << "the same" << endl << "  (ignoring punctuation and case)" << endl;

    cout << "The strings 'this, and THAT' and 'THIS, but not that' are ";
    if (!compare("this, and THAT", "THIS, but not that")) {cout << "NOT ";}
    cout << "the same" << endl << "  (ignoring punctuation and case)" << endl << endl;


    cout << "======== test for occurs_before func ========" << endl;
    cout << "The letter a ";
    if (!occurs_before("alpha_go", 'a', 7)) {cout << "does not ";}
    cout << "occur(s) before 7th pos in word alpha_go" << endl;

    cout << "The letter z ";
    if (!occurs_before("amazon", 'z', 3)) {cout << "does not ";}
    cout << "occur(s) before 3th pos in word amazon" << endl;

    cout << "The letter z ";
    if (!occurs_before("amazon", 'z', 4)) {cout << "does not ";}
    cout << "occur(s) before 4th pos in word amazon" << endl << endl;


    cout << "======== test for get_word and count_words func ========" << endl;
    char word[512];
    bool success = get_word("One, two, three!", 2, word);
    if (success)
        cout << "Word number 2 in \"One, two, three!\" is " << word << endl;
    else
        cout << "Word number 2 in \"One, two, three!\" does not exist." << endl;
    success = get_word("One, two, three!", 4, word);
    if (success)
        cout << "Word number 4 in \"One, two, three!\" is " << word << endl;
    else
        cout << "Word number 4 in \"One, two, three!\" does not exist." << endl;
    cout << endl;

    cout << "The line \"It's  not so easy!\" contains ";
    cout << count_words("It's  not so easy!") << " words" << endl;
    cout << "The line \"\" contains ";
    cout << count_words("") << " words" << endl;
    cout << "The line \"Shall I compare thee to a Summer's day?\" contains ";
    cout << count_words("Shall I compare thee to a Summer's day?") << " words" << endl;
    cout << "The line \"Sometime too hot the eye of heaven shines,\" contains ";
    cout << count_words("Sometime too hot the eye of heaven shines,") << " words" << endl;
    cout << endl;

    return 0;
}


int compare(char const * one, char const * two) {
    // go to the position of first char
    while (!isalpha(*one) && *one) {++one;}
    while (!isalpha(*two) && *two) {++two;}
    if (strlen(one) == 0 && strlen(two) == 0) {return 1;}
    if (strlen(one) == 0 || strlen(two) == 0) {return 0;}
    if (toupper(*one) == toupper(*two)) {
        return compare(one + 1, two + 1);
    }
    else {
        return 0;
    }
}


bool occurs_before(char const * const str, char letter, int pos) {
    // whatever func uses it should ensure pos < strlen(str)
    for (int i = 0; i < pos; ++i) {
        if (str[i] == letter) {return true;}
    }
    return false;
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
            *output_word = toupper(*input_line);
            output_word++;
            input_line++;
        }
        *output_word = '\0';

        if (++words == word_number) {return true;}

    } while (*input_line);

    *output_start = '\0';
    return false;
}


int count_words(char const * words) {
    int count = 0;
    char output[64];
    while(get_word(words, ++count, output)) {}
    return count-1;
}