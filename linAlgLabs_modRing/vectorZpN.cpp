#include "vectorZpN.h"
#include <vector>
#include <cmath>
#include <cstddef> //size_t
#include <iostream>

VectorZpN::VectorZpN(int numberOfDims, int module, std::vector<int> newComponents) {
	if(newComponents.size() != numberOfDims) {
		//except
	}

	p = module;
	dims = numberOfDims;
	std::vector<int>::iterator it = newComponents.begin();

	for(it; it != newComponents.end(); ++it) {
		comps.push_back(modFunc::modularCheck(*it, p));
	}

}

int modFunc::modularCheck(int n, int p) {
	if(p < 0) {
		return -1;
	}

	n %= p;

	if(n < 0) {
		n = p + n;
	}

	return n;
	
}

int modFunc::modularAdd(const int n1, const int n2, const int p) {

	int firstNum = n1, secondNum = n2;
	firstNum = modFunc::modularCheck(n1, p);
	secondNum = modFunc::modularCheck(n2, p);

	return (firstNum + secondNum) % p;
}

int modFunc::modularMultiply(const int n1, const int n2, const int p) {

	int firstNum = n1, secondNum = n2;
	firstNum = modFunc::modularCheck(n1, p);
	secondNum = modFunc::modularCheck(n2, p);

	return (firstNum * secondNum) % p;
}

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

/* Linear dependency checking */
std::vector<std::vector<int> > modFunc::getMatrixFromVectors(const std::vector<VectorZpN>& vectors) {
	std::vector<std::vector<int> > resMatrix;
	resMatrix.resize(vectors.size());

	for(size_t i = 0; i < vectors.size(); ++i) {
		for(size_t j = 0; j < vectors[0].dims; ++j) {
			resMatrix[i].push_back(vectors[i].comps[j]);
		}
	}

	return resMatrix;
	
}

void modFunc::swapMatrixRows(const int r1, const int r2, std::vector<std::vector<int> >& matrix) {
	if((r1 > matrix.size()) || (r2 > matrix.size())) {
		return;
	}

	std::vector<int> tmp = matrix[r1];
	matrix[r1] = matrix[r2];
	matrix[r2] = tmp;
}

void modFunc::swapMatrixCols(const int c1, const int c2, std::vector<std::vector<int> >& matrix) {
	if((c1 > (*(matrix.begin())).size()) || c2 > (*(matrix.begin())).size()) {
		return;
	}

	for(size_t i = 0; i < matrix.size(); ++i) {
		int tmp = matrix[i][c1];
		matrix[i][c1] = matrix[i][c2];
		matrix[i][c2] = tmp;
	}
	
}

void modFunc::makeColBelowZero(const int base_elem, std::vector<std::vector<int> >& mtr, const int p) {
	//col down
	for(int i = 0; i < mtr.size(); ++i) {
		if(i == base_elem) {
			continue;
		}
		int mult = modFunc::modularMultiply(mtr[i][base_elem], modFunc::inverseNumber(mtr[base_elem][base_elem], p), p);

		for(int j = 0; j < mtr[i].size(); ++j) {
			mtr[i][j] = modFunc::modularAdd(mtr[i][j], (-1) * modFunc::modularMultiply(mtr[base_elem][j], mult, p), p);
		}

	}
}

void printMtr(std::vector<std::vector<int> >& mtr) {
	for(int i = 0; i < mtr.size(); ++i) {
		for(int j = 0; j < mtr[i].size(); ++j) {
			std::cout << mtr[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}
bool modFunc::isLinDep(const std::vector<VectorZpN>& vectors) {
	int old_num = vectors.size();
	std::vector<std::vector<int> > mtr = modFunc::getMatrixFromVectors(vectors);
	int module = vectors[0].p;

	int rk;
	if(mtr.size() < mtr[0].size()) {
		rk = mtr.size();
	} else {
		rk = mtr[0].size();
	}
	for(int i = 0; i < rk; ++i) {
		if(mtr[i][i] != 0) {
			modFunc::makeColBelowZero(i, mtr, module);
		} else {
			// if there is a row below with non-zero base elem
			// swap it with current row (which has zero base-elem)
			bool swapped = false;
			for(int j = i + 1; j < mtr.size(); ++j) {
				if(mtr[j][i] != 0) {
					modFunc::swapMatrixRows(j, i, mtr);
					swapped = true;
					break;
				}
			}

			if(!swapped) {
				rk--;
				modFunc::swapMatrixCols(i, rk, mtr);
			}

			i -= 1;
			
		}
	}

	int rank = 0;
	int minDim;
	if(mtr.size() < mtr[0].size()) {
		minDim = mtr.size();
	} else {
		minDim = mtr[0].size();
	}
	for(int i = 0; i < minDim; ++i) {
		bool everythingZeroe = true;
		for(int j = i + 1; j < mtr.size(); ++j) {
			if(mtr[j][i] != 0) {
				everythingZeroe = false;
				break;
			}
		}
		if(everythingZeroe) {
			rank++;
		}
	}


	std::vector<std::vector<int> > resVectors;
	std::vector<std::vector<int> >::iterator resVectorsIterator = resVectors.begin();


	for(int i = 0; i < mtr.size(); ++i) {
		bool non_zero = false;
		for(int j = 0; j < mtr[i].size(); ++j) {
			if(mtr[i][j] != 0) {
				non_zero = true;
				break;
			}
		}

		if(non_zero) {
			std::vector<int> curVector;
			for(int k = 0; k < mtr[i].size(); ++k) {
				curVector.push_back(mtr[i][k]);
			}
			resVectors.push_back(curVector);
		}
	}

	if(vectors.size() == resVectors.size()) {
		std::cout << '1';
	} else {
		std::cout << '0';
	}
	std::cout << std::endl;

	std::cout << resVectors.size() << std::endl;

	for(resVectorsIterator = resVectors.begin(); resVectorsIterator != resVectors.end(); ++resVectorsIterator) {
		std::vector<int>::iterator it = (*resVectorsIterator).begin();

		for(it; it != (*resVectorsIterator).end(); ++it) {
			std::cout << *it << ' ';
		}

		std::cout << std::endl;
	}

	return true;
}
