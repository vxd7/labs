#include <iostream>
#include <algorithm>
#include <string>

bool palindrom(std::string str) {
	std::string rev(str.begin(), str.end());
	std::reverse(rev.begin(), rev.end());
	if(str == rev) {
		return true;
	}

	return false;
}

int main() {
	const int START_NUM = 15951;
	std::string str;
	std::cin >> str;

	int num = std::stoi(str);

	if(palindrom(str) && num > START_NUM) {
		std::cout << (num - START_NUM) / 2;
	}

	return 0;
}
