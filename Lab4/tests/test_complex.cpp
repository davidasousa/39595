#include "../poly.h"
#include <iostream>

int test_complex() {
	// 0
	std::vector<std::pair<power, coeff>> in1 = {{0,0}};
	polynomial p1(in1.begin(), in1.end());

	std::vector<std::pair<power, coeff>> in2 = {{2, 1}, {0, 1}};
	polynomial p2(in2.begin(), in2.end());

	std::vector<std::pair<power, coeff>> ans1 = {{2, 1}, {0, 1}};
	if((p2 % p1).canonical_form() != ans1) { return 1; }

	std::vector<std::pair<power, coeff>> in3 = {{3, 1}, {2, 2}, {0, 4}};
	polynomial p3(in3.begin(), in3.end());

	std::vector<std::pair<power, coeff>> in4 = {{2, 1}, {0, 1}};
	polynomial p4(in4.begin(), in4.end());

	std::vector<std::pair<power, coeff>> ans2 = {{1, -1}, {0, 2}};
	std::cout << "Here\n----------\n";
	if((p3 % p4).canonical_form() != ans2) { return 1; }

	return 0;
}
