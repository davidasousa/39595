#include <iostream>
#include <cassert>

#include "hash_list.h"
#include "hash_map.h"

int test1(); // Insert & Remove
int test2(); // Copy Constructor & Assignment Operator
int test3(); // Get Value & Get All Keys
int test4(); // General Stress Testing

int main(int argc, char *argv[])
{
	assert(test1() == 0);
	assert(test2() == 0);
	assert(test3() == 0);
	assert(test4() == 0);

	return 0;
}
