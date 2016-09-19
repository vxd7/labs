#include <iostream>
#include <cstring>
#include <vector>

#include <algorithm>

struct __barInfo
{
	std::string name;
	int freq;
};

class Histogram {
public:
	/* Number of bars in the Histogram */
	int barCount;

	/* Block type to print */
	char block;
	
	/* Standart constructor */
	Histogram();

	/*
	 * User Interface function. 
	 * Gets all of the input, parses it and creates the Histogram
	 */
	void parseData(std::string s);

	/*
	 * Prints Histogram.
	 * User Interface function for printing the while Histogram 
	 * to the STDOUT
	 */
	// TODO: add print to file feature
	void printHistogram();

	void sortHistogram(bool ascending = true);

private:
	/*
	 * Process character.
	 * Searches for a character in the Histogram. If found -- increases
	 * its freq, if not a new bar is created.
	 *
	 * addBar(...) is called when a new bar is created
	 */
	void procData(std::string s);

	/*
	 * Adds new bar to the Histogram.
	 * Increases the barCount variable by one.
	 */
	void addBar(std::string newName, int newFreq = 1);

	/*
	 * Calculate the percentage of each item.
	 */
	void computeRates();

	std::vector<__barInfo> barInfo;

	
};

Histogram::Histogram()
{
	barCount = 0;
	block = '#';
}

void Histogram::addBar(std::string newName, int newFreq)
{
	struct __barInfo __tmp;
	__tmp.name = newName;
	__tmp.freq = newFreq;

	barInfo.push_back(__tmp);

	barCount++;
}

void Histogram::parseData(std::string s)
{
	for(size_t i = 0; i < s.size(); ++i)
	{
		if(!isalpha(s[i]))
			continue;

		procData(s.substr(i, 1));

	}
	
	/*
	 * Equalize the histogram
	 */
	computeRates();
	
}

void Histogram::procData(std::string name)
{
	bool added = false;

	for(size_t i = 0; i < name.size(); ++i)
		name[i] = tolower(name[i]);

	for(size_t i = 0; i < barCount; ++i)
	{
		if(barInfo[i].name == name)
		{
			barInfo[i].freq++;
			added = true;
			break;
		}
	}

	if(!added)
		addBar(name);
}

void Histogram::printHistogram()
{
	for(size_t i = 0; i < barCount; ++i)
	{
		std::cout << barInfo[i].name << '|';
		for(size_t j = 0; j < barInfo[i].freq; ++j)
			std::cout << '#';

		std::cout << std::endl;
	}
}

void Histogram::computeRates()
{
	long int sum_t = 0;

	for(size_t i = 0; i < barCount; ++i)
	{
		sum_t += barInfo[i].freq;
	}

	double q = .0;

	for(size_t i = 0; i < barCount; ++i)
	{
		q = barInfo[i].freq * 1.0;
		q = (q / sum_t * 1.0);
		q *= 100.0;

		barInfo[i].freq = q;
	}
}

bool cmp(__barInfo b1, __barInfo b2)
{
	if(b1.freq < b2.freq)
		return true;
	else 
		return false;
}

void Histogram::sortHistogram(bool ascending)
{
	if(ascending)
		std::sort(barInfo.begin(), barInfo.end(), cmp);
	else
	{
		std::sort(barInfo.begin(), barInfo.end(), cmp);
		std::reverse(barInfo.begin(), barInfo.end());
	}
}
