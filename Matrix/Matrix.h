#pragma once
#include <vector>
#include <cmath>
#include <iostream>
#include <string>

#define eps 0.00001
class InvalidMatrixSize : public std::exception {
	std::string reason;

public:
	InvalidMatrixSize() :
		reason("Invalid matrix size")
	{}

	InvalidMatrixSize(std::string _reason) :
		reason(_reason)
	{}

	const char* what() const throw() {
		return reason.c_str();
	}
};

class DegenerateMatrix : public std::exception {
	const char* what() const throw() {
		return "Cannot invert degenerate(singular) matrix";
	}
};

class Matrix {
protected:
	std::vector<std::vector<double>> mtr;
	int rows, cols;


public:
	/* Default constructor */
	Matrix() {}

	Matrix(int rows, int cols) :
		rows(rows),
		cols(cols)
	{
		std::vector<double> zero(cols);
		for(int i = 0; i < rows; ++i) {
			mtr.push_back(zero);
		}
	}

	Matrix(int rows, int cols, std::vector<std::vector<double>> newMatrix) :
		rows(rows),
		cols(cols)
	{
		for(int i = 0; i < rows; ++i) {
			mtr.push_back(newMatrix[i]);
		}
	}

	void print() {
		for(int i = 0; i < rows; ++i) {
			for(int j = 0; j < cols; ++j) {
				std::cout << mtr[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	double& at(int i, int j) {
		return mtr[i][j];
	}

	double at(int i, int j) const {
		return mtr[i][j];
	}

	std::vector<double>& operator[](int i) { //PUTIN -- MNOGOHODOVOCHKA!!!
		return (mtr[i]);
	}

	std::vector<double> operator[](int i) const {
		return (mtr[i]);
	}

	Matrix& operator=(const Matrix& sec) {
		if(rows != sec.rows || cols != sec.cols) {
			throw InvalidMatrixSize("Invalid matrix sizes, noob");
		}

		for(int i = 0; i < rows; ++i) {
			mtr[i] = sec.mtr[i];
		}

		return *this;
	}

	Matrix operator+(const Matrix& sec) {
		if(rows != sec.rows || cols != sec.cols) {
			throw InvalidMatrixSize("Invalid matrix sizes, cannot summate!");
		}

		std::vector<std::vector<double>> tmp;

		tmp.resize(rows);
		for(int i = 0; i < rows; ++i) {
			tmp[i].resize(cols);
		}

		for(int i = 0; i < rows; ++i) {
			for(int j = 0; j < cols; ++j) {
				tmp[i][j] = mtr[i][j] + sec.mtr[i][j];
			}
		}

		return Matrix(rows, cols, tmp);
	}

	Matrix operator*(double num) {
		std::vector<std::vector<double>> tmp;

		tmp.resize(rows);
		for(int i = 0; i < rows; ++i) {
			tmp[i].resize(cols);
		}

		for(int i = 0; i < rows; ++i) {
			for(int j = 0; j < cols; ++j) {
				tmp[i][j] = mtr[i][j] * num;
			}
		}

		return Matrix(rows, cols, tmp);
		
	}

	Matrix operator*(const Matrix& sec) {

		if(cols != sec.rows) {
			throw InvalidMatrixSize("Invalid matrix sizes, cannot multiply!");
		}

		std::vector<std::vector<double>> tmp;

		tmp.resize(rows);
		for(int i = 0; i < rows; ++i) {
			tmp[i].resize(sec.cols);
		}

		for(size_t i = 0; i < rows; ++i) {
			for(size_t k = 0; k < sec.cols; ++k) {
				size_t j;
				int sum = 0;
				for(j = 0; j < sec.rows; ++j) {
					sum += mtr[i][j] * sec.mtr[j][k];
				}
				tmp[i][k] = sum;
			}
		}

		return Matrix(rows, sec.cols, tmp);
		
	}

	Matrix Transpose() {
		std::vector<std::vector<double>> tmp;
		tmp.resize(cols);
		for(int i = 0; i < cols; ++i) {
			tmp[i].resize(rows);
		}

		for(int i = 0; i < cols; ++i) {
			for(int j = 0; j < rows; ++j) {
				tmp[i][j] = mtr[j][i];
			}
		}

		return Matrix(cols, rows, tmp);
		
	}

	void addRow(std::vector<double> newRow) {
		if(newRow.size() != mtr[0].size()) {
			throw InvalidMatrixSize("Invalid row size");
		}

		mtr.push_back(newRow);
		rows++;
	}

	void addCol(std::vector<double> newCol) {
		if(newCol.size() != mtr.size()) {
			throw InvalidMatrixSize("Invalid col size");
		}

		for(int i = 0; i < mtr.size(); ++i) {
			mtr[i].push_back(newCol[i]);
		}
		cols++;
	}

	void swapRows(int row1, int row2) {
		for(int i = 0; i < cols; ++i) {
			double tmp = mtr[row1][i];
			mtr[row1][i] = mtr[row2][i];
			mtr[row2][i] = tmp;
		}
	}

	void swapCols(int col1, int col2) {
		for(int i = 0; i < rows; ++i) {
			double tmp = mtr[i][col1];
			mtr[i][col1] = mtr[i][col2];
			mtr[i][col2] = tmp;
		}
	}

	bool isSquare() const {
		return (rows == cols);
	}

	void transformPrecision(double epsilon) {
		for(int i = 0; i < rows; ++i) {
			for(int j = 0; j < cols; ++j) {
				if(mtr[i][j] < epsilon) {
					mtr[i][j] = 0.0;
				}
			}
		}
	}

	int GaussTransform();
	Matrix FullGaussTransform();
};

int Matrix::GaussTransform() {
	int rowSwaps = 0;
	for(int l1 = 0; l1 < rows - 1; ++l1) {
		int maxN = l1;
		double maxValue = mtr[l1][l1];

		for(int l2 = l1 + 1; l2 < rows; ++l2) {
			if(mtr[l2][l2] > maxValue) {
				maxN = l2;
				maxValue = mtr[l2][l2];
			}
		}

		if(maxN > l1) {
			//Then swap is needed
			swapRows(l1, maxN);
			++rowSwaps;
		} else {
			//Swap is NOT needed
			//But we need to check for zeroe-base-element
			if(maxValue == 0) {
				//Some shit happened
				//throw an exception here
				std::cout << "Shit happened...";
			}
		}

		//Subtract the row with base elem from all subsequent rows
		for(int l2 = l1 + 1; l2 < rows; ++l2) {
			double k = mtr[l2][l1]/mtr[l1][l1];
			mtr[l2][l1] = 0.0; //We need exact zeroe here -- because of double rounding
			for(int c = l1 + 1; c < cols; ++c) {
				mtr[l2][c] -= mtr[l1][c] * k;
			}
		}
	}

	return rowSwaps;
	
}

Matrix Matrix::FullGaussTransform() {
	Matrix res(rows, cols, mtr);
	int lead;
	int rix, iix;
	double lv;
	int rc = rows;

	lead = 0;
	for(rix = 0; rix < rc; ++rix) {
		if(lead >= cols) {
			return res;
		}
		iix = rix;
		while(res[iix][lead] == 0) {
			iix++;
			if(iix == rc) {
				iix = rix;
				lead++;
				if(lead == cols) {
					return res;
				}
			}
		}
		res.swapRows(iix, rix);

		//normalize ROW
		double llv = res[rix][lead];
		for(int i = 0; i < cols; ++i) {
			res[rix][i] /= llv;
		}

		for(iix = 0; iix < rc; ++iix) {
			if(iix != rix) {
				lv = res[iix][lead];
				//Multiply and subtract
				for(int ix = 0; ix < cols; ++ix) {
					res[iix][ix] += (-1.0) * lv * res[rix][ix];
				}
				
			}
		}
		lead++;
	}
	return res;
}

class sqMatrix : public Matrix {
private:
	/* Restrict user access for there functions */
	/* because it can break the square shape of the matrix */
	using Matrix::addRow;
	using Matrix::addCol;

protected:
	int GaussRowSwaps = 0; /* Number of rows swapped by Gauss Transform
						  We need to keep track of it if we don't want to
						  fail with the sign of the determinant
						  */
public:
	sqMatrix(int dim) : Matrix(dim, dim) {}
	sqMatrix(const Matrix& bmtr) : Matrix(bmtr) { /* !Very! important place! */
		if(!bmtr.isSquare()) {
			throw InvalidMatrixSize("Cannot construct square matrix from non-sqare");
		}
	}
	sqMatrix(int dims, std::vector<std::vector<double>> newMatrix) : Matrix(dims, dims, newMatrix) {
		if(newMatrix.size() != newMatrix[0].size()) {
			throw InvalidMatrixSize("Not sqare in constructor");
		}
	}

	double getDet() {
		GaussRowSwaps = GaussTransform();

		double det = mtr[0][0];
		for(int i = 1; i < rows; ++i) {
			det *= mtr[i][i];
		}

		if(GaussRowSwaps % 2 != 0) {
			det *= (-1.0);
		}

		return det;
	}

	sqMatrix getInverseMatrix();

};

sqMatrix sqMatrix::getInverseMatrix() {
	sqMatrix old(rows, mtr); //Dirty workaround here -- TODO: rewrite later!
	if(old.getDet() == 0.0) { //Add EPSILON comparision here 
		throw DegenerateMatrix();
	}

	Matrix inversify(rows, rows, mtr); //TODO: optimise
	for(int i = 0; i < rows; ++i) {
		std::vector<double> idCol(rows, 0);
		idCol[i] = 1.0;
		inversify.addCol(idCol);
	}

	 inversify = inversify.FullGaussTransform();

	std::cout << std::endl;
	inversify.print();
	std::cout << std::endl;


	sqMatrix res(rows);
	for(int i = 0; i < rows; ++i) {
		for(int j = 0; j < cols; ++j) {
			res.at(i, j) = inversify.at(i, cols + j);
		}
	}

	return res;
}
