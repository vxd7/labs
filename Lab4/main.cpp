#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

void parseString(const std::string& src, std::vector<std::set<std::string> >& dst);
void strLastLetter(std::vector<std::string>& stok, std::vector<std::string>& res, char letter);
bool cmp(std::set<std::string>& a, std::set<std::string>& b);
int main() {
	std::string src = "this is the mait that lay in the house that jack built";
	std::vector<std::set<std::string> > dst;

	parseString(src, dst);
	std::sort(dst.begin(), dst.end(), cmp);

	return 0;
}
bool cmp(std::set<std::string>& a, std::set<std::string>& b) {
	std::string first, sec;
	first = (*a.begin());
	sec = (*b.begin());

	char let1, let2;
	let1 = first.at(first.length() - 1);
	let2 = sec.at(sec.length() - 1);
	if (let1 < let2) {
		return true;
	}
	else {
		return false;
	}
}
void strLastLetter(std::vector<std::string>& stok, std::vector<std::string>& res, char letter) {
	std::vector<std::string>::iterator it = stok.begin();
	for (it; it != stok.end(); ++it) {
		std::string tmp = (*it);
		if (tmp.at(tmp.length() - 1) == letter) {
			res.push_back(tmp);
		}
	}
	std::vector<std::string>::iterator resIter = res.begin();
	for (resIter; resIter != res.end(); ++resIter) {
		stok.erase(std::remove(stok.begin(), stok.end(), (*resIter)), stok.end());

	}
}
void parseString(const std::string& src, std::vector<std::set<std::string> >& dst) {
	std::stringstream sstr(src);
	std::string token;

	std::vector<std::string> stok;
	while (std::getline(sstr, token, ' ')) {
		stok.push_back(token);
	}

	while (!stok.empty()) {
		std::vector<std::string> let;
		std::string tmp = (*(stok.begin()));
		char letter = tmp.at(tmp.length() - 1);

		strLastLetter(stok, let, letter);
		
		std::set < std::string > tmpSet;
		for (std::vector<std::string>::iterator it = let.begin(); it != let.end(); ++it) {
			std::string tmp = (*it);
			tmpSet.insert(tmp);
		
		}
		dst.push_back(tmpSet);

	}
}