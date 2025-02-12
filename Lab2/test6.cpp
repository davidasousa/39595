#include "hash_map.h"

int test6() {
	hash_map map(3);
	
	map.insert(0, 1);
	map.insert(3, 2);
	map.insert(6, 3);
	map.insert(2, 4);

	int* keyarr = new int[map.get_size()];
	size_t* buckets = new size_t[map.get_capacity()];

	map.get_all_keys(keyarr);
	map.get_bucket_sizes(buckets);
	
	if(keyarr[0] != 0) { return 1; }
	if(keyarr[1] != 3) { return 1; }
	if(keyarr[2] != 6) { return 1; }
	if(keyarr[3] != 2) { return 1; }

	if(buckets[0] != 3) { return 1; }
	if(buckets[1] != 0) { return 1; }
	if(buckets[2] != 1) { return 1; }

	delete[] keyarr;
	delete[] buckets;
	
	if(map.get_size() != 4 || map.get_capacity() != 3) {
		return 1;
	}

	if(map.remove(3) == false) { return 1; }

	keyarr = new int[map.get_size()];
	buckets = new size_t[map.get_capacity()];
	map.get_all_keys(keyarr);
	map.get_bucket_sizes(buckets);

	if(keyarr[0] != 0) { return 1; }
	if(keyarr[1] != 6) { return 1; }
	if(keyarr[2] != 2) { return 1; }

	if(buckets[0] != 2) { return 1; }
	if(buckets[1] != 0) { return 1; }
	if(buckets[2] != 1) { return 1; }

	delete[] keyarr;
	delete[] buckets;

	if(map.get_size() != 3) { return 1; }

	// Empty Map

	hash_map empty_map(0);

	if(empty_map.get_size() != 0 || empty_map.get_capacity() != 0) {
		return 1;
	}

	int* empty_keys = new int[empty_map.get_size()];	
	size_t* empty_bucket = new size_t[empty_map.get_capacity()];	

	empty_map.get_all_keys(empty_keys);
	empty_map.get_bucket_sizes(empty_bucket);

	delete[] empty_keys;
	delete[] empty_bucket;

	return 0;
}
