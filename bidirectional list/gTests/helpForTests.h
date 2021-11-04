//
// Created by embrace0feternity on 3.11.21.
//

#ifndef BIDIRECTIONAL_LIST_HELPFORTESTS_H
#define BIDIRECTIONAL_LIST_HELPFORTESTS_H

#include <string>

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
    bool operator == (const person &other){
        return (mName == other.mName && mAge == other.mAge);
    }
};

#endif //BIDIRECTIONAL_LIST_HELPFORTESTS_H
