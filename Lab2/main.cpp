#include <iostream>
#include <cassert>

int test1(); // Insert & Remove
int test2(); // Copy Constructor & Assignment Operator
int test3(); // Get Value & Get All Keys
int test4(); // General Stress Testing
int test5(); // Test All Keys
int test6();
int test7();

int main(int argc, char *argv[])
{
	assert(test1() == 0);
	assert(test2() == 0);
	assert(test3() == 0);
	assert(test4() == 0);
	assert(test5() == 0);
	assert(test6() == 0);
	assert(test7() == 0);

	return 0;
}
