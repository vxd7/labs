#pragma once
#include <vector>
#include <cmath>
#include <iostream>
#include <string>

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

class Matrix {
protected:
	std::vector<std::vector<double>> mtr;
	int rows, cols;

public:
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

};
