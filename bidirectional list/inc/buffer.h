
#ifndef INC_BUFFER_H_
#define INC_BUFFER_H_

#include <memory>

/*
 * 		I decided to create a buffer class which contains 3 field:
 *
 * 		mBuff - arrays of node;
 * 		mBot - pointer to a current Node in array
 * 		maxSize - max size of buffer
 *
 * 		This class looks like a template class, although it works only with list`s Nodes
 * 		I've realized it later and left it as it is.
 */


template <typename T>
class buffer{
private:
	T *mBuff;
	T *mBot;
	size_t maxSize = 11;

	bool isFill(){
		return mBuff+maxSize == mBot;
	}
public:
	buffer() noexcept { mBuff = new T[maxSize]; mBot = mBuff; }
	~buffer() { delete[] mBuff; }

	size_t getMaxSize() const {
		return maxSize;
	}

	// This method returns a Node and is needed for copy constructor and assignment operator
	T& getNode(int index) const {
		return mBuff[index];
	}
	// The method helps me to create a fictitious element of a list
	T* getPlaceForFictive() const {
		return mBuff;
	}

	// The method allocates memory for 1 Node in an empty place of the buffer
	T* push() noexcept {
		mBot = mBuff+1;			// The first element of a list starts after fictitious element
		// To find out an empty space in the buffer for Node, i need to consider related list's elements.
		// If there aren't any related elements around (mNext == mPrev == nullptr), this place is meant empty
		for (; mBot <= mBuff+maxSize && mBot->mNext != nullptr && mBuff->mPrev != nullptr; ++mBot);
		return mBot;
	}

	// This method deletes transmitted Node
	void pop(T* node) noexcept{
		mBot = mBuff+1;
		// i pop to essential Node and call its destructor explicitly
		while (mBot != node) ++mBot;
		mBot->~T();
	}

	// This method destroys all the Nodes in buffer except fictitious
	void clear(){
		for (mBot = mBuff+1; mBot != mBuff + maxSize; mBot++)
			mBot->~T();

	}
};



#endif /* INC_BUFFER_H_ */
