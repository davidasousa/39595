#include <vector>

int main() {
	std::vector<int> vec;
	vec.push_back(3);

	int err1 = vec[1];
	int err2 = vec.at(1);

	// Runtime Error Thrown
}
