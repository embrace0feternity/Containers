#include <iostream>
#include "list.h"

int main() {

    customList::list<int, 10> l;
    customList::list<int, 10> l2;
    for (int i=0; i<4; i++) l2.push_front(i+1);
    l = l2;

    for (const auto &i : l)
        std::cout << i << ' ';
    std::cout << std::endl;

    l.pop_front();
    std::cout << "\ndelete first\n";

    auto j = l.begin();
    j++;
    l.insert(j, 9);
    std::cout << "insert second\n";

    for (const auto &i : l)
        std::cout << i << ' ';
    std::cout << std::endl;

    return 0;
}
