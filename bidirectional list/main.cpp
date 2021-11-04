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
    list<int> moveList;
    moveList = list<int>(3,6);
    std::cout << moveList.front() << ' ' << moveList.back() << std::endl;
    return 0;
}
