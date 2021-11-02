
#ifndef INC_BUFFER_H_
#define INC_BUFFER_H_

#include <memory>
#include <array>
#include <iostream>

template <typename T>
class buffer{
private:
	inline static constexpr size_t mSize = 10;
	std::array<T, mSize> mBuff;
	T *current = &mBuff[0];
public:
	buffer() = default;
	T* push(){
		size_t i =1;
		for (; i<mSize; ++i){
			if (mBuff[i].mNext == nullptr && mBuff[i].mPrev == nullptr) return &mBuff[i];
		}
		current++;
		if (current >= &mBuff[mSize]) current = &mBuff[1];
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

	void showbuff()const {
		for (size_t i = 0; i<mSize; ++i)
			std::cout << "mBuff[i] = " << mBuff[i].mData  << "\t\taddr = " << &mBuff[i] << "\t\tmNext = " << mBuff[i].mNext
				<< "\t\tmPrev = " << mBuff[i].mPrev << std::endl;
	}
};



#endif /* INC_BUFFER_H_ */
