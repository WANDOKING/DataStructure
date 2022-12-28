#include <cassert>
#include <iostream>

// define USE_STD to use STL list.
// the way to use this list is the same as std::list container
//#define USE_STD

#ifdef USE_STD
#include <list>
using namespace std;
#else
#include "List.h"
using namespace mds;
#endif

int main(void)
{
	// Linekd List test for std::string
	{
		list<std::string> strList;

		strList.push_back("hello world");
		strList.push_front("ok");

		assert(strList.size() == 2);
		assert(strList.front() == "ok");
		assert(strList.back() == "hello world");

		// clear
		strList.clear();
		assert(strList.size() == 0);

		strList.push_back("who are you");
		strList.push_back("we can go");
		strList.push_back("tree");
		strList.push_front("coffee");

		// traversal
		assert(strList.size() == 4);
		auto it = strList.begin();
		assert(*it == "coffee");
		++it;
		assert(*it == "who are you");
		++it;
		assert(*it == "we can go");
		++it;
		assert(*it == "tree");
		++it;
		assert(it == strList.end());

		// remove
		strList.remove("we can go");
		strList.push_back("hood");
		strList.remove("tree");

		assert(strList.size() == 3);
		auto it2 = strList.begin();
		assert(*it2 == "coffee");
		it2++;
		assert(*it2 == "who are you");
		it2++;
		assert(*it2 == "hood");
		it2++;
		assert(it2 == strList.end());

		// clear
		strList.clear();
		assert(strList.size() == 0);

		// erase
		strList.push_back("its");
		strList.push_back("beginning");
		strList.push_back("to");
		strList.push_back("look");
		strList.push_back("a");
		strList.push_back("lot");
		strList.push_back("like");
		strList.push_back("christmas");
		assert(strList.size() == 8);
		
		for (auto it = strList.begin(); it != strList.end(); ++it)
		{
			if (*it == "to")
			{
				it = strList.erase(it);
				it = strList.erase(it);
			}

			if (*it == "lot")
			{
				it = strList.erase(it);
				it = strList.erase(it);
			}
		}

		assert(strList.size() == 4);
		auto it3 = strList.begin();
		assert(*it3 == "its");
		it3++;
		assert(*it3 == "beginning");
		it3++;
		assert(*it3 == "a");
		it3++;
		assert(*it3 == "christmas");
		it3++;
		assert(it3 == strList.end());
	}

	std::cout << "test pass\n";
	_CrtDumpMemoryLeaks();
}
