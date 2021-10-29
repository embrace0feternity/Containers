#ifndef INC_LIST_H_
#define INC_LIST_H_

#include "buffer.h"
#include <utility>
#include <iterator>
#include <initializer_list>

template <typename T>
class list{
public:
	class iterator;

	using const_iterator = iterator;
	using reverse_iterator = std::reverse_iterator<iterator>;

	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using size_type = size_t;
	using difference_type = std::ptrdiff_t;
private:
	class Node;

	buffer<Node> mBuff;
	Node* mHead = nullptr;
	Node* mTail = nullptr;
	size_type mSize = 0;

	// This function is using into move constructor and move move operator
	friend void swap(list<T> &first, list<T> &second) noexcept {
		std::swap(first.mBuff, second.mBuff);
		std::swap(first.mHead, second.mHead);
		std::swap(first.mTail, second.mTail);
		std::swap(first.mSize, second.mSize);
	}
public:
/*	constructor ------------------------------------------------------------------------------------- */
	list() noexcept {
		Node *fictitious = new(mBuff.getPlaceForFictitious()) Node;
		mHead = mTail = fictitious;
	}
/*	elements access --------------------------------------------------------------------------------- */
	reference front() {
		return mHead->mData;
	}

	reference back() {
		return mTail->mPrev->mData;
	}
/*	capacity ---------------------------------------------------------------------------------------- */
	bool isEmpty() const noexcept {
		return mHead == mTail;
	}

	size_type size() const noexcept {
		return mSize;
	}

/*	modifiers --------------------------------------------------------------------------------------- */
	void push_front(const T data = T()) {
		Node *temp = new(mBuff.push()) Node(data);
		temp->mNext = mHead;
		temp->mPrev = nullptr;
		mHead->mPrev = temp;
		mHead = temp;
		++mSize;
	}

	void push_back(const value_type data) {
		if (isEmpty()) push_front(data);
		else
		{
			Node *temp = new(mBuff.push()) Node(data);
			temp->mNext = mTail;
			temp->mPrev = mTail->mPrev;
			mTail->mPrev->mNext = temp;
			mTail->mPrev = temp;
			++mSize;
		}
	}

	void pop_front() {
		if (!isEmpty())
		{
			Node *temp = mHead;
			mHead = temp->mNext;
			mHead->mPrev = nullptr;
			mBuff.pop(temp);
			--mSize;
		}
	}

	void pop_back() {
		if (!isEmpty())
		{
			if (mTail->mPrev == mHead) pop_front();
			else
			{
				Node *temp = mTail->mPrev;
				mTail->mPrev = temp->mPrev;
				temp->mPrev->mNext = mTail;
				mBuff.pop(temp);
				--mSize;
			}
		}
	}


	void show()const{
		mBuff.showbuff();
	}

};




template <typename T>
class list<T>::Node{
public:
	T mData = 0;
	Node *mNext = nullptr;
	Node *mPrev = nullptr;
	Node() = default;
	Node(T data): mData(data) { }
	~Node() { mData.~T(); mNext = nullptr; mPrev = nullptr; }
	// this method return a value of Node and is used in copy constructor and operator =
	T getData() const {
		return mData;
	}

};

template <typename T>
class list<T>::iterator{
public:
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using difference_type = ptrdiff_t;
	using iterator_category = std::bidirectional_iterator_tag;
private:
	Node *mIter = nullptr;
public:
	iterator() = default;
	iterator(Node* ptr): mIter(ptr) { }
	iterator(const iterator &other): mIter(other.mIter) { }
	iterator(iterator &&other): mIter(other.mIter) {
		other.mIter = nullptr;
	}

	iterator& operator = (const iterator &other) {
		if (other.mIter == mIter) return *this;
		mIter = other.mIter;
		return *this;
	}

	iterator& operator = (iterator &&other) {
		if (other.mIter == mIter) return *this;
		mIter = other.mIter;
		other.mIter = nullptr;
		return *this;
	}

	reference operator* () {
		return mIter->mData;
	}

	bool operator == (const iterator &other) {
		return mIter == other.mIter;
	}

	bool operator != (const iterator &other) {
		return mIter != other.mIter;
	}

	iterator& operator -- () { // prefix
		if (mIter->mPrev != nullptr) mIter = mIter->mPrev;
		return *this;
	}

	iterator operator -- (int) { // postfix
		iterator temp = *this;
		if (mIter->mPrev != nullptr) mIter = mIter->mPrev;
		return temp;
	}

	iterator& operator ++ () { // prefix
		if (mIter->mNext != nullptr) mIter = mIter->mNext;
		return *this;
	}

	iterator operator ++ (int) { // postfix
		iterator temp = *this;
		if (mIter->mNext != nullptr) mIter = mIter->mNext;
		return temp;
	}
};



#endif /* INC_LIST_H_ */
