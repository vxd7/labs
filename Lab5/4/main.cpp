#include <iostream>
#include <algorithm>
#include <vector>

typedef std::string::iterator strIter;


int main() {
	std::string str1, str2;
	std::getline(std::cin, str1);
	std::getline(std::cin, str2);

	std::sort(str1.begin(), str1.end());

	strIter uniqElems = std::unique(str1.begin(), str1.end());
	str1.erase(uniqElems, str1.end());

	std::vector<char> res;
	strIter str1Iterator = str1.begin();
	while(str1Iterator != str1.end()) {
		strIter tmpIter = std::find(str2.begin(), str2.end(), *str1Iterator);
		if(tmpIter != str2.end()) {
			res.push_back(*str1Iterator);
		}
		++str1Iterator;
	}

	if(res.size() == 0) {
		std::cout << "There are no identical symbols in the strings";
	} else {
		std::cout << "There are " << res.size() << " identical symbols in the strings:" << std::endl;
		std::vector<char>::iterator it = res.begin();
		while(it != res.end()) {
			std::cout << (*it) << ' ';
			++it;
		}
	}

	std::cout << std::endl;

	return 0;
	
}
