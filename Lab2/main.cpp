#include <iostream>
#include <cassert>

int test1();

int main(int argc, char *argv[])
{
	assert(test1() == 0);
	return 0;
}
