#include <iostream>
#include <vector>

template<typename T>
typename std::vector<T>::iterator findIf(std::vector<T>& vec, bool (*predicate)(T)) {
	for(typename std::vector<T>::iterator it = vec.begin(); it != vec.end(); it++) {
		if(predicate(*it)) { return it; }
	}
	return {};
}

bool isOdd(int arg) {
	if(arg % 2 == 1) { return true; }
	else { return false; }
}

bool isDavid(std::string arg) {
	if(arg == "David") { return true; }
	else { return false; }
}

int main(int argc, char* argv[]) {
	std::vector<int> testInts = {1,2,3,4,5,6};
	std::vector<std::string> testNames = {"Joe","Sue","David"};

	std::vector<int>::iterator p = findIf(testInts, isOdd);
	std::vector<std::string>::iterator q = findIf(testNames, isDavid);

	std::cout << "First Odd Number: " << *p << std::endl;
	std::cout << "Name: " << *q << std::endl;
	return 0;
}
