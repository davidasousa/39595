#include "../poly.h"
#include <iostream>

int test_canonical() {
	// 0
	std::vector<std::pair<power, coeff>> in1 = {{0,0}};
	polynomial p1(in1.begin(), in1.end());
	polynomial p2;

	// x^2 + 7x^4 + 1
	std::vector<std::pair<power, coeff>> in2 = {{2, 1}, {4, 7}, {0, 1}};
	polynomial p3(in2.begin(), in2.end());

	std::vector<std::pair<power, coeff>> in3 = {{2, 1}, {4, 7}, {2, 3}, {0, 1}};
	polynomial p4(in3.begin(), in3.end());

	std::vector<std::pair<power, coeff>> in4 = {{2, 1}, {4, 7}, {3, 0}, {0, 1}};
	polynomial p5(in4.begin(), in4.end());

	std::vector<std::pair<power, coeff>> in5 = {{3, 0}, {0, 2}};
	polynomial p6(in5.begin(), in5.end());

	std::vector<std::pair<power, coeff>> in6 = {{0, 5}, {0, 2}, {1, 1}, {0, 8}};
	polynomial p7(in6.begin(), in6.end());

	// Testing Canonical
	std::vector<std::pair<power, coeff>> ans1 = {{0, 0}};
	if(p1.canonical_form() != ans1) { return 1; }
	if(p2.canonical_form() != ans1) { return 1; }
	if(p2.canonical_form().size() != 1) { return 1; }

	std::vector<std::pair<power, coeff>> ans2 = {{4, 7}, {2, 1}, {0,1}};
	if(p3.canonical_form() != ans2) { return 1; }
	if(p5.canonical_form() != ans2) { return 1; }

	std::vector<std::pair<power, coeff>> ans4 = {{0, 2}};
	if(p6.canonical_form() != ans4) { return 1; }

	// Testing Merging
	std::vector<std::pair<power, coeff>> ans3 = {{4, 7}, {2, 4}, {0,1}};
	if(p4.canonical_form() != ans3) { return 1; }

	std::vector<std::pair<power, coeff>> ans5 = {{1, 1}, {0, 15}};
	if(p7.canonical_form() != ans5) { return 1; }

	return 0;
}
