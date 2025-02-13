#include "hash_map.h"
#include <iostream>

int test3() {
	hash_map<int, float> map(209, 0.1, 0.05);

	int key = 0;
	for(size_t idx = 0; idx < 21; idx++) {
		map.insert(key++, 1.1);
	}
	
	if(map.get_capacity() != 1021 || map.get_size() != 21) {
		return 1;
	}

	map.remove(--key);

	if(map.get_capacity() != 209 || map.get_size() != 20) {
		return 1;
	}

	return 0;
}
