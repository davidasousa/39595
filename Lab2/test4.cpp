#include "hash_map.h"

int test4() {
	hash_map map1(1);
	hash_map map2 = map1; // Assignment Operator
	hash_map map3(map1);

	if(map2.get_size() != 0 || map3.get_size() != 0) {
		return 1;
	}
	if(map2.get_capacity() != 1 || map3.get_capacity() != 1) {
		return 1;
	}

	// Checking Non Present Key
	if(map2.get_value(4).has_value() || map3.get_value(4).has_value()) {
		return 1;
	}
	
	// Inserting To Original Hashmap 
	map1.insert(4, 1.2);
	map1.insert(5, 1.2);

	if(map2.get_value(4).has_value() || map3.get_value(4).has_value()) {
		return 1;
	}

	if(map1.get_size() != 2) {
		return 1;
	}

	int* keyarr = new int[map1.get_size()];
	map1.get_all_keys(keyarr);
	
	if(keyarr[0] != 4 || keyarr[1] != 5) {
		return 1;
	}
	delete[] keyarr;

	// Valid Remove
	if(map1.remove(1) != false || map1.get_size() != 2) {
		return 1;
	}
	if(map1.remove(4) != true || map1.get_size() != 1) {
		return 1;
	}

	map2 = map1;
	if(map2.get_size() != 1) { 
		return 1;
	}

	map2.insert(5, 1.4);

	if(map2.get_size() != 1) { 
		return 1;
	}
	
	return 0;
}
