#include <iostream>
#include "vectorZp.h"

int main(int argc, char *argv[])
{
	VectorZp vec1;
	VectorZp vec2;

	vec1.setVector(4, -3, 2, 5);
	vec2.setVector(3, 4, -1, 5);

	vec1.printVector();
	vec2.printVector();

	return 0;
}


