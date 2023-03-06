#include <iostream>
#include "Serializer.h"

int main(void)
{
	Serializer serializer;

	printf("cpacity = %d, size = %d\n", serializer.GetCapacity(), serializer.GetUseSize());

	serializer << 5 << 8 << 'A' << 3.18f;
	printf("cpacity = %d, size = %d\n", serializer.GetCapacity(), serializer.GetUseSize());

	serializer.Clear();
	printf("cpacity = %d, size = %d\n", serializer.GetCapacity(), serializer.GetUseSize());

	serializer << LONG_MAX << 10.3f << 'F';
	printf("cpacity = %d, size = %d\n", serializer.GetCapacity(), serializer.GetUseSize());

	serializer.InsertByte("hello", 5);
	printf("cpacity = %d, size = %d\n", serializer.GetCapacity(), serializer.GetUseSize());

	char temp[6] = { 0, };
	serializer.GetByte(temp, 5);
	printf("temp = %s\n", temp);
	printf("cpacity = %d, size = %d\n", serializer.GetCapacity(), serializer.GetUseSize());

	long a;
	float b;
	char c;
	serializer >> c >> b >> a;
	printf("a = %d\n", a);
	printf("b = %f\n", b);
	printf("c = %c\n", c);
	printf("cpacity = %d, size = %d\n", serializer.GetCapacity(), serializer.GetUseSize());

	unsigned int A = 5;
	unsigned char B = 'B';
	serializer << A << B;
	printf("cpacity = %d, size = %d\n", serializer.GetCapacity(), serializer.GetUseSize());

	serializer >> B >> A;
	printf("A = %d\n", A);
	printf("B = %c\n", B);
	printf("cpacity = %d, size = %d\n", serializer.GetCapacity(), serializer.GetUseSize());
}
