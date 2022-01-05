#include <iostream>
#include <array>
#include <cstring>
using namespace std;

/**
 * std::array is a container that encapsulates fixed size arrays.
 * Defined in header <array> (since C++11)
 * template<
 *     class T,
 *     std::size_t N
 * > struct array;
*/

int main() {
    array<char, 8> chs = {'H', 'E', 'L', 'L', 'O', '!'};
    cout << "An array of 6 chars is initialized" << endl;
    cout << ".front() get the first element: " << chs.front() << endl;
    cout << ".back() get the last element (should be empty): " << chs.back() << endl;
    cout << ".data() direct access the data: " << chs.data() << endl;
    cout << "use strlen to check if a \\0 is automatically added: " << strlen(chs.data()) << endl;
    cout << ".size() is a more elegant way to get size: " << chs.size() << endl;
    cout << ".empty() checks if empty: " << chs.empty() << endl;
    cout << ".max_size() return max possible size: " << chs.max_size() << endl;
    

    return 0;
}