#include "myMatrix.h"

myMatrix::myMatrix()
{
	
}
myMatrix::myMatrix(std::vector <std::vector<double>> newMatrix)
{
	//int rows, cols;
	//cols = newMatrix[0].size();
	//rows = newMatrix.size();

	matrix = newMatrix;
}

void myMatrix::makeMatrix(std::vector <std::vector<double>> newMatrixDef)
{
	matrix = newMatrixDef;
}
void myMatrix::makeRotMatrix(std::string rotAxes, double angle)
{
	angle *= 180.0/M_PI;

	if(matrix.size() == 0) {
		matrix.resize(3);
		for(size_t i = 0; i < 3; ++i) {
			matrix[i].resize(3);
		}
	}

	if(rotAxes == "X") {

		matrix[0][0] = 1.0;
		matrix[0][1] = 0.0;
		matrix[0][2] = 0.0;

		matrix[1][0] = 0.0;
		matrix[1][1] = std::cos(angle);
		matrix[1][2] = (-1.0) * std::sin(angle);

		matrix[2][0] = 0.0;
		matrix[2][1] = std::sin(angle);
		matrix[2][2] = std::cos(angle);
	} else if(rotAxes == "Y") {

		matrix[0][0] = std::cos(angle);
		matrix[0][1] = 0.0;
		matrix[0][2] = std::sin(angle);

		matrix[1][0] = 0.0;
		matrix[1][1] = 1.0;
		matrix[1][2] = 0.0;

		matrix[2][0] = (-1.0) * std::sin(angle);
		matrix[2][1] = 0.0;
		matrix[2][2] = std::cos(angle);
	} else if(rotAxes == "Z") {

		matrix[0][0] = std::cos(angle);
		matrix[0][1] = (-1.0) * std::sin(angle);
		matrix[0][2] = 0.0;

		matrix[1][0] = std::sin(angle);
		matrix[1][1] = std::cos(angle);
		matrix[1][2] = 0.0;

		matrix[2][0] = 0.0;
		matrix[2][1] = 0.0;
		matrix[2][2] = 1.0;
	}
}
void myMatrix::makeMatrixFromVector(myvector vec)
{
	if(matrix.size() == 0) {
		matrix.resize(3);
		for(size_t i = 0; i < 3; ++i) {
			matrix[i].resize(1);
		}
	}

	matrix[0][0] = vec.getVectorCoords().getx();
	matrix[1][0] = vec.getVectorCoords().gety();
	matrix[2][0] = vec.getVectorCoords().getz();
}

int myMatrix::getrows()
{
	return matrix.size();
	
}

int myMatrix::getcols()
{
	return matrix[0].size();
	
}

myMatrix myMatrix::operator* (myMatrix& matrixClass1)
{
	std::vector<std::vector<double>> res;

	int newMatrixCols = matrixClass1.getcols();
	int newMatrixRows = matrixClass1.getrows();

	int matrixRows = getrows();
	int matrixCols = getcols();

	res.resize(matrixRows);
	for(size_t i = 0; i < matrixRows; ++i) {
		res[i].resize(newMatrixCols);
	}

	if(matrixCols != newMatrixRows) {
		std::cout << "Error multiplying matrices! Incorrect sizes" << std::endl;
		//throw an exception here!!
		std::exit(1);
	}


	for(size_t i = 0; i < matrixRows; ++i) {
		for(size_t k = 0; k < newMatrixCols; ++k) {
			size_t j;
			int sum = 0;
			for(j = 0; j < newMatrixRows; ++j) {
				sum += matrix[i][j] * matrixClass1.matrix[j][k];
			}
			res[i][k] = sum;
		}
	}

	myMatrix resMatrixClass(res);

	return resMatrixClass;
}


