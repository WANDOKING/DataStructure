#pragma once

#include <cstring>

class RingBuffer
{
public:
    RingBuffer(int bufferSize)
        : mCapacity(bufferSize)
    {
        mBuffer = new char[bufferSize];
    }

    // 현재 사용중인 용량 얻기
    inline int GetUseSize(void) const
    {
        return mSize;
    }

    // 현재 버퍼에 남은 용량 얻기
    inline int GetFreeSize(void) const
    {
        return mCapacity - mSize;
    }

    // 버퍼 포인터로 외부에서 한방에 쓸 수 있는 길이
    inline int GetDirectEnqueueSize(void) const
    {
        int freeSize = GetFreeSize();
        return (mCapacity - mRear) < freeSize ? (mCapacity - mRear) : freeSize;
    }

    // 버퍼 포인터로 외부에서 한방에 읽을 수 있는 길이
    inline int GetDirectDequeueSize(void) const
    {
        int useSize = GetUseSize();
        return (mCapacity - mFront) < useSize ? (mCapacity - mFront) : useSize;
    }

    bool Enqueue(const char* data, int dataSize)
    {
        int freeSize = GetFreeSize();
        int directEnqueueSize = GetDirectEnqueueSize();
        if (freeSize < dataSize)
        {
            return false;
        }

        char* enqueuePosition = mBuffer + mRear;

        if (directEnqueueSize >= dataSize)
        {
            memcpy(enqueuePosition, data, dataSize);
        }
        else
        {
            int firstEnqueueSize = directEnqueueSize;
            int secondEnqueueSize = dataSize - directEnqueueSize;
            memcpy(enqueuePosition, data, firstEnqueueSize);
            memcpy(mBuffer, data + firstEnqueueSize, secondEnqueueSize);
        }

        mSize += dataSize;
        mRear = (mRear + dataSize) % mCapacity;

        return true;
    }

    bool Dequeue(char* data, int dataSize)
    {
        int useSize = GetUseSize();
        int directDequeueSize = GetDirectDequeueSize();
        if (useSize < dataSize)
        {
            return false;
        }

        char* dequeuePosition = mBuffer + mFront;

        if (directDequeueSize >= dataSize)
        {
            memcpy(data, dequeuePosition, dataSize);
        }
        else
        {
            int firstDequeueSize = directDequeueSize;
            int secondDequeueSize = dataSize - directDequeueSize;
            memcpy(data, dequeuePosition, firstDequeueSize);
            memcpy(data + firstDequeueSize, mBuffer, secondDequeueSize);
        }

        mSize -= dataSize;
        mFront = (mFront + dataSize) % mCapacity;

        return true;
    }

    bool Peek(char* data, int dataSize) const
    {
        int useSize = GetUseSize();
        int directDequeueSize = GetDirectDequeueSize();
        if (useSize < dataSize)
        {
            return false;
        }

        char* peekPosition = mBuffer + mFront;

        if (directDequeueSize >= dataSize)
        {
            memcpy(data, peekPosition, dataSize);
        }
        else
        {
            int firstPeekSize = directDequeueSize;
            int secondPeekSize = dataSize - directDequeueSize;
            memcpy(data, peekPosition, firstPeekSize);
            memcpy(data + firstPeekSize, mBuffer, secondPeekSize);
        }

        return true;
    }

    inline void ClearBuffer(void)
    {
        mSize = 0;
        mRear = mFront;
    }

    // int DirectEnqueueSize(void);	
    // int DirectDequeueSize(void);
    // int MoveFront(int Size);
    // int MoveRear(int Size);
    // char* GetFrontBufferPtr(void);
    // char* GetRearBufferPtr(void);
private:
    char* mBuffer;
    int mCapacity;
    int mSize = 0;
    int mFront = 0;
    int mRear = 0;
};
