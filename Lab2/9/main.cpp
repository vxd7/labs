#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

void averageNumbers(string &str);
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

		averageNumbers(input);
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

void averageNumbers(string &str)
{
	bool no_nums = false;

	/* Get all the numbers */
	vector <int> nums;
	size_t pos = 0;

	for(size_t i = 0; i < str.size(); i++) {
		if(isdigit(str[i])) {
			int res = stoi(str.substr(i), &pos);
			nums.push_back(res);

			i += pos;
		}
	}

	/* Average of all the numbers */
	int avr = 0;

	/* If there are no numbers in the string */
	if(nums.size() == 0) {
		no_nums = true;

	} else {

		/* Calculate average */
		for(size_t i = 0; i < nums.size(); i++) {
			avr += nums[i];
		}

		avr /= nums.size();
	}


	/* Create a local copy */
	string bkp = str;

	/* Clear the string */
	str.clear();

	/* Convert average from int to string representation */
	string avr_str = "";
	if(!no_nums) {
		avr_str = to_string(avr);
	}

	/* Actually change now */
	for(size_t i = 0; i < bkp.size(); i++) {

		if(!isdigit(bkp[i])) {
			str.push_back(bkp[i]);

		} else {
			/* Insert average number */
			str.insert(str.size(), avr_str);

			/* Skip all other numbers */
			while(isdigit(bkp[i + 1])) {
				i++;
			}

		}
	}

}
