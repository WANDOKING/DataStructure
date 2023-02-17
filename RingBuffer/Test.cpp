#include <iostream>
#include <Windows.h>
#include <cstring>
#include <cassert>

#include "RingBuffer.h"

int main(void)
{
	// string loop test
	if (true)
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

	// 전체적인 마구잡이 테스트 - version 1.0.0 에서 작성되었음
	if (false)
	{
		const int TEST_BUFFER_SIZE = 200; // 변경하면서 테스트하진 말 것
		const int RING_BUFFER_SIZE = 50; // 변경하면서 테스트하진 말 것
		char testBuffer[TEST_BUFFER_SIZE];
		RingBuffer ringBuffer(RING_BUFFER_SIZE);
		bool returnValue;

		assert(ringBuffer.GetFreeSize() == RING_BUFFER_SIZE);
		assert(ringBuffer.GetUseSize() == 0);

		ringBuffer.ClearBuffer();
		assert(ringBuffer.GetFreeSize() == RING_BUFFER_SIZE);
		assert(ringBuffer.GetUseSize() == 0);

		strcpy_s(testBuffer, "hello");
		returnValue = ringBuffer.Enqueue(testBuffer, 5);
		assert(returnValue == true);
		assert(ringBuffer.GetFreeSize() == RING_BUFFER_SIZE - 5);
		assert(ringBuffer.GetUseSize() == 5);

		returnValue = ringBuffer.Peek(testBuffer, 5);
		assert(strncmp(testBuffer, "hello", 5) == 0);
		assert(returnValue == true);
		assert(ringBuffer.GetFreeSize() == RING_BUFFER_SIZE - 5);
		assert(ringBuffer.GetUseSize() == 5);

		returnValue = ringBuffer.Dequeue(testBuffer, 5);
		assert(strncmp(testBuffer, "hello", 5) == 0);
		assert(returnValue == true);
		assert(ringBuffer.GetFreeSize() == RING_BUFFER_SIZE);
		assert(ringBuffer.GetUseSize() == 0);

		strcpy_s(testBuffer, "we will we will rock you");
		returnValue = ringBuffer.Enqueue(testBuffer, 24);
		assert(returnValue == true);
		assert(ringBuffer.GetFreeSize() == RING_BUFFER_SIZE - 24);
		assert(ringBuffer.GetUseSize() == 24);

		returnValue = ringBuffer.Enqueue(testBuffer, 24);
		assert(returnValue == true);
		assert(ringBuffer.GetFreeSize() == RING_BUFFER_SIZE - 48);
		assert(ringBuffer.GetUseSize() == 48);

		returnValue = ringBuffer.Enqueue(testBuffer, 24);
		assert(returnValue == false);
		assert(ringBuffer.GetFreeSize() == RING_BUFFER_SIZE - 48);
		assert(ringBuffer.GetUseSize() == 48);

		returnValue = ringBuffer.Peek(testBuffer, 7);
		assert(strncmp(testBuffer, "we will", 7) == 0);
		assert(returnValue == true);
		assert(ringBuffer.GetFreeSize() == RING_BUFFER_SIZE - 48);
		assert(ringBuffer.GetUseSize() == 48);

		returnValue = ringBuffer.Dequeue(testBuffer, 10);
		assert(strncmp(testBuffer, "we will we", 10) == 0);
		assert(returnValue == true);
		assert(ringBuffer.GetFreeSize() == RING_BUFFER_SIZE - 38);
		assert(ringBuffer.GetUseSize() == 38);

		returnValue = ringBuffer.MoveFront(5);
		assert(returnValue == true);
		assert(ringBuffer.GetFreeSize() == RING_BUFFER_SIZE - 33);
		assert(ringBuffer.GetUseSize() == 33);

		ringBuffer.ClearBuffer();
		assert(ringBuffer.GetFreeSize() == RING_BUFFER_SIZE);
		assert(ringBuffer.GetUseSize() == 0);
	}

	printf("Test Passed");
}