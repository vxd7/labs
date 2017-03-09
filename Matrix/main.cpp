#include "Matrix.h"
#include <iomanip>
typedef std::vector<std::vector<double>> CMTR;

int main() {

	CMTR vec1 = {
		{1, 1},
		{1, 1},
		{1, 1},
	};

	CMTR vec2 = {
		{1, 2, 1},
		{1, 2, 1},
	};

	Matrix mtr1(3, 2, vec1);
	Matrix mtr2(2, 3, vec2);


	std::vector<std::vector<double>> m = {
		{2,5,7},
		{6,3,4},
		{5,-2,-3}
	};

	sqMatrix r(3,m);
	Matrix eee = r.getInverseMatrix();
	eee.print();
	sqMatrix qw = r * eee;
	qw.transformPrecision(0.0001);
	qw.print();

	/*
	Matrix mtr3 = mtr1 * mtr2;
	mtr3.print();

	std::cout << std::endl;
	Matrix mtr4 = mtr2.Transpose();
	mtr4.print();
	*/
	return 0;
	
}
