//
// Created by embrace0feternity on 3.11.21.
//

#ifndef BIDIRECTIONAL_LIST_BUFFER_H
#define BIDIRECTIONAL_LIST_BUFFER_H

#include <memory>
#include "list.h"
#include <array>


namespace customList {

    template<typename T, size_t maxSize>
    class buffer {
    private:
        inline static constexpr size_t mSize = maxSize+1;
        inline static int mBotCount = 1;
        std::array<T, mSize> mBuff;
        T *mBot = &mBuff[0];
        T *mNextAfterPrevHead;
        T *mBeforePrevHead;

        T* rewrite(const T &data) {
            T *before;
            T *temp;
            T *test;
            if (mBotCount == 1)
            {
                mBot = mBuff[0].mNext;
                mNextAfterPrevHead = mBot->mNext;
            }
            else
            {
                before = mBeforePrevHead;
                before->mPrev = mBot;
                before->mNext = mNextAfterPrevHead->mNext;
                temp = mNextAfterPrevHead->mNext;
            }

            *mBot = data;       // manipulations with a new Head in the list    Create new Node in array
            mBuff[0].mNext = mBot;      // link to fictitious
            mBot->mPrev = &mBuff[0];
            if (mBotCount != 1)
            {
                mBot->mNext = before;
                test = mBot;
                for (int i = 0; i < mBotCount - 1; ++i)
                    test = test->mNext;
                mNextAfterPrevHead = temp;
                test->mNext = mNextAfterPrevHead;
                mNextAfterPrevHead->mPrev = test;

            }
            else
            {
                mBot->mNext = mNextAfterPrevHead;
            }
            ++mBotCount;
            mBeforePrevHead = mBot;

            mBot = mNextAfterPrevHead;
            return mBeforePrevHead;
        }

    public:

        buffer() = default;

        T* getFictitious() {
            return mBot; // test
        }

        T* push(T &&data) {
            int i = 0;
            T *current = &mBuff[1];
            while (current != &mBuff[mSize] && current != nullptr)
            {
                if ((current->mNext == nullptr && current->mPrev == nullptr))
                {
                    *current = data;
                    return current;
                }
                current = &mBuff[i++];
            }
            std::cout << mBotCount << std::endl;
            return rewrite(data);

        }

        T* push_back(T &&data) {
            *mBot = data;
            return mBot;        /* bullshit */
        }

        void pop(T *temp) {
            T *current = &mBuff[1];
            while (true)
            {
                if (current->mNext == temp->mNext)
                {
                    current->~T();
                    break;
                }
                current = current->mNext;
            }
        }

        buffer<T, maxSize>& operator = (const buffer &other){
            // copy pointers!
            for (size_t i = 0; i<mSize; ++i)
            {
                mBuff[i] = other.mBuff[i];
            }
            return *this;
        }

    };


}
#endif //BIDIRECTIONAL_LIST_BUFFER_H
