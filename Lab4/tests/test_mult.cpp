#include "../poly.h"
#include <iostream>

int test_mult() {
	std::vector<std::pair<power, coeff>> in1 = {{0,0}};
	polynomial p1(in1.begin(), in1.end());
	polynomial p2;

	std::vector<std::pair<power, coeff>> ans1 = {{0, 0}};
	if((p1 * 1).canonical_form() != ans1) { return 1; }
	if((1 * p1).canonical_form() != ans1) { return 1; }
	if((p2 * 1).canonical_form() != ans1) { return 1; }
	if((1 * p2).canonical_form() != ans1) { return 1; }
	if((0 * p2).canonical_form() != ans1) { return 1; }

	std::vector<std::pair<power, coeff>> in2 = {{2, 1}, {3, 5}, {0, 0}};
	polynomial p3(in2.begin(), in2.end());

	std::vector<std::pair<power, coeff>> ans2 = {{3, 20}, {2, 4}};
	if((p3 * 4).canonical_form() != ans2) { return 1; }

	return 0;
}
