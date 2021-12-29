#include <iostream>
#include "words.h"

using namespace std;

int main() {

  /*** QUESTION 1 ***/
  char reversed[9];
  reverse("lairepmi", reversed);
  cout << "'lairepmi' reversed is '" << reversed << "'" << endl;
  reverse("desserts", reversed);
  cout << "'desserts' reversed is '" << reversed << "'" << endl << endl;

  /*** QUESTION 2 ***/
  cout << "The strings 'this, and THAT......' and 'THIS and THAT!!!' are ";
  if (!compare("this, and THAT......", "THIS and THAT!!!"))
    cout << "NOT ";
  cout << "the same" << endl << "  (ignoring punctuation and case)" << endl;
  
  cout << "The strings 'this, and THAT' and 'THIS, but not that' are ";
  if (!compare("this, and THAT", "THIS, but not that")) 
    cout << "NOT ";
  cout << "the same" << endl << "  (ignoring punctuation and case)" << endl << endl;


  /*** QUESTION 3 ***/
  cout << "The string 'fuck' is ";
  if (!palindrome("fuck"))
    cout << "NOT ";
  cout << "a palindrome." << endl;

    cout << "The string 'Zhainb' is ";
  if (!palindrome("Zhainb"))
    cout << "NOT ";
  cout << "a palindrome." << endl;

    cout << "The string 'Huang' is ";
  if (!palindrome("Huang"))
    cout << "NOT ";
  cout << "a palindrome." << endl;



  cout << "The string '0' is ";
  if (!palindrome("0"))
    cout << "NOT ";
  cout << "a palindrome." << endl;

  cout << "The string 'Aa' is ";
  if (!palindrome("Aa"))
    cout << "NOT ";
  cout << "a palindrome." << endl;

  cout << "The string '' is ";
  if (!palindrome(""))
    cout << "NOT ";
  cout << "a palindrome." << endl;

    cout << "The string 'kick your ass' is ";
  if (!palindrome("kick your ass"))
    cout << "NOT ";
  cout << "a palindrome." << endl;

    cout << "The string 'Lol' is ";
  if (!palindrome("Lol"))
    cout << "NOT ";
  cout << "a palindrome." << endl;

  cout << "The string 'Madam I'm adam' is ";
  if (!palindrome("Madam I'm adam"))
    cout << "NOT ";
  cout << "a palindrome." << endl;
 
  cout << "The string 'rotor' is ";
  if (!palindrome("rotor"))
    cout << "NOT ";
  cout << "a palindrome." << endl;

  cout << "The string 'Madam I'm adam' is ";
  if (!palindrome("Madam I'm adam"))
    cout << "NOT ";
  cout << "a palindrome." << endl;
  cout << "The string 'Madam I'm not adam' is ";
  if (!palindrome("Madam I'm not adam"))
    cout << "NOT ";
  cout << "a palindrome." << endl << endl;

  /*** QUESTION 4 ***/

  cout << "The string 'I am a weakish speller!' is ";
  if (!anagram("I am a weakish speller!", "William Shakespeare"))
    cout << "NOT ";
  cout << "an anagram of 'William Shakespeare'" << endl;

  cout << "The string 'I am a good speller!' is ";
  if (!anagram("I am a good speller!", "William Shakespeare"))
    cout << "NOT ";
  cout << "an anagram of 'William Shakespeare'" << endl;

  cout << "The string 'doadjoie(*&%(*&' is ";
  if (!anagram("doadjoie(*&%(*&", "    doad(*&joie(*&%"))
    cout << "NOT ";
  cout << "an anagram of '    doad(*&joie(*&%'" << endl;

  cout << "The string 'jsifhd(*#%^)(Q^JF:E' is ";
  if (!anagram("jsifhd(*#%^)(Q^JF:E", "jsiQ^fhJF:E'd(*#%^)("))
    cout << "NOT ";
  cout << "an anagram of 'jsiQ^fhJF:E'd(*#%^)(" << endl;

  cout << "The string '1' is ";
  if (!anagram("1", "2"))
    cout << "NOT ";
  cout << "an anagram of '2" << endl;

  cout << "The string 'Hello, World!' is ";
  if (!anagram("Hello, World!", "Goodbye, World!"))
    cout << "NOT ";
  cout << "an anagram of 'Goodbye, World" << endl;

  return 0;
}