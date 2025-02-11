#include <iostream>
#include "hash_map.h"

int test1() {
	hash_map map(5);

	if(map.get_capacity() != 5) {
		return 1;
	}
	if(map.get_size() != 0) {
		return 1;
	}

	// Inserting
	map.insert(4, 9.1);
	map.insert(3, 4.2);
	map.insert(-1, 1.2);

	if(map.get_capacity() != 5) {
		return 1;
	}
	if(map.get_size() != 3) {
		return 1;
	}

	// Removing
	if(map.remove(-1) == false) {
		return 1;
	}
	if(map.get_size() != 2) {
		return 1;
	}
	// 4 Not In Hash Map -> Return False
	if(map.remove(-1) == true) {
		return 1;
	}
	if(map.get_size() != 2) {
		return 1;
	}

	return 0;
}
