#include "hash_map.h"

int test2() {
	hash_map<int,int> map(5, 1.0, 2.0);

	map.insert(1,2);
	map.insert(5,2);
	map.insert(8,3);
	map.insert(-1,4);
	map.insert(9,0);

	int* keyArr = new int[map.get_size()];
	map.get_all_sorted_keys(keyArr);	

	if(keyArr[0] != -1 || keyArr[4] != 9) {
		return 1;
	}

	delete[] keyArr;
	return 0;
}
