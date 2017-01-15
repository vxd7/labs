#pragma once
#include <iostream>

/*
 * Modular arithmetics:
 */
int modularCheck(int n, int p);
int modularAdd(int n1, int n2, int p);
int modularMultiply(int n1, int n2, int p);
int inverseNumber(int n, int p);
int extended_euclid(int a, int b);
int inverseNumber(int n, int p);

class VectorZp {
	/* Data */
	int x, y, z;
	int p;
public:
	/* Constructors */
	VectorZp();
	VectorZp(int x, int y, int z, int p);

	/* Interfaces: */

	/* Initialize a vector */
	void setVector(int x, int y, int z, int p);
	/* Sum of two vectorZp */
	void addVector(VectorZp vec);
	/* multiplication of two vectorZp */
	void multiplyVector(VectorZp vec);
	/* Find an inverse vectorZp */
	void inverseVector();

	/* Getters */

	int getX() { return x; }
	int getY() { return y; }
	int getZ() { return z; }

	/* Printer */

	void printVector();
};

/*
 * Class functions:
 */
VectorZp::VectorZp() {
	x = 0;
	y = 0;
	z = 0;
	p = 0;
}

VectorZp::VectorZp(int x, int y, int z, int p) {
	setVector(x, y, z, p);
}

void VectorZp::setVector(int x, int y, int z, int p) {

	x = modularCheck(x, p);
	y = modularCheck(y, p);
	z = modularCheck(z, p);

	if((x == -1) || (y == -1) || (z == -1)) {
		return;
	}

	this->x = x;
	this->y = y;
	this->z = z;
	this->p = p;
}

void VectorZp::addVector(VectorZp vec) {
	x = modularAdd(x, vec.getX(), p);
	y = modularAdd(y, vec.getY(), p);
	z = modularAdd(z, vec.getZ(), p);
}

void VectorZp::multiplyVector(VectorZp vec) {
	x = modularMultiply(x, vec.getX(), p);
	y = modularMultiply(y, vec.getY(), p);
	z = modularMultiply(z, vec.getZ(), p);
}

void VectorZp::inverseVector() {
	x = inverseNumber(x, p);
	y = inverseNumber(y, p);
	z = inverseNumber(z, p);
}

void VectorZp::printVector() {
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
int modularCheck(int n, int p) {
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
int modularAdd(int n1, int n2, int p) {

	n1 = modularCheck(n1, p);
	n2 = modularCheck(n2, p);

	if((n1 == -1) || (n2 == -1)) {
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
int modularMultiply(int n1, int n2, int p) {

	n1 = modularCheck(n1, p);
	n2 = modularCheck(n2, p);

	if((n1 == -1) || (n2 == -1)) {
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
int extended_euclid(int n, int p, int &x, int &y) {
	if(n == 0) {
		x = 0;
		y = 1;

		return p;
	}

	int x1, y1;
	int d = extended_euclid(p%n, n, x1, y1);

	x = y1 - (p/n) * x1;
	y = x1;

	return d;
}

int inverseNumber(int n, int p) {
	int x, y, d;
	d = extended_euclid(n, p, x, y);

	if(d == 1) { /* IF GCD(n, p) == 1 (ensure that p is indeed a prime number) */
		return x;
	} else {
		return 0; /* Incorrect user input of number p */
	}
}
