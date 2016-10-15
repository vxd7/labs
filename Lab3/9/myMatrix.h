#pragma once
#include <iostream>
#include <vector>
#include <cmath>

#include "geomVector.h"

class myMatrix {
public:
	myMatrix();
	myMatrix(std::vector <std::vector<double>> newMatrix);
	myMatrix operator* (myMatrix& newMatrix);

	void makeMatrix(std::vector <std::vector<double>> newMatrixDef);
	void makeRotMatrix(std::string rotAxes, double angle);
	void makeMatrixFromVector(myvector vec);

	int getrows();
	int getcols();

	std::vector <std::vector<double>> matrix;
};
