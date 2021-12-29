#include <iostream>
#include "soundex.h"

using namespace std;

int main() {

  // question 3

  cout << "====================== Question 3 ======================" << endl;

  cout << "There are ";
  cout << count("Leeson", "Linnings, Leasonne, Lesson and Lemon.") << " ";
  cout << "surnames in the sentence 'Linnings, Leasonne, Lesson and Lemon.'"
       << endl;
  cout << "  that have the same Soundex encoding as 'Leeson'" << endl;

  cout << "There are ";
  cout << count("Jackson", "Jakes, Jaxin, J acksin, Jones.");
  cout << " surnames in the sentence 'Jakes, Jaxin, J acksin, Jones.'" 
       << endl;
  cout << "  that have the same Soundex encoding as 'Jackson'" << endl << endl;

  
  return 0;
}

