#include <iostream>
#include "substring.h"

using namespace std;

int main() {
//   cout << is_prefix("this", "this is a simple exercise") << endl;
//   cout << is_prefix("is", "is a simple exercise") << endl;
//   cout << is_prefix("is a", "is a simple exercise") << endl;
//   cout << is_prefix("is an", "is a simple exercise") << endl;
//   cout << is_prefix("exercise", "exercise111") << endl;
//   cout << is_prefix("simple exercise", "simple") << endl;
//     cout << strlen("Hello world") << endl;
//     cout << strlen("H world") << endl;
//     cout << strlen("d") << endl;
  cout << substring_position2("this", "this is a simple exercise") << endl;
  cout << substring_position2("is", "this is a simple exercise") << endl;
  cout << substring_position2("is a", "this is a simple exercise") << endl;
  cout << substring_position2("is an", "this is a simple exercise") << endl;
  cout << substring_position2("exercise", "this is a simple exercise") << endl;
  cout << substring_position2("simple exercise", "this is a simple") << endl;
  cout << substring_position2("", "this is a simple exercise") << endl;
  cout << substring_position2("", "") << endl;
  return 0;
}