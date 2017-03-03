#pragma once
#include <vector>

class VectorZpN;

namespace modFunc {
	/*
	 * Modular arithmetics:
	 */
	int modularCheck(int n, int p);
	int modularAdd(const int n1, const int n2, const int p);
	int modularMultiply(const int n1, const int n2, const int p);
	int inverseNumber(const int n, const int p);
	int extended_euclid(const int n, const int p, int &x, int &y);

	/* Linear dependency checking */
	std::vector<std::vector<int> > getMatrixFromVectors(const std::vector<VectorZpN>& vectors);
	void swapMatrixRows(const int r1, const int r2, std::vector<std::vector<int> >& matrix);
	void swapMatrixCols(const int c1, const int c2, std::vector<std::vector<int> >& matrix);
	void makeColBelowZero(const int base_elem, std::vector<std::vector<int> >& mtr, const int p);
	bool isLinDep(const std::vector<VectorZpN>& vectors);
}

class VectorZpN {
public:
	int dims;
	int p;
	std::vector<int> comps;

	VectorZpN(int numberOfDims, int module, std::vector<int> newComponents);
};

