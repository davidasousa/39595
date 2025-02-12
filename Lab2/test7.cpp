#include "hash_map.h"
#include <iostream>

int test7() {
	hash_map a(4);
	hash_map b(1);
	hash_map c(3);

	a.insert(4, 12.4);
	a.insert(2, 4121.1);
	a.insert(-4, 112);

	// Testing Self Assignment
	a = a;
	c = b = a;
	
	if(a.get_size() != 3 || b.get_size() != 3 || c.get_size() != 3) {
		return 1;
	}
	if(c.get_value(-4).has_value() == false) {
		return 1;
	}
	if(c.get_value(-4).value() != 112) {
		return 1;
	}

	return 0;
}
