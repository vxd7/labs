#include <iostream>
#include "hgram.h"

int main()
{
	Histogram myHistogram;

	std::string s;
	getline(std::cin, s);

	myHistogram.parseData(s);

	myHistogram.printHistogram();

	return 0;
}
