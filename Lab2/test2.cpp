#include "hash_map.h"
#include <iostream>

int test2() {
	hash_map map1(3);

	map1.insert(2, 4.5);
	map1.insert(5, 1.5);
	map1.insert(-1, -1.1);
	map1.insert(2, 0);

	// Testing Copy Constructor
	hash_map map2(map1);
	if(map2.get_size() != 3) {
		return 1;
	}
	
	// Testing Assignment Operator
	hash_map map3(6);
	map3.insert(1, 1.2);
	map3.insert(2, 4.1);
	map3.insert(5, 19.2);
	map3.insert(10, 2.5);
	
	if(map3.get_size() != 4) {
		return 1;
	}

	map3 = map2;

	if(map3.get_size() != 3) {
		return 1;
	}

	return 0;
}
