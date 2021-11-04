//
// Created by embrace0feternity on 3.11.21.
//

#ifndef BIDIRECTIONAL_LIST_BUFFER_H
#define BIDIRECTIONAL_LIST_BUFFER_H

#include <memory>
#include <array>
#include <iostream>

template <typename T>
class buffer{
private:
    inline static constexpr size_t mSize = 11;
    std::array<T, mSize> mBuff;
    T *current = &mBuff[0];
public:
    buffer() = default;
    T* push(){
        size_t i =1;
        for (; i<mSize; ++i){
            if (mBuff[i].mNext == nullptr && mBuff[i].mPrev == nullptr)
            {
                current = &mBuff[i];
                return current;
            }
        }
        current++;
        if (current > &mBuff[mSize-1]) current = &mBuff[1];
        return current;
    }

    void pop(T *pointer){
        size_t i=0;
        for (; pointer != &mBuff[i];){
            i++;
        }
        mBuff[i].~T();
    }

    T* getPlaceForFictitious(){
        return &mBuff[0];
    }

    [[nodiscard]] size_t getSize() const{
        return mSize-1;
    }

    const T& getNode(int i) const {
        return mBuff[i];
    }

    void showbuff()const {
        std::cout << "----------------------------\n";
        for (size_t i = 0; i<mSize; ++i)
            std::cout << "mBuff[i] = " << mBuff[i].mData  << "\t\taddr = " << &mBuff[i] << "\t\tmNext = " << mBuff[i].mNext
                      << "\t\tmPrev = " << mBuff[i].mPrev << std::endl;
    }
};


#endif //BIDIRECTIONAL_LIST_BUFFER_H
