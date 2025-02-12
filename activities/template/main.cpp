#include <iostream>
#include <string>
#include "complex.h"

// Step 1 Function
int 
minArray(const int* array, int length) {
	int min = array[0];
	for(int idx = 1; idx < length; idx++) {
		if(min > array[idx]) {
			min = array[idx];
		}
	}
	return min;
}

// Step 2 Function -> Templatized
template<typename T1>
T1 minArray(const T1* array, int length) {
	T1 min = array[0];
	for(int idx = 1; idx < length; idx++) {
		if(min > array[idx]) {
			min = array[idx];
		}
	}
	return min;
}

int 
main(int argc, char* argv[]) {
	// Step 1 Test
	int arr1[7] = {1,2,3,4,5,6,-1};
	int min1 = minArray(arr1, 7);
	std::cout << "Step 1" << std::endl;
	std::cout << min1 << std::endl;

	// Step 2 Test
	int step2int[7] = {1, 2, 3, 4, 5, 6, -1};
	float step2float[7] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, -1.1};
	char step2char[7] = {'a', 'A', 'b', 'B', 'c', 'C', 'd'};
	std::string step2string[7] = {"aa", "AA", "bb", "BB", "cc", "CC", "dd"};

	int min2int = minArray<int>(step2int, 7);
	float min2float = minArray<float>(step2float, 7);
	char min2char = minArray<char>(step2char, 7);
	std::string min2string = minArray<std::string>(step2string, 7);

	std::cout << "Step 2" << std::endl;
	std::cout << min2int << std::endl;
	std::cout << min2float << std::endl;
	std::cout << min2char << std::endl;
	std::cout << min2string << std::endl;

	// Step 4 Test
	complexNumber step3arr[2] = {complexNumber(1.2, -1.4), complexNumber(-1.41, -51.2)};
	complexNumber min3 = minArray<complexNumber>(step3arr, 2);
	std::cout << min3.real << " " << min3.im << std::endl;
			
	return 0;
}
