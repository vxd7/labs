#include "vectorZp.h"
#include <iostream>
#include <cmath>
#include <vector>

/*
 * Class functions:
 */
VectorZp::VectorZp() {
	x = 0;
	y = 0;
	z = 0;
	p = 0;
}

VectorZp::VectorZp(const int x, const int y, const int z, const int p) {
	setVector(x, y, z, p);
}

void VectorZp::setVector(int x, int y, int z, int p) {

	x = modFunc::modularCheck(x, p);
	y = modFunc::modularCheck(y, p);
	z = modFunc::modularCheck(z, p);

	if((x == -1) || (y == -1) || (z == -1)) {
		return;
	}

	this->x = x;
	this->y = y;
	this->z = z;
	this->p = p;
}

void VectorZp::addVector(const VectorZp& vec) {
	x = modFunc::modularAdd(x, vec.getX(), p);
	y = modFunc::modularAdd(y, vec.getY(), p);
	z = modFunc::modularAdd(z, vec.getZ(), p);
}

void VectorZp::multiplyVector(const int scalar) {
	int scalar_mod = modFunc::modularCheck(scalar, p);
	if(scalar_mod == -1) {
		return;
	}

	x = modFunc::modularMultiply(x, scalar_mod, p);
	y = modFunc::modularMultiply(y, scalar_mod, p);
	z = modFunc::modularMultiply(z, scalar_mod, p);
}

void VectorZp::inverseVector() {
	x = modFunc::inverseNumber(x, p);
	y = modFunc::inverseNumber(y, p);
	z = modFunc::inverseNumber(z, p);
}

void VectorZp::printVector() const {
	std::cout << "(" << x << ", " << y << ", " << z << ")";
	std::cout << std::endl;
}


//****************************************************************************************************
//<+>                                                                        Added (Y-M-D): 2017-01-14
// Method: modularCheck(int, int)
//
// Purpose: 1. Check whether the number n can be found in the ring of Zp
// 			2. If the number n is negative, convert it to its positive representation in Zp
//
// Parameters:
//       [n]:      Number to be ckecked
//       [p]:      Prime number, the base of Z ring
//
// Returns: 1. n, if n is in Zp
// 			2. (-1) if the checks have failed
//<->
//****************************************************************************************************
int modFunc::modularCheck(int n, int p) {
	if(p < 0) {
		return -1;
	}

	if((n > p) || (n < (-1) * p)) {
		return -1;
	}

	if(n < 0) {
		n = p + n;
	}

	return n;
	
}

//****************************************************************************************************
//<+>                                                                        Added (Y-M-D): 2017-01-14
// Method: modularAdd(int, int, int)
//
// Purpose: Add two numbers in the ring of Zp
//
// Parameters:
//       [n1]:      The first number to be added
//       [n2]:      The second number to be added
//       [p]:       The base of Z ring
//
// Returns: 1. (n1 + n2)(mod p) if everything is alright
// 			2. (-1) if smth went wrong
//<->
//****************************************************************************************************
int modFunc::modularAdd(const int n1, const int n2, const int p) {

	int firstNum = n1, secondNum = n2;
	firstNum = modFunc::modularCheck(n1, p);
	secondNum = modFunc::modularCheck(n2, p);

	if((firstNum == -1) || (secondNum == -1)) {
		return -1;
	}

	return (n1 + n2) % p;
}

//****************************************************************************************************
//<+>                                                                        Added (Y-M-D): 2017-01-14
// Method: modularMultiply(int, int, int)
//
// Purpose: Multiply two numbers in the ring of Zp
//
// Parameters:
//       [n1]:      The first number to be multiplied
//       [n2]:      The second number to be multiplied
//       [p]:       The base of Z ring
//
// Returns: 1. (n1 * n2)(mod p) if everything is alright
// 			2. (-1) if smth went wrong
//
//<->
//****************************************************************************************************
int modFunc::modularMultiply(const int n1, const int n2, const int p) {

	int firstNum = n1, secondNum = n2;
	firstNum = modFunc::modularCheck(n1, p);
	secondNum = modFunc::modularCheck(n2, p);

	if((firstNum == -1) || (secondNum == -1)) {
		return -1;
	}

	return (n1 * n2) % p;
}

//****************************************************************************************************
//<+>                                                                        Added (Y-M-D): 2017-01-14
// Method: extended_euclid(int n, int p, int &x, int &y)
//
// Purpose: Implements the extended Euclid algo in order to find the b coeff
//			x * n + y * p = GCD(n, p) (=1)
//
// Parameters:
//       [n]:      The number to find the inverse to
//       [p]:      Base of Z ring
//       [&x]:     Coefficient x
//       [&y]:     Coefficient y
//
// Returns: GCD(n, p);
//<->
//****************************************************************************************************
int modFunc::extended_euclid(const int n, const int p, int &x, int &y) {
	if(n == 0) {
		x = 0;
		y = 1;

		return p;
	}

	int x1, y1;
	int d = modFunc::extended_euclid(p%n, n, x1, y1);

	x = y1 - (p/n) * x1;
	y = x1;

	return d;
}

int modFunc::inverseNumber(const int n, const int p) {
	int x, y, d;
	d = modFunc::extended_euclid(n, p, x, y);

	if(d == 1) { /* IF GCD(n, p) == 1 (ensure that p is indeed a prime number) */
		return x;
	} else {
		return 0; /* Incorrect user input of number p */
	}
}

int modFunc::scalarProductZp(const VectorZp& vec1, const VectorZp& vec2) {
	if(vec1.getMod() != vec2.getMod()) {
		return -1;
	}

	int module = vec1.getMod();
	int ans, ans1, ans2, ans3;
	ans1 = modFunc::modularMultiply(vec1.getX(), vec2.getX(), module);
	ans2 = modFunc::modularMultiply(vec1.getY(), vec2.getY(), module);
	ans3 = modFunc::modularMultiply(vec1.getZ(), vec2.getZ(), module);

	ans = modFunc::modularAdd(ans1, modFunc::modularAdd(ans2, ans3, module), module);
	return ans;

}

/* Linear dependency checking */
std::vector<std::vector<int> > modFunc::getMatrixFromVectors(const std::vector<VectorZp>& vectors) {
	std::vector<std::vector<int> > resMatrix;
	resMatrix.resize(vectors.size());

	for(size_t i = 0; i < vectors.size(); ++i) {
		resMatrix[i].push_back(vectors[i].getX());
		resMatrix[i].push_back(vectors[i].getY());
		resMatrix[i].push_back(vectors[i].getZ());
	}

	return resMatrix;
	
}
void modFunc::swapMetrixRows(const int r1, const int r2, std::vector<std::vector<int> >& matrix) {
	if((r1 > matrix.size()) || (r2 > matrix.size())) {
		return;
	}

	std::vector<int> tmp = matrix[r1];
	matrix[r1] = matrix[r2];
	matrix[r2] = tmp;
}

void modFunc::swapMetrixCols(const int c1, const int c2, std::vector<std::vector<int> >& matrix) {
	if((c1 > (*(matrix.begin())).size()) || c2 > (*(matrix.begin())).size()) {
		return;
	}

	for(size_t i = 0; i < matrix.size(); ++i) {
		int tmp = matrix[i][c1];
		matrix[i][c1] = matrix[i][c2];
		matrix[i][c2] = tmp;
	}
	
}

bool modFunc::isLinDep(const std::vector<VectorZp>& vectors) {
	std::vector<std::vector<int> > mtr = getMatrixFromVectors(vectors);

	
}
