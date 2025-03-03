#include <vector>
#include <iostream>

int main() {
	std::vector<std::vector<int>> vec;
	for(int idx = 0; idx < 2; idx++) {
		vec.push_back(std::vector<int>()); // () Needed For Default Vec Constructor
		for(int jdx = 0; jdx < 3; jdx++) {
			vec[idx].push_back(3 * idx + jdx);	
		}
	}

	for(int idx = 0; idx < 2; idx++) {
		for(int jdx = 0; jdx < 3; jdx++) {
			std::cout << vec.at(idx).at(jdx);
		}
	}

	std::vector<std::vector<int>> vec2;
	for(int idx = 0; idx < 2; idx++) {
		vec2.push_back(std::vector<int>());
		for(int jdx = 0; jdx < 3; jdx++) {
			vec2[idx].push_back(3 * idx + jdx);	
		}
	}

	std::cout << std::endl;
	for(int idx = 0; idx < 2; idx++) {
		for(int jdx = 0; jdx < 3; jdx++) {
			vec[idx][jdx] += vec2[idx][jdx];
			std::cout << vec.at(idx).at(jdx);
		}
	}
	
	return 0;
}
