#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

void numbersFromBinary(string &str);
bool checkValidity(string &str);

int main(int argc, char* argv[])
{
	string input;

	if(argc > 1) {
		input = string(argv[1]);
	} else {
		cout << "Enter string: ";
		getline(cin, input);
	}

	if(!checkValidity(input)) {
		cerr << "Error! Input string is invalid!" << endl;
	} else {

		numbersFromBinary(input);
		cout << "Resulting string: " << input << endl;
	}

	return 0;
}

bool checkValidity(string &str)
{
	bool is_valid = false;
	for(int i = 0; i < str.size(); i++) {
		if(isalnum(str[i])) {
			is_valid = true;
			break;
		}
	}

	return is_valid;
}

void numbersFromBinary(string &str)
{
	
	bool no_nums = false;

	/* Get all the numbers */
	vector <int> nums;
	size_t pos = 0;

	for(size_t i = 0; i < str.size(); i++) {
		if(isdigit(str[i])) {
			int res = stoi(str.substr(i), &pos, 2);
			nums.push_back(res);

			i += pos;
		}
	}

	if(nums.size() == 0) {
		no_nums = true;
	}

	/* Create a local copy */
	string bkp = str;

	/* Clear the string */
	str.clear();

	/* Actually change now */
	int c = 0;

	if(no_nums) {
		for(size_t i = 0; i < bkp.size(); i++) {
			if(!isdigit(bkp[i])) {
				str.push_back(bkp[i]);
			}
		}
	} else {

		for(size_t i = 0; i < bkp.size(); i++) {

			if(!isdigit(bkp[i])) {
				str.push_back(bkp[i]);

			} else {
				/* Insert average number */
				str.insert(str.size(), to_string(nums[c]));
				c++;

				/* Skip all other numbers */
				while(isdigit(bkp[i + 1])) {
					i++;
				}

			}
		}

	}


}
