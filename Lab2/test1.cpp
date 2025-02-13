#include "hash_map.h"

int test1() {
	hash_map<float, int> map(4, 1.0, 2.0);

	if(map.get_size() != 0 || map.get_capacity() != 4) {
		return 1;
	}

	return 0;
}
