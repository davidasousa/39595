#include <iostream>
#include <cassert>

int test1(); // Basics
int test2(); // Sort All Keys
int test3(); // Load Rebalancing

int main(int argc, char *argv[])
{
	assert(test1() == 0); 
	assert(test2() == 0); 
	assert(test3() == 0);
	return 0;
}
