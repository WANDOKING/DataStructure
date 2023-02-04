#include <iostream>
#include <random>
#include <queue>

#include "FixedPriorityQueue.h"

int main(void)
{
    srand((unsigned int)time(nullptr));

    {
        std::priority_queue<int> stl;
        FixedPriorityQueue<int> pq(100000);

        for (int i = 0; i < 100000; ++i)
        {
            const int PUSH = 0;
            const int EMPTY = 1;
            const int SIZE = 2;
            const int TOP = 3;
            const int POP = 4;
            const int MAX = 5;

            int testCase = rand() % MAX;

            int randomNumber;
            switch (testCase)
            {
            case PUSH:
                randomNumber = rand();
                stl.push(randomNumber);
                pq.push(randomNumber);
                break;
            case EMPTY:
                assert(stl.empty() == pq.empty());
                break;
            case SIZE:
                assert(stl.size() == pq.size());
                break;
            case TOP:
                if (stl.empty() == true && pq.empty() == true)
                {
                    break;
                }
                assert(stl.top() == pq.top());
                break;
            case POP:
                if (stl.empty() == true && pq.empty() == true)
                {
                    break;
                }
                stl.pop();
                pq.pop();
                break;
            default:
                assert(false);
            }
        }
    }

    _CrtDumpMemoryLeaks();
    std::cout << "test passed\n";
}
