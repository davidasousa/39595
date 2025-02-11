#include "hash_map.h"
#include <iostream>

int test3() {
	hash_map map1(4);	

	map1.insert(1,2);
	map1.insert(2,3);
	map1.insert(3,4);
	map1.insert(4,5);
	map1.insert(5,6);
	map1.insert(6,7);
	map1.insert(-1,4);

	// Test Get Value
	if(!(map1.get_value(2).has_value())) {
		return 1;
	}
	if(map1.get_value(2).value() != 3) {
		return 1;
	}
	if(map1.get_value(0).has_value()) {
		return 1;
	}

	// Test Get All Keys
	int* keyarr = new int[map1.get_size()];
	map1.get_all_keys(keyarr);
	
	if(keyarr[0] != 4 || keyarr[1] != 1 || keyarr[2] != 5 || keyarr[3] != -1) {
		return 1;
	}
	delete[] keyarr;

	// Test Get Bucket Sizes
	size_t* bucketsizes = new size_t[map1.get_capacity()];
	map1.get_bucket_sizes(bucketsizes);
	if(bucketsizes[0] != 1 || bucketsizes[1] != 3) {
		return 1;
	}
	delete[] bucketsizes;

	return 0;
}
