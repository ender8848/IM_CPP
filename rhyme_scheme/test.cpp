#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>
#include <map>
#include <string>
#include "sonnet.h"
using namespace std;



int main() {
  // Question 3
  char test[20] = {};
  test[0] = '1';
  cout << strlen(test) << endl;
  cout << "====================== Question 3 ======================" << endl << endl;

  char scheme[512];
  find_rhyme_scheme("shakespeare.txt", scheme); 
  cout << "The rhyme scheme of shakespeare.txt is " << scheme << endl;

  find_rhyme_scheme("petrarch.txt", scheme);
  cout << "The rhyme scheme of petrarch.txt is " << scheme << endl;

  find_rhyme_scheme("spenser.txt", scheme);
  cout << "The rhyme scheme of spenser.txt is " << scheme << endl;

  cout << endl;
    return 0;
}

