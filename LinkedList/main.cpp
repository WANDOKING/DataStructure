#include <iostream>
#include <list>
#include <random>

#include "List.h"

enum class EListOperation
{
	CLEAR,
	ERASE,
	POP_BACK,
	POP_FRONT,
	PUSH_BACK,
	PUSH_FRONT,
	REMOVE,
	MAX_VALUE
};

int main(void)
{
	// randomTest
	if (true)
	{
		const int RANDOM_SEED = 150;
		const int TEST_COUNT = INT_MAX;

		std::list<int> listSTL;
		mds::list<int> listMDS;

		srand(RANDOM_SEED);
		int testCount = 0;
		while (testCount <= TEST_COUNT)
		{
			if (testCount % 100000 == 0) printf("testCount = %d\n", testCount);
			testCount++;

			// validation check
			assert(listSTL.size() == listMDS.size());
			assert(listSTL.empty() == listMDS.empty());
			if (listSTL.empty() == false)
			{
				assert(listSTL.back() == listMDS.back());
				assert(listSTL.front() == listMDS.front());
			}

			std::list<int>::iterator iteratorSTL = listSTL.begin();
			mds::list<int>::iterator iteratorMDS = listMDS.begin();

			while (true)
			{
				if (iteratorSTL == listSTL.end())
				{
					assert(iteratorMDS == listMDS.end());
					break;
				}

				assert(*iteratorSTL == *iteratorMDS);
				iteratorSTL++;
				iteratorMDS++;
			}

			// random operation
			EListOperation operation = (EListOperation)(rand() % (int)EListOperation::MAX_VALUE);
			int randomNumber;

			switch (operation)
			{
			case EListOperation::CLEAR:
				break;
			case EListOperation::ERASE:
				break;
			case EListOperation::POP_BACK:
				if (listMDS.empty() == false)
				{
					listMDS.pop_back();
					listSTL.pop_back();
				}
				break;
			case EListOperation::POP_FRONT:
				if (listMDS.empty() == false)
				{
					listMDS.pop_front();
					listSTL.pop_front();
				}
				break;
			case EListOperation::PUSH_BACK:
				randomNumber = rand();
				listMDS.push_back(randomNumber);
				listSTL.push_back(randomNumber);
				break;
			case EListOperation::PUSH_FRONT:
				randomNumber = rand();
				listMDS.push_front(randomNumber);
				listSTL.push_front(randomNumber);
				break;
			case EListOperation::REMOVE:
				break;
			default:
				assert(false);
			}
		}
	}

	printf("Test Passed\n");
	_CrtDumpMemoryLeaks();
}
