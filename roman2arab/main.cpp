/*
 * 08-Sept-2016 01:28:29
 *
 * Roman 2 Arab numbers checker and converter.
 *
 * Uses classic roaman numbers ruleset:
 * 1) No more than 3 repeated numbers in row
 * 2) Only 6 subtraction rules avaliable:
 * 	- IV
 * 	- IX
 * 	- XL
 * 	- XC
 * 	- CD
 * 	- CM
 * 3) Previous number can be greater, equal, 5 times lower or 10 times lower than the current number
 *
 * Input -> Check -> Convert -> Result
 *   |        |
 * Cmd args or by hand
 *            |
 *         Failure if incorrect
 */
#include <iostream>
#include <string>

using namespace std;

int roman2arab(string roman);
bool checkRoman(string roman);

int cnvRmn(char d);

int main(int argc, char *argv[])
{
	string s;

	if(argc > 1)
	{
		s = string(argv[1]);

		if(!checkRoman(s))
			cout << "Incorrect number: " << s << endl;
		else
		{
			int res = roman2arab(s);
			cout << "Result: " << res << endl;
		}
	}

	else
	{
		cout << "Input roman number: " << endl;
		cin >> s;

		if(!checkRoman(s))
			cout << "Incorrect number: " << s << endl;
		else
		{

			int res = roman2arab(s);
			cout << "Result: " << res << endl;
		}
	}

	return 0;
}

/* Check number for correctness */
bool checkRoman(string roman)
{
	/* One-digit number */
	if((roman.size() == 1) && cnvRmn(roman[0]) != -1)
		return true;
	else
	{
		for(size_t i = 0; i < roman.size() - 1; ++i)
		{
			/* Incorrect character in Roman number string */
			if(cnvRmn(roman[i]) == -1)
				return false;

			/*Check the numbers according t the rules */
			if( (cnvRmn(roman[i]) >= cnvRmn(roman[i + 1])) || (5 * cnvRmn(roman[i]) == cnvRmn(roman[i + 1])) || (10 * cnvRmn(roman[i]) == cnvRmn(roman[i + 1])) );
			else return false;

			/* Numbers can repeate only 3 times */
			if(cnvRmn(roman[i]) == cnvRmn(roman[i + 1]))
			{
				int ret = 1;
				while(cnvRmn(roman[i]) == cnvRmn(roman[i + 1]))
				{
					ret++;
					i++;
					
				}

				if(ret > 3)
					return false;
			}
		}
	}

	return true;
}

/* Convert */
int roman2arab(string roman)
{
	if(roman.size() == 0)
		return 0;

	if(roman.size() == 1)
		return cnvRmn(roman[0]);

	/* We assume now that the input Roman number string is checked and correct */
	int res = 0;

	/* Find the subtraction rule */
	for(size_t i = 0; i < roman.size() - 1; ++i)
	{
		/* There are 6 valid subtraction rules in classic Roman numbers system */
		if( (roman[i] == 'I' && roman[i + 1] == 'V') ||
				(roman[i] == 'I' && roman[i + 1] == 'X') ||
				(roman[i] == 'X' && roman[i + 1] == 'L') ||
				(roman[i] == 'X' && roman[i + 1] == 'C') ||
				(roman[i] == 'C' && roman[i + 1] == 'D') ||
				(roman[i] == 'C' && roman[i + 1] == 'M')
		  )
		{
			/* Sum everything up recursively */
			res += roman2arab(roman.substr(0, i)); // Sum up the substring without subtraction
			res += cnvRmn(roman[i + 1]) - cnvRmn(roman[i]); // Sum up the subtraction part
			res += roman2arab(roman.substr(i + 2, roman.size() - (i + 2))); // Sum up the other string part

			return res; // EXIT FUKKEN EVERYTHING!!!!

		}
	}

	/* If we didn't find any subtraction -- go here */
	for(size_t i = 0; i < roman.size(); ++i)
	{
		res += cnvRmn(roman[i]);
	}

	return res;
}

/* Convert single digit to arab
 * If incorrect -- return (-1)
 */
int cnvRmn(const char d)
{
	switch(d)
	{
		case 'I': return 1; break;
		case 'V': return 5; break;
		case 'X': return 10; break;
		case 'L': return 50; break;
		case 'C': return 100; break;
		case 'D': return 500; break;
		case 'M': return 1000; break;

		default: return -1; break;
	}
}
