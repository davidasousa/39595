#include <vector>
#include <iostream>

void printVec(std::vector<int> vec) {
	for(auto it = vec.begin(); it != vec.end(); it++) {
		std::cout << *it;
	}
}

void changeVec(std::vector<int> vec) {
	vec.push_back(4);
}

int main() {
	std::vector<int> vec;
	changeVec(vec);
	printVec(vec); // If Should Print 4 If ChangeVec Uses A Ref
	return 0;

	// Nothing Was Printed -> Takes A Copy
}
