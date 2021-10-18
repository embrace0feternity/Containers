#include "list.h"
#include <gtest/gtest.h>
#include <iostream>



class listTest : public ::testing::Test {
protected:
	list<int> l1;
	list<int> l2 = { 1, 6, 9, 21, -6 };

	void compareListAndArr(list<int> &l){
		int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		int k = 0;
		for (auto i = l.begin(); i != l.end(); ++i)
			ASSERT_EQ(*i, arr[k++]);
	}
};

/*	Size of lists ------------------------------------------------------------------------- */
TEST_F(listTest, fListIsEmpty) {
	size_t size = l1.size();
	ASSERT_EQ(size, 0); // size == 0
	ASSERT_TRUE(l1.isEmpty());
}

TEST_F(listTest, sListIsntEmpty) {
	size_t size = l2.size();
	ASSERT_GT(size, 0); // size > 0
	ASSERT_FALSE(l2.isEmpty());
}

/*	Front of secondlist (the first is empty)------------------------------------------------ */
TEST_F(listTest, sListBack) {
	auto frontElement = l2.front();
	ASSERT_EQ(frontElement, 1); // frontElement == 1
}

/*	Front of secondlist (the first is empty)------------------------------------------------ */
TEST_F(listTest, sListFront) {
	auto backElement = l2.back();
	ASSERT_EQ(backElement, -6); // backElement == -6
}

/*	Clear ---------------------------------------------------------------------------------- */
TEST_F(listTest, fListClear) {
	size_t size = l1.size();
	ASSERT_EQ(size, 0); // size > 0
	l1.clear();
	size = l1.size();
	ASSERT_EQ(size, 0); // size == 0
}

TEST_F(listTest, sListClear) {
	size_t size = l2.size();
	ASSERT_GT(size, 0); // size > 0
	l2.clear();
	size = l2.size();
	ASSERT_EQ(size, 0); // size == 0
}

/*	Iterator  ---------------------------------------------------------------------------------- */
TEST_F(listTest, sListBegin){
	ASSERT_EQ(*(l2.begin()),1);
}

TEST_F(listTest, sListEnd){
	auto tail = l2.end();
	--tail;
	EXPECT_EQ(*tail, -6);
}

TEST_F(listTest, sListRBegin){
	auto rhead = l2.rbegin();
	EXPECT_EQ(*rhead,-6);
}

TEST_F(listTest, sListREnd){
	EXPECT_EQ(*(l2.rend()), 1);
}

TEST_F(listTest, fListRIterator){
	int arr[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	int k = 0;
	for (auto i = l1.rbegin(); i != l1.rend(); i++)
		ASSERT_EQ(*i, arr[k++]);
}



/*	Push  ---------------------------------------------------------------------------------- */
TEST_F(listTest, fListPush){
	for (int i=0; i<2; i++) l1.push_front(i+1);
	for (int i=0; i<2; i++) l1.push_back((i+1)*10);
	for (int i=0; i<2; i++)
	{
		l1.push_back((i-4)*(i+1));
		l1.push_front((i-101)*(i+1));
	}
	size_t size = l1.size();
	ASSERT_LE(size, 10); // size <= 10
	auto frontElement = l1.front();
	ASSERT_EQ(frontElement, -200);
}

TEST_F(listTest, sListPush){
	l2.clear();
	for (int i=0; i<10; i++) l2.push_back(i+1);
	compareListAndArr(l2);
}

/*	Pop  ----------------------------------------------------------------------------------- */
TEST_F(listTest, sListPop){
	for (size_t i=0; i<l2.size()+5; i++)
	{
		l2.pop_back();
		l2.pop_front();
	}
	ASSERT_TRUE(l2.isEmpty());
}

TEST_F(listTest, fListPop){
	for (int i=0; i<10; i++) l1.push_back(i+1);
	size_t n = l1.size();
	for (size_t i=0; i<n-1; i++) l1.pop_front();
	auto frontElement = l1.front();
	ASSERT_EQ(frontElement, 10);
}

/*	Insert  -------------------------------------------------------------------------------- */
TEST_F(listTest, fListInsert){
	auto iter = l1.begin();
	for (int i=0; i<10; i++, ++iter)
	{
		l1.insert(iter, i+1);
	}
	compareListAndArr(l1);
}

/*	Erase  --------------------------------------------------------------------------------- */
TEST_F(listTest, fListErase){
	auto iter = l1.begin();
	l1.push_front(1);
	ASSERT_EQ(l1.size(), 1);
	ASSERT_EQ(*(l1.begin()),1);
	l1.erase(iter);
	ASSERT_EQ(l1.size(), 0);
}

TEST_F(listTest, sListRangeErase){
	auto head = l2.begin();
	auto tail = l2.end();
	tail--;
	l2.erase(head, tail);
	ASSERT_EQ(l2.size(), 1);
	ASSERT_EQ(l2.front(), -6);
	ASSERT_EQ(l2.back(), -6);
	head = l2.begin();
	l2.erase(head);
	ASSERT_TRUE(l2.isEmpty());
}

/*	Constructor  --------------------------------------------------------------------------------- */
TEST_F(listTest, constructorWithSize){
	list<int> l(6);
	ASSERT_FALSE(l.isEmpty());
	ASSERT_EQ(l.size(),6);
}

TEST_F(listTest, copyConstructor){
	list<int> targetList(l2);
	for (auto targetIter = targetList.begin(), Iter = l2.begin(); Iter != l2.end(); ++targetIter, ++Iter)
		ASSERT_EQ(*targetIter, *Iter);
}

TEST_F(listTest, moveConstructor){
	list<int> targetList(list<int>(5, 3));
	ASSERT_EQ(targetList.size(), 5);
	int sumAllElement = 0;
	for (const auto &i : targetList) sumAllElement += i;
	ASSERT_EQ(sumAllElement, 15);
}

/* Operator ------------------------------------------------------------------------------------- */

TEST_F(listTest, assignmentOperator){
	list<int> targetList(1);
	targetList = l2;
	for (auto targetIter = targetList.begin(), Iter = l2.begin(); Iter != l2.end(); ++targetIter, ++Iter)
		ASSERT_EQ(*targetIter, *Iter);
}

TEST_F(listTest, moveOperator){
	list<int> targetList;
	targetList = list<int>(5, 3);
	ASSERT_EQ(targetList.size(), 5);
	int sumAllElement = 0;
	for (const auto &i : targetList) sumAllElement += i;
	ASSERT_EQ(sumAllElement, 15);
}

/* Algorithm ------------------------------------------------------------------------------------- */
struct Sum{
	int sum = 0;
	Sum() = default;
	explicit Sum(int s): sum(s) { }
	void operator() (int n) {
		sum += n;
	}
	friend bool operator == (const Sum &s1, const Sum &s2){
		return s1.sum == s2.sum;
	}
};

TEST_F(listTest, std_for_each){
	Sum s = std::for_each(l2.begin(), l2.end(), Sum());
	ASSERT_EQ(s, Sum(31));
}

TEST_F(listTest, std_count){
	auto count = std::count(l2.begin(), l2.end(), 6);
	ASSERT_EQ(count, 1);
	count = std::count(l2.begin(), l2.end(), 1000);
	ASSERT_EQ(count, 0);
}


TEST_F(listTest, std_find){
	auto iter = std::find(l2.begin(), l2.end(), 10000);
	bool temp = (iter == l2.end())? true : false;
	ASSERT_TRUE(temp);
	iter = std::find(l2.begin(), l2.end(), 6);
	temp = (iter != l2.end())? true : false;
	ASSERT_TRUE(temp);
}

TEST_F(listTest, std_copy){
	auto iter = l2.begin();
	list<int> l3(4);
	iter++;
	std::copy(iter, l2.end(), l3.begin());
	for (auto l3iter = l3.begin(); iter != l2.end(); ++iter, ++l3iter)
		ASSERT_EQ(*iter, *l3iter);

	/* ---------------------------> */   FAIL(); // don't apply std::copy to list
}

TEST_F(listTest, std_reverse){
	l1 = l2;
	std::reverse(l2.begin(), l2.end());
	auto iter = l2.begin();
	for (auto rIter = l1.rbegin(); rIter != l1.rend(); ++rIter, ++iter)
		ASSERT_EQ(*iter, *rIter);
}

TEST_F(listTest, std_equal){
	auto temp = std::equal(l1.begin(), l1.end(), l2.begin(), l2.end());
	ASSERT_FALSE(temp);
	l1 = l2;
	temp = std::equal(l1.begin(), l1.end(), l2.begin(), l2.end());
	ASSERT_TRUE(temp);
}

TEST_F(listTest, sort){
	l2.sort();
	auto iter = l2.begin();
	ASSERT_EQ(*iter, 21);
	iter++;
	ASSERT_EQ(*iter, 9);
	iter = l2.end();
	--iter;
	ASSERT_EQ(*iter, -6);
}





