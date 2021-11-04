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
    list<int> mDefaultList;
    list<person> mInitList = {person("Vlad", 20), person("Egor", 21), person("Masha", 20)};
    std::deque<std::string> mDeq = {"Vlad", "Egor", "Masha"};
};

TEST_F(listTests, test)
{
    bool t = true;
    ASSERT_TRUE(t);
}


TEST_F(listTests, SeveralElemConstructor){
    list<int> severalElemList(3, 6);
    while (!severalElemList.isEmpty())
    {
        ASSERT_EQ(severalElemList.front(), 6);
        severalElemList.pop_front();
    }
}


TEST_F(listTests, CopyConstructor) {
    list<person> copyList = mInitList;
    ASSERT_EQ(copyList.size(), mInitList.size());
    auto i2 = mInitList.begin();
    auto i1 = copyList.begin();
    for (; i1 != copyList.end(); ++i1, ++i2) {
        ASSERT_EQ((*i1).getName(), (*i2).getName());
        ASSERT_EQ((*i1).getAge(), (*i2).getAge());
    }
}

TEST_F(listTests, MoveConstructor){
    list<int> moveList(list<int>(3,6));
    ASSERT_EQ(moveList.size(), 3);
    ASSERT_EQ(moveList.front(), moveList.back());
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
    //optional
}

TEST_F(listTests, MethodPush){
    for (int i=0; i<5; ++i){
        mDefaultList.push_back(i+1);
        mDefaultList.push_front(-1*(i+1));
    }
    ASSERT_EQ(mDefaultList.size(), 10);
    ASSERT_EQ(mDefaultList.front(), -5);
    ASSERT_EQ(mDefaultList.back(), 5);

    //  rewrite buffer

    mDefaultList.push_front(100);
    ASSERT_EQ(mDefaultList.size(), 1);
    ASSERT_EQ(mDefaultList.front(), mDefaultList.back());
}

TEST_F(listTests, MethodPop){
    mInitList.pop_front();
    ASSERT_EQ(mInitList.size(), 2);
    auto beginIterator = mInitList.begin();
    auto endIterator = mInitList.end();
    for (int i = 1; beginIterator != endIterator; ++beginIterator, ++i)
        ASSERT_EQ((*beginIterator).getName(), mDeq[i]);
}







TEST_F(listTests, AssignmentOperator){
    list<person> assignmentList;
    assignmentList = mInitList;
    auto i2 = mInitList.begin();
    auto i1 = assignmentList.begin();
    for (; i1 != assignmentList.end(); ++i1, ++i2) {
        ASSERT_EQ((*i1).getName(), (*i2).getName());
        ASSERT_EQ((*i1).getAge(), (*i2).getAge());
    }
}


TEST_F(listTests, MoveOperator){
    list<int> moveList;
    moveList = list<int>(3,6);
    ASSERT_EQ(moveList.size(), 3);
    ASSERT_EQ(moveList.front(), moveList.back());
}






