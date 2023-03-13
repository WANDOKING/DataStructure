#include <iostream>

#include "ObjectFreeList.h"

int main(void)
{
	if (true) 
	{
		ObjectFreeList<int*> ofl;
		printf("capacity = %d, size = %d\n", ofl.GetCapacity(), ofl.GetSize());

		int* ptr_num1 = ofl.Alloc();
		printf("capacity = %d, size = %d\n", ofl.GetCapacity(), ofl.GetSize());

		int* ptr_num2 = ofl.Alloc();
		printf("capacity = %d, size = %d\n", ofl.GetCapacity(), ofl.GetSize());

		int* ptr_num3 = ofl.Alloc();
		printf("capacity = %d, size = %d\n", ofl.GetCapacity(), ofl.GetSize());

		*ptr_num1 = 5;
		*ptr_num2 = 17;
		*ptr_num3 = 23;

		ofl.Free(ptr_num1);
		printf("capacity = %d, size = %d\n", ofl.GetCapacity(), ofl.GetSize());

		ofl.Free(ptr_num2);
		printf("capacity = %d, size = %d\n", ofl.GetCapacity(), ofl.GetSize());

		ofl.Free(ptr_num3);
		printf("capacity = %d, size = %d\n", ofl.GetCapacity(), ofl.GetSize());

		int* ptr_num4 = ofl.Alloc();
		int* ptr_num5 = ofl.Alloc();
		int* ptr_num6 = ofl.Alloc();
		printf("%d\n", *ptr_num4);
		printf("%d\n", *ptr_num5);
		printf("%d\n", *ptr_num6);

		printf("capacity = %d, size = %d\n", ofl.GetCapacity(), ofl.GetSize());
	}

	{
		ObjectFreeList<int*> ofl(5);
		printf("capacity = %d, size = %d\n", ofl.GetCapacity(), ofl.GetSize());

		int* ptr_num1 = ofl.Alloc();
		int* ptr_num2 = ofl.Alloc();
		int* ptr_num3 = ofl.Alloc();
		int* ptr_num4 = ofl.Alloc();
		int* ptr_num5 = ofl.Alloc();
		int* ptr_num6 = ofl.Alloc();
		printf("capacity = %d, size = %d\n", ofl.GetCapacity(), ofl.GetSize());

		ofl.Free(ptr_num1);
		ofl.Free(ptr_num2);
		ofl.Free(ptr_num3);
		printf("capacity = %d, size = %d\n", ofl.GetCapacity(), ofl.GetSize());

		int* ptr_num7 = ofl.Alloc();
		int* ptr_num8 = ofl.Alloc();
		int* ptr_num9 = ofl.Alloc();
		printf("capacity = %d, size = %d\n", ofl.GetCapacity(), ofl.GetSize());
	}

	_CrtDumpMemoryLeaks();
}
