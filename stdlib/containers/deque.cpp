#include <iostream>
#include <deque>
#include <cstring>
using namespace std;

/**
 * std::deque (double-ended queue) is an indexed sequence container that 
 * allows fast insertion and deletion at both its beginning and its end. 
 * 双端队列（deque，全名double-ended queue）是一种具有队列和栈性质的数据结构。
 * 双端队列中的元素可以从两端弹出，插入和删除操作限定在队列的两边进行。
 * Defined in header <deque> (since C++11)
 * template<
 *  class T,
 *  class Allocator = std::allocator<T>
 * > class deque;
*/

int main() {
    // Create a deque containing integers
    std::deque<int> d = {7, 5, 16, 8};
 
    // Add an integer to the beginning and end of the deque
    d.push_front(13);
    d.push_back(25);
 
    // Iterate and print values of deque
    for(int n : d) {
        std::cout << n << '\n';
    }
}