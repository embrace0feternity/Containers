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
    for (int i=0; i<5; i++){
        l.push_front(i+1);
        l.push_back(-1*(1+i));
    }
    l.show();

    for (int i=0; i<3; ++i){
        l.push_front((i+1)*111);
        l.push_back(-1*111*(i+1));
    }
    l.show();

    return 0;
}
