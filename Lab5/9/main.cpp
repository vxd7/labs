#include <iostream>
#include <algorithm> //for_each, transform
#include <vector>
#include <numeric> //accumulate

void func(int i) {
	std::cout << ' ' << i*i;
}

int mkFunc(int i) {
	return i*i;
}

int main() {
	const int START_NUM = 1;
	const int END_NUM = 15;

	std::vector<int> nums;
	nums.resize(END_NUM);
	for(size_t i = 0; i < END_NUM; ++i) {
		nums[i] = START_NUM + i;
	}

	std::cout << "Squares of the range [" << START_NUM << ", " << END_NUM << "]:";
	std::for_each(nums.begin(), nums.end(), func);
	std::cout << std::endl;
	
	std::vector<int> res;
	res.resize(END_NUM);

	std::vector<int>::iterator it = res.begin();
	std::transform(nums.begin(), nums.end(), it, mkFunc);

	std::cout << "Sum of squares: " << std::accumulate(res.begin(), res.end(), 0);

	return 0;
}
