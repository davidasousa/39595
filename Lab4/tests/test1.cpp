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
	// X^2
	std::vector<std::pair<power, coeff>> in5 = {{2, 1}};
	polynomial p5(in5.begin(), in5.end());
	// X
	std::vector<std::pair<power, coeff>> in6 = {{1, 1}};
	polynomial p6(in6.begin(), in6.end());
	// 0
	std::vector<std::pair<power, coeff>> in7 = {{0, 0}};
	polynomial p7(in7.begin(), in7.end());
	
	// Testing Addition
	std::vector<std::pair<power, coeff>> ans1 = {{1, 2}, {0, 3}};
	if((p1 + p2).canonical_form() != ans1) { return 1; }

	std::vector<std::pair<power, coeff>> ans2 = {{2, 1}, {1, 2}, {0, 3}};
	if((p1 + p3).canonical_form() != ans2) { return 1; }
	if((p3 + p1).canonical_form() != ans2) { return 1; }

	std::vector<std::pair<power, coeff>> ans3 = {{2, 1}, {1, 1}, {0, 2}};
	if((p1 + p4).canonical_form() != ans3) { return 1; }

	std::vector<std::pair<power, coeff>> ans4 = {{1, 1}, {0, 7}};
	if((p1 + 6).canonical_form() != ans4) { return 1; }

	std::vector<std::pair<power, coeff>> ans5 = {{2, 1}, {1, 1}};
	if((p5 + p6).canonical_form() != ans5) { return 1; }
	
	// Testing Multiplication
	std::vector<std::pair<power, coeff>> ans6 = {{2, 1}, {1, 3}, {0, 2}};
	if((p1 * p2).canonical_form() != ans6) { return 1; }
	if((p2 * p1).canonical_form() != ans6) { return 1; }

	std::vector<std::pair<power, coeff>> ans7 = {{3, 1}};
	if((p5 * p6).canonical_form() != ans7) { return 1; }
	if((p6 * p5).canonical_form() != ans7) { return 1; }


	return 0;
}
