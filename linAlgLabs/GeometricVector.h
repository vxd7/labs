#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

#include "myException.h"

enum componentName {X_COMP = 0, Y_COMP, Z_COMP};

class GeometricPoint {
public:
	double getComponent(const componentName compName) const;

	void setComponent(const componentName compName);
	void setAllComponents(const double newx, const double newy, const double newz);

	GeometricPoint();
	GeometricPoint(const double newx, const double newy, const double newz);

private:
	double x;
	double y;
	double z;
};

//////////////////////////////////////////////////////////////////////
class GeometricVector {
public:
	double getVectorSize() const;
	GeometricPoint getVectorCoords() const;
	std::string getVectorName() const;

	void setVectorCoords(const GeometricPoint& vectorCoords);
	void setVectorName(const std::string& newName);

	// double scalarProduct(const myvector& vec); /**< Scalar product */
	// void crossProduct(const myvector& vec); /**< Cross product */

	GeometricVector operator+(const GeometricVector& vec);
	GeometricVector operator-(const GeometricVector& vec);
	GeometricVector operator*(const double num);

	friend std::ostream& operator<<(std::ostream& os, const GeometricVector& vec);
	GeometricVector();
	GeometricVector(const double x, const double y, const double z, std::string newName = "");
	~GeometricVector();


private:
	GeometricPoint vectorCoords;
	std::string name;
};
