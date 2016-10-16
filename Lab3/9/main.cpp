#include <iostream>
#include "shape.h"

int main() 
{

	pyramid myPyramid;
	myPyramid.mkShape();
	myPyramid.printShape();

	myPyramid.rotateShape(90.0, 90.0, 0.0);

	myPyramid.printShape();

	return 0;

}
