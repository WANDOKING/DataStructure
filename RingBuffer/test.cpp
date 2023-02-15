#include <iostream>
#include <cstring>
#include <random>
#include <Windows.h>

#include "RingBuffer.h"

int main(void)
{
    // string loop test
    {
        const int TEST_COUNT = 100'000;
        const int RING_BUFFER_SIZE = 83;

        const char* ptr_testString = "1234567890 abcdefghijklmnopqrstuvwxyz 1234567890 abcdefghijklmnopqrstuvwxyz 12345 ENDEND";
        int testStringIndex = 0;
        int testStringLength = static_cast<int>(strlen(ptr_testString));

        RingBuffer ringBuffer(RING_BUFFER_SIZE);
        char bufferForTest[RING_BUFFER_SIZE];

        srand(130U);

        for (int i = 0; i < TEST_COUNT; ++i)
        {
            int enqueueSize = rand() % (RING_BUFFER_SIZE / 2);

            if (enqueueSize > testStringLength - testStringIndex)
            {
                enqueueSize = testStringLength - testStringIndex;
            }

            ringBuffer.Enqueue(ptr_testString + testStringIndex, enqueueSize);
            ringBuffer.Dequeue(bufferForTest, enqueueSize);
            bufferForTest[enqueueSize] = '\0';
            printf(bufferForTest);

            testStringIndex = (testStringIndex + enqueueSize) % testStringLength;

            Sleep(300);
        }
    }
}
