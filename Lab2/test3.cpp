#include "hash_map.h"
#include <iostream>

int test3() {
	hash_map<int, int> map(209, 0.1, 0.05);

	int key = 0;
	int val = 0;

	if(map.get_capacity() != 209 || map.get_size() != 0) {
		return 1;
	}

	for(size_t idx = 0; idx < 21; idx++) {
		map.insert(key++, val--);
	}
	
	if(map.get_capacity() != 1021 || map.get_size() != 21) {
		return 1;
	}

	map.remove(--key);

	if(map.get_capacity() != 209 || map.get_size() != 20) {
		return 1;
	}

	if(map.get_value(3).has_value() == false || map.get_value(3).value() != -3) {
		return 1;
	}

	// Testing Char To Int
	hash_map<char, int> cmap(194, 0.1, 0.05);

	char key2 = 'A';

	for(size_t idx = 0; idx < 20; idx++) {
		cmap.insert(key2++, idx);
	}
	
	if(cmap.get_value('D').value() != 3) { return 1; }
	if(cmap.get_capacity() != 209) { return 1;} 
	
	return 0;
}
