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
    T* mCurrent = &mBuff[0];
public:
    T* get(){
        return mCurrent++;
    }

    T* createNode(const T& data = T()){
        T* temp = &mBuff[1];
        int i = 0;
        while (temp != &mBuff[mSize] && temp != nullptr)
        {
            if ((temp->mNext == nullptr && temp->mPrev == nullptr))
            {
                *temp = data;
                mCurrent = temp;
                return temp;
            }
            temp = &mBuff[i++];
        }
        mCurrent++;
        if (mCurrent >= &mBuff[mSize])
            mCurrent = &mBuff[1];
        T* before = mCurrent->mPrev;
        T* after = mCurrent->mNext;
        before->mNext = after;
        after->mPrev = before;
        *mCurrent = data;
        return mCurrent;
    }

    void showbuff()const {
        std::cout << "----------------------------\n";
        for (size_t i = 0; i<mSize; ++i)
            std::cout << "mBuff[i] = " << mBuff[i].mData  << "\t\taddr = " << &mBuff[i] << "\t\tmNext = " << mBuff[i].mNext
                      << "\t\tmPrev = " << mBuff[i].mPrev << std::endl;
    }

    buffer<T, maxSize>& operator = (const buffer &other){
        mBuff = other.mBuff;
        mCurrent = other.mCurrent;
    }

};


#endif //BIDIRECTIONAL_LIST_BUFFER_H
