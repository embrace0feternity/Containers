//
// Created by embrace0feternity on 3.11.21.
//

#include "list.h"
#include "helpForTests.h"
#include <gtest/gtest.h>
#include <deque>
#include <optional>

class listTests : public ::testing::Test {
protected:
    customList::list<int, 5> mDefaultList;
    customList::list<person, 3> mInitList = {person("Vlad", 20), person("Egor", 21), person("Masha", 20)};
    std::deque<std::string> mDeq = {"Vlad", "Egor", "Masha"};
};

TEST_F(listTests, test)
{
    bool t = true;
    ASSERT_TRUE(t);
}

TEST_F(listTests, CopyConstructor) {
    customList::list<person, 3> copyList = mInitList;
    ASSERT_EQ(copyList.size(), mInitList.size());
    auto i2 = mInitList.begin();
    auto i1 = copyList.begin();
    for (; i1 != copyList.end(); ++i1, ++i2)
    {
        ASSERT_EQ((*i1).getName(), (*i2).getName());
        ASSERT_EQ((*i1).getAge(), (*i2).getAge());
    }
}

TEST_F(listTests, MethodIsEmpty){
    ASSERT_TRUE(mDefaultList.isEmpty());
    ASSERT_FALSE(mInitList.isEmpty());
}

TEST_F(listTests, Iterator){
    auto beginIterator = mInitList.begin();
    auto endIterator = mInitList.end();
    for (int i = 0; beginIterator != endIterator; ++beginIterator, ++i)
    ASSERT_EQ((*beginIterator).getName(), mDeq[i]);
}

TEST_F(listTests, Reverse_iterator){
    std::reverse(mDeq.begin(), mDeq.end());
    auto rbeginIterator = mInitList.rbegin();
    auto rendIterator = mInitList.rend();
    for (int i = 0; rbeginIterator != rendIterator; ++rbeginIterator, ++i)
    ASSERT_EQ((*rbeginIterator).getName(), mDeq[i]);
}

TEST_F(listTests, MethodClear){
    ASSERT_EQ(mInitList.size(), 3);
    mInitList.clear();
    ASSERT_EQ(mInitList.size(), 0);
    ASSERT_NE(mInitList.front().getName(), "Vlad");
}

TEST_F(listTests, MethodPush){
    for (int i=0; i<2; ++i)
    {
        mDefaultList.push_back(i+1);
        mDefaultList.push_front(-1*(i+1));
    }
    ASSERT_EQ(mDefaultList.front(), -2);
    ASSERT_EQ(mDefaultList.back(), 2);
    ASSERT_EQ(mDefaultList.size(), 4);
}

TEST_F(listTests, rewriteBuffer){
    mInitList.push_back(person("Sonya", 20));
    mInitList.push_front(person("Katya", 20));
    mDeq.at(0) = "Katya";       mDeq.at(2) = "Sonya";

    auto beginIterator = mInitList.begin();
    auto endIterator = mInitList.end();

    for (int i = 0; beginIterator != endIterator; ++beginIterator, ++i)
        ASSERT_EQ((*beginIterator).getName(), mDeq[i]);
}

TEST_F(listTests, MethodPop){
    mInitList.pop_back();
    ASSERT_EQ(mInitList.size(), 2);
    ASSERT_EQ(mInitList.back().getName(), "Egor");

    mInitList.pop_front();
    ASSERT_EQ(mInitList.size(), 1);
    ASSERT_EQ(mInitList.front().getName(), "Egor");
}

TEST_F(listTests, MethodInsert){
    auto beginIterator = mDefaultList.begin();

    mDefaultList.insert(beginIterator,1);
    ASSERT_EQ(mDefaultList.size(), 1);
    ASSERT_EQ(mDefaultList.front(), 1);

    mDefaultList.insert(mDefaultList.end(),3);
    ASSERT_EQ(mDefaultList.size(), 2);
    ASSERT_EQ(mDefaultList.front(), 1);
    ASSERT_EQ(mDefaultList.back(), 3);

    beginIterator = mDefaultList.begin();
    beginIterator++;
    mDefaultList.insert(beginIterator,2);

    for (size_t i = 0; !mDefaultList.isEmpty(); ++i)
    {
        ASSERT_EQ(mDefaultList.front(),i+1);
        mDefaultList.pop_front();
    }
}

TEST_F(listTests, MethodErase){
    auto iter = mInitList.begin();
    iter++;
    mInitList.erase(iter);

    ASSERT_EQ(mInitList.front().getName(), "Vlad");
    mInitList.pop_front();

    ASSERT_EQ(mInitList.front().getName(), "Masha");
    mInitList.pop_front();
}

TEST_F(listTests, MethodErase2){ // range erase
    mInitList.erase(mInitList.begin(), mInitList.end());
    ASSERT_EQ(mInitList.size(), 0);
}


TEST_F(listTests, AssignmentOperator){
    customList::list<person,3> assignmentList;
    assignmentList = mInitList;
    auto i2 = mInitList.begin();
    auto i1 = assignmentList.begin();
    for (; i1 != assignmentList.end(); ++i1, ++i2)
    {
        ASSERT_EQ((*i1).getName(), (*i2).getName());
        ASSERT_EQ((*i1).getAge(), (*i2).getAge());
    }
}







