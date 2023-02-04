#pragma once

#include <cassert>

template<typename T>
class FixedPriorityQueue
{
public:
    inline FixedPriorityQueue(size_t elementCount)
        : mSize(0)
    {
        mDatas = new T[elementCount];
        mCapacity = elementCount;
    }

    inline ~FixedPriorityQueue()
    {
        delete[] mDatas;
    }

    void push(T data)
    {
        if (mSize == mCapacity)
        {
            return;
        }

        mDatas[mSize] = data;

        int currentIndex = mSize;
        int parentIndex = (currentIndex - 1) / 2;
        while (currentIndex != parentIndex)
        {
            if (mDatas[parentIndex] < mDatas[currentIndex])
            {
                T temp = mDatas[parentIndex];
                mDatas[parentIndex] = mDatas[currentIndex];
                mDatas[currentIndex] = temp;

                currentIndex = parentIndex;
                parentIndex = (parentIndex - 1) / 2;
            }
            else
            {
                break;
            }
        }
        mSize++;
    }

    void pop()
    {
        assert(mSize > 0);
        mDatas[0] = mDatas[mSize - 1];
        mSize--;

        if (mSize <= 1)
        {
            return;
        }

        int currentIndex = 0;
        int maxIndex = mSize - 1;
        while (true)
        {
            int leftChildIndex = currentIndex * 2 + 1;
            int rightChildIndex = currentIndex * 2 + 2;

            if (rightChildIndex <= maxIndex)
            {
                if (mDatas[currentIndex] > mDatas[leftChildIndex] && mDatas[currentIndex] > mDatas[rightChildIndex])
                {
                    break;
                }
                else if (mDatas[leftChildIndex] >= mDatas[rightChildIndex])
                {
                    T temp = mDatas[leftChildIndex];
                    mDatas[leftChildIndex] = mDatas[currentIndex];
                    mDatas[currentIndex] = temp;

                    currentIndex = leftChildIndex;
                }
                else
                {
                    T temp = mDatas[rightChildIndex];
                    mDatas[rightChildIndex] = mDatas[currentIndex];
                    mDatas[currentIndex] = temp;

                    currentIndex = rightChildIndex;
                }
            }
            else if (leftChildIndex <= maxIndex)
            {
                if (mDatas[leftChildIndex] > mDatas[currentIndex])
                {
                    T temp = mDatas[leftChildIndex];
                    mDatas[leftChildIndex] = mDatas[currentIndex];
                    mDatas[currentIndex] = temp;
                }

                break;
            }
            else
            {
                break;
            }
        }
    }

    inline const T top() const
    {
        assert(mSize > 0);
        return mDatas[0];
    }

    inline size_t size() const
    {
        return mSize;
    }

    inline bool empty() const
    {
        return mSize == 0;
    }
private:
    T* mDatas;
    size_t mSize;
    size_t mCapacity;
};
