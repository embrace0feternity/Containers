//
// Created by embrace0feternity on 3.11.21.
//

#ifndef BIDIRECTIONAL_LIST_BUFFER_H
#define BIDIRECTIONAL_LIST_BUFFER_H

#include <memory>
#include "list.h"
#include <array>
#include <typeinfo>

namespace customList {

    template<typename T, size_t maxSize>
    class buffer {
    private:
        inline static constexpr size_t mSize = maxSize+1;
        inline static int rewriteCountFront = 0;
        inline static int rewriteCountBack = 0;
        std::array<T, mSize> mBuff;
        T *mFront = &mBuff[0];
        T *mBack = &mBuff[0];

        T* rewrite(T &node, int &key) {
            T* tempPointer;
            if (key == 0) // push_front();
            {
                if (mFront->mNext == &mBuff[0]) mFront = &mBuff[0];
                if (mFront != mBuff[0].mNext)
                    rewriteCountFront++;
                tempPointer = mFront->mNext;
                mFront = mFront->mNext;
            }
            else
            {
                if (mBack->mPrev == &mBuff[0]) mBack = &mBuff[0];
                if (mBack != mBuff[0].mPrev)
                    rewriteCountBack++;
                tempPointer = mBack->mPrev;
                mBack = mBack->mPrev;
            }
            tempPointer->setData(node.getData());
            return tempPointer;
        }

    public:

        buffer() = default;

        T* getFictitious() {
            return &mBuff[0]; // test
        }

        T* push(T &&node, int &&key = 0) {
            int i = 0;
            T* tempPointer = &mBuff[1];
            while (tempPointer != &mBuff[mSize] && tempPointer != nullptr)
            {
                if ((tempPointer->mNext == nullptr && tempPointer->mPrev == nullptr))
                {
                    *tempPointer = node;
                    return tempPointer;
                }
                tempPointer = &mBuff[i++];
            }
            if (rewriteCountBack == mSize-2) rewriteCountBack = 0;
            if (rewriteCountFront == mSize-2) rewriteCountFront = 0;
            std::cout << " " << std::endl;
            return rewrite(node, key);
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

        [[nodiscard]] int getRewriteCount(int key = 0) const {
            if (key == 0) return rewriteCountFront;
            return rewriteCountBack;
        }
    };


}
#endif //BIDIRECTIONAL_LIST_BUFFER_H
