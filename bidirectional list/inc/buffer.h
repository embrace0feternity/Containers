//
// Created by embrace0feternity on 3.11.21.
//

#ifndef BIDIRECTIONAL_LIST_BUFFER_H
#define BIDIRECTIONAL_LIST_BUFFER_H

#include <array>
#include <initializer_list>

namespace customList {

    template<typename T, std::size_t maxSize>
    class buffer {
    private:
        inline static constexpr std::size_t mSize = maxSize+1;
        std::array<T, mSize> mBuff;
        T *mFictitious = mBuff.begin();

    public:
        buffer() = default;
        buffer(std::initializer_list<T> other){
            for (const auto &i: other)
                push_back(i);
        }

        typename std::array<T, mSize>::iterator& getFictitious() {
            return mFictitious;
        }

        T* push(T &&node) {
            T* tempPointer = &mBuff[1]; // mFictitious->mNext doesn't work because as I create list, there is only fictitious element and
                                        // mNext == mPrev == nullptr;
            while (tempPointer != &mBuff[mSize])  // go along the buffer
            {
                if ((tempPointer->mNext == nullptr && tempPointer->mPrev == nullptr)) //if I find empty space into buffer, I'll fill it
                {
                    *tempPointer = node;
                    return tempPointer;
                }
                tempPointer++;  // go next element
            }
            return mFictitious;
        }

        template <typename lType>
        T* rewrite_back(lType &data){           // before:  1 2 3 4 5 6 f    ---->  after push_front(8): 8 2 3 4 5 6 f. Then I set 8 after 6 before f and get smth like this: 2 3 4 5 6 8 f
            T* temp = mFictitious->mNext;       // rewrite mHead data
            temp->setData(data);
            return temp;
        }

        template <typename lType>
        T* rewrite_front(lType &&data){         // before:  1 2 3 4 5 6 f    ---->  after push_front(7): 1 2 3 4 5 7 f. Then I set 7 before 1 and get smth like this: 7 1 2 3 4 5 f
            T* temp = mFictitious->mPrev;       // rewrite mTail data
            temp->setData(data);
            return temp;
        }


        void pop(T *temp) {
            T *current = mBuff.begin()->mNext;
            while (current != nullptr)
            {
                if (current->mNext == temp->mNext)
                {
                    current->~T();
                    break;
                }
                current = current->mNext;
            }
        }


        template <typename lType>
        T* insert(lType data){
            T* temp = mBuff.begin()->mPrev;
            temp->setData(data);
            return temp;
        }

        buffer<T, maxSize> &operator = (const buffer &other){
            if (this == &other)
                return *this;

            for (std::size_t i = 0; i<mSize; ++i)
                mBuff = other.mBuff;

            return *this;
        }

    };


}
#endif //BIDIRECTIONAL_LIST_BUFFER_H
