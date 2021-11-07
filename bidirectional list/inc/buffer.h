//
// Created by embrace0feternity on 3.11.21.
//

#ifndef BIDIRECTIONAL_LIST_BUFFER_H
#define BIDIRECTIONAL_LIST_BUFFER_H

#include <memory>
#include "list.h"
#include <array>
#include <iostream>

template <typename T, size_t maxSize>
class buffer{
private:
    inline static constexpr size_t mSize = maxSize;
    std::array<T, mSize> mBuff;
    T* mBot = &mBuff[0];
    T* mTop = &mBuff[mSize-1];
public:

    buffer() = default;

    T* get(){
        return mBot;
    }

    T* push_front(T&& data){
        int i = 0;
        T* current = &mBuff[1];
        while (current != &mBuff[mSize] && current != nullptr)
        {
            if ((current->mNext == nullptr && current->mPrev == nullptr))
            {
                *current = data;
                return current;
            }
            current = &mBuff[i++];
        }

        T* after;
        T* before;
        mBot = mBot->mNext;
        after = mBot->mNext;
        before = mBot->mPrev;

        *mBot = data;
        if (before != &mBuff[0])
        {
            before->mNext = after;
            after->mPrev = before;
            mBot->mNext = before;
            before->mPrev = mBot;
        }
        else
            mBot->mNext = after;
        mBot->mPrev = &mBuff[0];
        mBuff[0].mNext = mBot;



        std::cout << "Before = " << before->mData << "\t\tAfter = " << after->mData << std::endl;
        return mBot;
    }
    // after = 8, before = 100;
    T* push_back(const T& data){
        int i = 0;
        T* current = mTop;
        while (current != &mBuff[mSize] && current != nullptr)
        {
            if ((current->mNext == nullptr && current->mPrev == nullptr))
            {
                *current = data;
                return current;
            }
            current = &mBuff[i++];
        }
        current = &mBuff[0];

        T* temp = current->mNext;

        current->mNext = temp->mNext;
        temp->mNext->mPrev = current;

        current = temp;
        *current = data;
        return current;
    }

    void showbuff()const {
        std::cout << "----------------------------\n";
        for (size_t i = 0; i<mSize; ++i)
            std::cout << "mBuff[i] = " << mBuff[i].mData  << "\t\taddr = " << &mBuff[i] << "\t\tmNext = " << mBuff[i].mNext
                      << "\t\tmPrev = " << mBuff[i].mPrev << std::endl;
    }

};


#endif //BIDIRECTIONAL_LIST_BUFFER_H
