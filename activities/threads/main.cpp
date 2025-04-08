#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <sys/time.h> // For Timing

int find_sum(const std::vector<int>& vec) {
	int ans = 0;
	for(auto it : vec) { ans += it; }
	return ans;
}

int main(int argc, char* argv[]) {
	if(argc != 2) { return 1; }
	if(std::stoi(argv[1]) < 1) { return 1; }

	struct timeval start, end, diff;

	std::vector<std::thread> threads(std::stoi(argv[1])); 
	std::vector<int> nums(100000, 1); // Large Enough To See Threading Benifit

	// Timing Concurrent
	
	gettimeofday(&start, nullptr);

	for(auto it = threads.begin(); it != threads.end(); it++) { 
		*it = std::thread(find_sum, nums);
	}

	for(auto it = threads.begin(); it != threads.end(); it++) { 
		(*it).join();
	}

	gettimeofday(&end, nullptr);
	timersub(&end, &start, &diff);
	std::cout << "Total Parallel Time: " << diff.tv_usec;
	std::cout << std::endl;

	// Timing Sequential

	gettimeofday(&start, nullptr);

	for(int idx = 0; idx < threads.size(); idx++) {
		find_sum(nums);
	}	

	gettimeofday(&end, nullptr);
	timersub(&end, &start, &diff);
	std::cout << "Total Sequential Time: " << diff.tv_usec;
	std::cout << std::endl;

	return 0;
}
