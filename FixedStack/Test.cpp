#include <iostream>
#include <cassert>
#include <stack>
#include <string>
#include "FixedStack.h"

int main(void)
{
	{
		mds::FixedStack<int> fs(5);

		assert(fs.empty() == true);

		fs.push(10);
		fs.push(2);
		fs.push(123);
		fs.push(1624);
		fs.push(235);

		assert(fs.empty() == false);
		assert(fs.size() == 5);

		assert(fs.top() == 235);
		fs.pop();
		assert(fs.top() == 1624);
		fs.pop();
		assert(fs.top() == 123);
		fs.pop();
		assert(fs.top() == 2);
		fs.pop();
		assert(fs.top() == 10);
		fs.pop();

		assert(fs.empty() == true);
	}
	
	{
		mds::FixedStack<std::string> s(3);

		s.push("this");
		s.push("is");
		s.push("ok");

		assert(s.top() == "ok");
		s.pop();

		assert(s.top() == "is");
		s.pop();

		s.push("why");
		assert(s.top() == "why");
		assert(s.empty() == false);
		assert(s.size() == 2);

		s.pop();
		s.pop();

		assert(s.empty() == true);
	}

	_CrtDumpMemoryLeaks();
}
