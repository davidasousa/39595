#include "hash_map.h"

int test1() {
	hash_map<float, int> map(4, 1.0, 2.0);

	if(map.get_size() != 0 || map.get_capacity() != 4) {
		return 1;
	}

	map.insert(12.14, 2);
	if(map.get_size() != 1 || map.get_capacity() != 4) {
		return 1;
	}
	if(map.get_value(12.14).has_value() == false) {
		return 1;
	}
	if(map.get_value(12.14).value() != 2) {
		return 1;
	}

	size_t* bucketArr = new size_t[map.get_capacity()];
	map.get_bucket_sizes(bucketArr);		
	delete[] bucketArr;

	float* keyArr = new float[map.get_size()];
	map.get_all_keys(keyArr);
	delete[] keyArr;

	map.insert(32.1, 41);
	map.insert(17.4, 61);
	map.insert(1.4, 14);

	// Testing Copy Constructor & Assignment Operator
	hash_map<float, int> map2(map); // Copy Constructor
	map2 = map2; // Self Assignment

	hash_map<float, int> map3(1, 1.0, 2.0);
	map3 = map2; // Assignment Operator

	if(map2.get_size() != 4 || map3.get_size() != 4) {
		return 1;
	}

	map3.remove(17.4);
	if(map2.get_size() != 4 || map3.get_size() != 3) {
		return 1;
	}

	return 0;
}
