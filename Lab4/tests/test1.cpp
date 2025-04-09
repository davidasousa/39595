#include "../poly.h"

int test1() {
	// X + 1
	std::vector<std::pair<power, coeff>> in1 = {{1,1}, {0,1}};
	polynomial p1(in1.begin(), in1.end());
	// X + 2
	std::vector<std::pair<power, coeff>> in2 = {{1,1}, {0,2}};
	polynomial p2(in2.begin(), in2.end());
	// X^2 + X + 2
	std::vector<std::pair<power, coeff>> in3 = {{2, 1}, {1,1}, {0,2}};
	polynomial p3(in3.begin(), in3.end());
	// X^2 + 1
	std::vector<std::pair<power, coeff>> in4 = {{2, 1}, {0,1}};
	polynomial p4(in4.begin(), in4.end());
	
	// Testing Addition
	std::vector<std::pair<power, coeff>> ans1 = {{2, 1}, {1, 2}, {0, 4}};
	(p2 + p3).print();
	if((p2 + p3).canonical_form() != ans1) { return 1; }

	return 0;
}
