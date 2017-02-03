#pragma once
#include <iostream>
#include <vector>;

class VectorZp;

namespace modFunc {
	/*
	 * Modular arithmetics:
	 */
	int modularCheck(int n, int p);
	int modularAdd(const int n1, const int n2, const int p);
	int modularMultiply(const int n1, const int n2, const int p);
	int inverseNumber(const int n, const int p);
	int extended_euclid(const int n, const int p, int &x, int &y);
	int inverseNumber(const int n, const int p);

	int scalarProductZp(const VectorZp& vec1, const VectorZp& vec2);

	/* Linear dependency checking */
	std::vector<std::vector<int> > getMatrixFromVectors(const std::vector<VectorZp>& vectors);
	void swapMetrixRows(const int r1, const int r2, std::vector<std::vector<int> >& matrix);
	void swapMetrixCols(const int c1, const int c2, std::vector<std::vector<int> >& matrix);
	bool isLinDep(const std::vector<VectorZp>& vectors);
}

class VectorZp {
	/* Data */
	int x, y, z;
	int p;
public:
	/* Constructors */
	VectorZp();
	VectorZp(const int x, const int y, const int z, const int p);

	/* Interfaces: */

	/* Initialize a vector */
	void setVector(int x, int y, int z, int p);
	/* Sum of two vectorZp */
	void addVector(const VectorZp& vec);
	/* multiplication of vectorZp and a scalar*/
	void multiplyVector(const int scalar);
	/* Find an inverse vectorZp */
	void inverseVector();

	/* Getters */

	int getX() const { return x; }
	int getY() const { return y; }
	int getZ() const { return z; }

	int getMod() const { return p; }

	/* Printer */

	void printVector() const;
};
