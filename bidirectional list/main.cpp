#include <iostream>
#include "list.h"

int main() {

    customList::list<int, 10> l;
    for (int i=0; i<5; i++)
    {
        l.push_front(100*(i+1));
        l.push_back(i+1);
    }
    for (const auto &i : l)
        std::cout << i << ' ';
    std::cout << std::endl;

    for (int i=0; i<5; i++)
    {
        l.push_front(1000*(i+1));
        l.push_back(30*(i+1));
    }
    for (const auto &i : l)
        std::cout << i << ' ';
    std::cout << std::endl;

    return 0;
}
