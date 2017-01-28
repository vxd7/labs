#include "GeometricVector.h"

#include <iostream>
#include <string>
#include <map>
#include <cmath>

GeometricPoint::GeometricPoint() {
	//dimensionCount = DEFAULT_DIM;
	pointCoords.resize(DEFAULT_DIM);
	name = "";
}

// GeometricPoint::GeometricPoint(const int newDimensionCount, const std::vector<double>& newPointCoords, const std::string& pointName) {
// 
// 	if(newPointCoords.size() < newDimensionCount) {
// 		// throw exception
// 	}
// 
// 	dimensionCount = newDimensionCount;
// 	name = pointName;
// 
// 	for(size_t i = 0; i < dimensionCount; ++i) {
// 		pointCoords[i] = newPointCoords[i];
// 	}
// 	
// }

GeometricPoint::GeometricPoint(const double newx, const double newy, const double newz, const std::string& pointName) {
	pointCoords[X_COMP] = newx;
	pointCoords[Y_COMP] = newy;
	pointCoords[Z_COMP] = newz;

	name = pointName;
}

void GeometricPoint::setAllComponents(const double newx, const double newy, const double newz) {
	pointCoords[X_COMP] = newx;
	pointCoords[Y_COMP] = newy;
	pointCoords[Z_COMP] = newz;
}

double GeometricPoint::getComponent(const componentName& compName) const {
	return pointCoords[compName];
}

void GeometricPoint::setComponent(const componentName& compName, const double newComponent) {
	pointCoords[compName] = newComponent;
}

// GEOMETRIC VECTOR
GeometricVector::GeometricVector(const double x, const double y, const double z, const std::string& vectorName) {
	vectorCoords.setAllComponents(x, y, z);
}
