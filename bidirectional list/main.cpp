#include <iostream>
#include "list.h"
#include "array"


class person{
    std::string mName;
    int mAge{};
public:
    person() = default;
    person(std::string &&name, int &&age): mName(name), mAge(age) { }
    person(const person &other): mName(other.mName), mAge(other.mAge) {

    }

    [[nodiscard]] std::string_view getName() const {
        return mName;
    }
    [[nodiscard]] int getAge() const {
        return mAge;
    }
    bool operator == (const person &other){
        return (mName == other.mName && mAge == other.mAge);
    }
};

int main() {
    const std::size_t size = 4;

    customList::list<int,size> l2;
    for (std::size_t i=0; i<size; ++i)
        l2.push_front(i+1);

    customList::list<int,size> l = l2;
    for (const auto &i : l)
        std::cout << i << ' ';
    std::cout << std::endl << std::endl;
    /*
    std::cout << "Push_front:\n";
    for (int i=0; i<4; ++i)
        l.push_front(i+1);
    for (const auto &i : l)
        std::cout << i << ' ';
    std::cout << std::endl << std::endl;

    std::cout << "Push_back (rewrite):\n";
    l.push_back(100);
    l.push_back(200);
    for (const auto &i : l)
        std::cout << i << ' ';
    std::cout << std::endl << std::endl;

    std::cout << "Push_front (rewrite):\n";
    l.push_front(1000);
    l.push_front(2000);
    for (const auto &i : l)
        std::cout << i << ' ';
    std::cout << std::endl << std::endl;

    std::cout << "Random insert:\n";
    auto iter = l.begin();
    ++iter;
    l.insert(iter, 666);
    for (const auto &i : l)
        std::cout << i << ' ';
    std::cout << std::endl << std::endl;

    std::cout << "Random erase:\n";
    ++iter;
    l.erase(iter);
    for (const auto &i : l)
        std::cout << i << ' ';
    std::cout << std::endl << std::endl;

    std::cout << "One more time push_front (not rewrite!):\n";
    l.push_front(3333);
    for (const auto &i : l)
        std::cout << i << ' ';
    std::cout << std::endl << std::endl;

    std::cout << "Push_back (rewrite)\n";
    l.push_back(11);
    for (const auto &i : l)
        std::cout << i << ' ';
    std::cout << std::endl;

     */
    return 0;
}