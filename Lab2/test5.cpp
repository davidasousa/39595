#include "hash_map.h"

int test5() {
	hash_map map(7);

	map.insert(1, 5.3);
	map.insert(4, 5.2);
	map.insert(14, 51.2);

	if(map.get_size() != 3) {
		return 1;
	}
	
	int* keyarr = new int[map.get_size()];
	map.get_all_keys(keyarr);

	if(keyarr[0] != 14 || keyarr[1] != 1 || keyarr[2] != 4) {
		return 1;
	}
	delete[] keyarr;

	size_t* bucketsizes = new size_t[map.get_capacity()];
	map.get_bucket_sizes(bucketsizes);
	if(bucketsizes[0] != 1 || bucketsizes[1] != 1 || bucketsizes[2] != 0) {
		return 1;
	}
	delete[] bucketsizes;

	map.insert(-1, 2.1);
	map.insert(-2, 2.1);
	map.insert(-3, 2.1);
	map.insert(-4, 2.1);
	map.insert(-5, 2.1);
	map.insert(-6, 2.1);
	map.insert(-7, 2.1);

	bucketsizes = new size_t[map.get_capacity()];
	map.get_bucket_sizes(bucketsizes);
	if(
		bucketsizes[0] != 2 || bucketsizes[1] != 2 || bucketsizes[2] != 1 ||
		bucketsizes[3] != 1 || bucketsizes[4] != 2 || bucketsizes[5] != 1 ||
		bucketsizes[6] != 1
		) {
		return 1;
	}
	delete[] bucketsizes;

	return 0;
}
