#include "../poly.h"
#include <iostream>

int test_addition() {
	// 0
	std::vector<std::pair<power, coeff>> in1 = {{0,0}};
	polynomial p1(in1.begin(), in1.end());
	polynomial p2;

	std::vector<std::pair<power, coeff>> ans1 = {{0, 1}};
	if((p1 + 1).canonical_form() != ans1) { return 1; }
	if((1 + p1).canonical_form() != ans1) { return 1; }
	if((p2 + 1).canonical_form() != ans1) { return 1; }
	if((1 + p2).canonical_form() != ans1) { return 1; }

	std::vector<std::pair<power, coeff>> in2 = {{2, 1}};
	polynomial p3(in2.begin(), in2.end());

	std::vector<std::pair<power, coeff>> ans2 = {{2, 1}, {0, 3}};
	if((3 + p3).canonical_form() != ans2) { return 1; }
	if((p3 + 3).canonical_form() != ans2) { return 1; }

	std::vector<std::pair<power, coeff>> ans3 = {{2, 1}};
	if((p3 + 0).canonical_form() != ans3) { return 1; }

	return 0;
}
