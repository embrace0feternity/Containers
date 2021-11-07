//
// Created by embrace0feternity on 3.11.21.
//

#ifndef BIDIRECTIONAL_LIST_LIST_H
#define BIDIRECTIONAL_LIST_LIST_H

#include "buffer.h"
#include <utility>
#include <iterator>
#include <initializer_list>
#include <array>


template <typename T, size_t maxSize>
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

    buffer<Node, maxSize+1> mBuff;
    Node* mHead = nullptr;
    Node* mTail = nullptr;
    size_type mSize = 0;

    // This function is using into move constructor and move operator
    friend void swap(list<T, maxSize> &first, list<T, maxSize> &second) noexcept {
        std::swap(first.mHead, second.mHead);
        std::swap(first.mTail, second.mTail);
        std::swap(first.mSize, second.mSize);
        std::swap(first.mBuff, second.mBuff);
    }
public:
/*	constructor ------------------------------------------------------------------------------------- */
    list() noexcept {
        Node *fictitious = mBuff.get();
        mHead = mTail = fictitious;
    }

    // It also an analog of the STL initializer_list constructor
    list(const std::initializer_list<T> &init_list): list() {
        for (const auto &i: init_list)
        {
            push_back(i);
        }
    }

    // Deep copy constructor. It copies every Node from the source to the target list
    list(const list &other) noexcept: list() {
        mBuff = other.mBuff;
        /*for (size_type i = 0; i<other.mSize; ++i)
        {
            Node temp = other.mBuff.getNode(i+1);
            push_back(temp.getData());
        }
         */
    }

    // Move semantic constructor that uses my swap function
    list(list &&other) noexcept : list() {
        swap(*this, other);
    }

/*	destructor -------------------------------------------------------------------------------------- */
    ~list() = default;

/*	elements access --------------------------------------------------------------------------------- */
    reference front() {
        return mHead->mData;
    }

    reference back() {
        return mTail->mPrev->mData;
    }
/*	capacity ---------------------------------------------------------------------------------------- */
    [[nodiscard]] bool isEmpty() const noexcept {
        return mHead == mTail;
    }

    [[nodiscard]] size_type size() const noexcept {
        return mSize;
    }
/*  iterator ------------------------------------------------------------------------------------------ */

    iterator begin(){
        return iterator(mHead);
    }
    iterator end(){
        return iterator(mTail);
    }

    reverse_iterator rbegin(){
        return std::make_reverse_iterator(iterator(mTail));
    }
    reverse_iterator rend(){
        return std::make_reverse_iterator(iterator(mHead));
    }
/*	modifiers --------------------------------------------------------------------------------------- */
    void clear(){
        while(!isEmpty()) pop_back();
    }

    void push_front(const T& data) {
        Node *temp = mBuff.push_front(Node(data));
        if (mSize < maxSize) {
            temp->mNext = mHead;
            temp->mPrev = mTail;
            mHead->mPrev = temp;
            mHead = temp;
            mTail->mNext = mHead;
            ++mSize;
        }
        else
            mHead = temp;
    }

    void push_back(const T& data) {
        if (isEmpty()) push_front(data);
        else
        {
            if (mSize < maxSize)
                ++mSize;
            else
                mHead = mHead->mNext;
            Node *temp = mBuff.push_back(Node(data));
            temp->mNext = mTail;
            temp->mPrev = mTail->mPrev;
            mTail->mPrev->mNext = temp;
            mTail->mPrev = temp;
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

    void insert(iterator && pos, const T data){
        insert(pos, data);
    }

    void insert(iterator& pos, const T &data){
        iterator headIterator(mHead);
        if (pos == headIterator) push_front(data);
        else
        if (pos == iterator(mTail)) push_back(data);
        else
        {
            Node *temp = mBuff.push(Node(data));
            Node *before = mHead, *after;
            --pos;
            for (; headIterator != pos; before = before->mNext);
            after = before->mNext;
            temp->mNext = after;	temp->mPrev = before;
            after->mPrev = temp;	before->mNext = temp;
            ++mSize;
        }
    }

    // Delete 1 Node from list
    void erase(iterator& pos) {
        iterator headIterator(mHead);
        if (pos == headIterator) pop_front();
        else
        if (pos == iterator(mTail)) pop_back();
        else
        {
            Node *before = mHead, *after;
            --pos;
            for (; headIterator != pos; before = before->mNext);
            Node *temp = before->mNext;
            after = temp->mNext;
            before->mNext = temp->mNext;
            after->mPrev = temp->mPrev;
            mBuff->pop(temp);
            --mSize;
        }
    }

    // Delete a range [first, second] of Node from list
    void erase(iterator& first, iterator& second) {
        iterator headIterator(mHead);
        iterator tailIterator(mTail);
        if (first == second) erase(first);
        else if (first == headIterator)
        {
            while (first != second)
            {
                ++first;
                pop_front();
            }
        }
        else if (second == tailIterator)
        {
            --second;
            while (first != second)
            {
                --second;
                pop_back();
            }
            pop_back();
        }
        else
        {
            while (first != second)
            {
                Node *before = mHead, *after;
                --first;
                for (; headIterator != first; before = before->mNext);
                Node *temp = before->mNext;
                after = temp->mNext;
                before->mNext = temp->mNext;
                after->mPrev = temp->mPrev;
                mBuff->pop(temp);
                --mSize;
                ++first;
            }
        }
    }

/*	operator ---------------------------------------------------------------------------------------- */
    list<T, maxSize>& operator = (const list &other) {
        if (this == &other) return *this;
        while(mHead->mNext != nullptr)
        {
            pop_front();
        }
        for (size_type i = 0; i<other.mSize; ++i)
        {
            Node temp = other.mBuff.getNode(i+1);
            push_back(temp.getData());
        }
        return *this;
    }

    list<T, maxSize>& operator = (list &&other) noexcept {
        swap(*this, other);
        mBuff = other.mBuff;
        other.mBuff.~buffer();
        return *this;
        mBuff = std::move(other.mBuff);
        mHead = other.mHead;
        mTail = other.mTail;
        mSize = other.mSize;

        other.mHead = nullptr;
        other.mTail = nullptr;
        other.mSize = 0;
         return *this;
    }

    void show()const{
        mBuff.showbuff();
    }
};




template <typename T, size_t maxSize>
class list<T, maxSize>::Node{
public:
    T mData;
    Node *mNext = nullptr;
    Node *mPrev = nullptr;
    Node() = default;
    explicit Node(T data): mData(data) { }
    ~Node() { mData.~T(); mNext = nullptr; mPrev = nullptr; }
    // this method return a value of Node and is used in copy constructor and operator =
    T getData() const {
        return mData;
    }

};

template <typename T, size_t maxSize>
class list<T, maxSize>::iterator{
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
    explicit iterator(Node* ptr): mIter(ptr) { }
    iterator(const iterator &other): mIter(other.mIter) { }
    iterator(iterator &&other) noexcept : mIter(other.mIter) {
        other.mIter = nullptr;
    }

    iterator& operator = (const iterator &other) {
        if (this == &other) return *this;
        mIter = other.mIter;
        return *this;
    }

    iterator& operator = (iterator &&other) noexcept {
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

    const iterator operator -- (int) { // postfix
        const iterator temp = *this;
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



#endif //BIDIRECTIONAL_LIST_LIST_H
