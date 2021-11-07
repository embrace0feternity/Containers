#include <iostream>
#include "list.h"
#include <deque>
#include <string>
#include <algorithm>

class person{
    std::string mName;
    int mAge{};
public:
    person() = default;
    person(std::string &&name, int &&age): mName(name), mAge(age) { }

    [[nodiscard]] std::string_view getName() const {
        return mName;
    }
    [[nodiscard]] int getAge() const {
        return mAge;
    }

};

int main() {

    list<int, 10> l;

    for (int i=0; i<10; ++i)
        l.push_front(i+1);
    for (const auto &i : l)
        std::cout << i << ' ';
    std::cout << std::endl;
    l.show();

    for (int i=0; i<10; ++i)
        l.push_front(100*(i+1));
    for (const auto &i : l)
        std::cout << i << ' ';
    std::cout << std::endl;
    l.show();



    return 0;
}
