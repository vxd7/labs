/* ZASHQUARE */
#include "GeometricVector.h"

#include <iostream>
#include <string>
#include <map>
#include <cmath>

double vectorAlgebra::scalarProduct(const GeometricVector& vector1, const GeometricVector& vector2) {
	double vec1X, vec1Y, vec1Z;
	double vec2X, vec2Y, vec2Z;

	vec1X = vector1.getComponentX();
	vec1Y = vector1.getComponentY();
	vec1Z = vector1.getComponentZ();

	vec2X = vector2.getComponentX();
	vec2Y = vector2.getComponentY();
	vec2Z = vector2.getComponentZ();

	return (vec1X * vec2X + vec1Y * vec2Y + vec1Z * vec2Z);
}
GeometricVector vectorAlgebra::crossProduct(const GeometricVector& vector1, const GeometricVector& vector2) {
	double vec1X, vec1Y, vec1Z;
	double vec2X, vec2Y, vec2Z;
	double resx, resy, resz;

	vec1X = vector1.getComponentX();
	vec1Y = vector1.getComponentY();
	vec1Z = vector1.getComponentZ();

	vec2X = vector2.getComponentX();
	vec2Y = vector2.getComponentY();
	vec2Z = vector2.getComponentZ();

	resx = vec1Y * vec2Z - vec2Y * vec1Z;
	resy = (-1) * (vec1X * vec2Z  - vec2X * vec1Z);
	resz = vec1X * vec2Y - vec1Y * vec2X;

	GeometricVector resVector(resx, resy, resz);

	if(!vector1.getVectorName().empty() && !vector2.getVectorName().empty()) {
		resVector.setVectorName("Cross product of " + vector1.getVectorName() + " and " + vector2.getVectorName());
	}

	return resVector;
	
}
double vectorAlgebra::tripleProduct(const GeometricVector& vector1, const GeometricVector& vector2, const GeometricVector& vector3) {
	GeometricVector crProd = vectorAlgebra::crossProduct(vector2, vector3);
	double result = vectorAlgebra::scalarProduct(vector1, crProd);
	return result;
}

double vectorAlgebra::angleBetweenVectors(const GeometricVector& vector1, const GeometricVector& vector2) {
	double temp = vectorAlgebra::scalarProduct(vector1, vector2)/(vector1.getVectorSize() * vector2.getVectorSize());
	return std::acos(temp);
}

double vectorAlgebra::distPointPlane(const GeometricPoint& point, const GeometricPlane& plane) {
	double ptX, ptY, ptZ;
	ptX = point.getx();
	ptY = point.gety();
	ptZ = point.getz();

	GeometricVector tmp(ptX, ptY, ptZ);
	double res = (vectorAlgebra::scalarProduct(tmp, plane.getNormal()) + plane.getCoefficientD())/plane.getNormal().getVectorSize();

	return std::fabs(res);
	
}

double vectorAlgebra::dist2Lines(const GeometricLine& line1, const GeometricLine& line2) {
	GeometricVector pl1(line1.getPoint()); // Make radius vector from point
	GeometricVector pl2(line2.getPoint());

	/* Construct a parallelepiped on vectors (pl2 - pl1), s1, s2,
	 * where s1 -- directing vector of line 1
	 * s2 -- --//--
	 */
	double parallelepiped = vectorAlgebra::tripleProduct((pl2 - pl1), line1.getDirectingVector(), line2.getDirectingVector());
	GeometricVector parallelogram = vectorAlgebra::crossProduct(line1.getDirectingVector(), line2.getDirectingVector());

	double ans = parallelepiped/(parallelogram.getVectorSize());

	return std::fabs(ans);

}

bool vectorAlgebra::vec3Complanary(const GeometricVector& vec1, const GeometricVector& vec2, const GeometricVector& vec3) {
	GeometricVector zeroVec(0.0, 0.0, 0.0);
	if((vec1 == zeroVec) || (vec2 == zeroVec) || (vec3 == zeroVec)) {
		return true; // Complanary
	}

	if(tripleProduct(vec1, vec2, vec3) == 0.0) {
		return true;
	} else {
		return false;
	}
	
}

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
	pointCoords.resize(DEFAULT_DIM);

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

std::string GeometricPoint::getPointName() const {
	return name;
}

double GeometricPoint::getx() const{
	return pointCoords[X_COMP];
}
double GeometricPoint::gety() const{
	return pointCoords[Y_COMP];
}
double GeometricPoint::getz() const{
	return pointCoords[Z_COMP];
}

// GEOMETRIC VECTOR
GeometricVector::GeometricVector() {
	name = "";
}

GeometricVector::GeometricVector(const GeometricPoint& pt) {
	vectorCoords = pt;
	if(!pt.getPointName().empty()) {
		name = pt.getPointName();
	} else {
		name = "";
	}
}
GeometricVector::GeometricVector(const double x, const double y, const double z) {
	vectorCoords.setAllComponents(x, y, z);
}

GeometricVector::GeometricVector(const double x, const double y, const double z, const std::string& vectorName) {
	vectorCoords.setAllComponents(x, y, z);

	name = vectorName;
}
double GeometricVector::getVectorSize() const {
	double origx, origy, origz, size;

	origx = vectorCoords.getx();
	origy = vectorCoords.gety();
	origz = vectorCoords.getz();

	size = std::sqrt(std::pow(origx, 2.0) + std::pow(origy, 2.0) + std::pow(origz, 2.0));

	return size;
	
}
GeometricPoint GeometricVector::getVectorCoords() const {
	return vectorCoords;
	
}
std::string GeometricVector::getVectorName() const {
	return name;
}

void GeometricVector::setVectorCoords(const GeometricPoint& newVectorCoords) {
	vectorCoords = newVectorCoords;
}

void GeometricVector::setVectorName(const std::string& newName) {
	name = newName;
}
	
GeometricVector GeometricVector::operator+(const GeometricVector& vec) {
	double origx, origy, origz;
	double newx, newy, newz;

	origx = vectorCoords.getx();
	origy = vectorCoords.gety();
	origz = vectorCoords.getz();

	newx = vec.vectorCoords.getx();
	newy = vec.vectorCoords.gety();
	newz = vec.vectorCoords.getz();

	double resx, resy, resz;
	resx = origx + newx;
	resy = origy + newy;
	resz = origz + newz;

	GeometricVector res(resx, resy, resz);

	return res;

}

GeometricVector GeometricVector::operator-(const GeometricVector& vec) {
	double origx, origy, origz;
	double newx, newy, newz;

	origx = vectorCoords.getx();
	origy = vectorCoords.gety();
	origz = vectorCoords.getz();

	newx = vec.vectorCoords.getx();
	newy = vec.vectorCoords.gety();
	newz = vec.vectorCoords.getz();

	double resx, resy, resz;
	resx = origx - newx;
	resy = origy - newy;
	resz = origz - newz;

	GeometricVector res(resx, resy, resz);

	return res;
}

GeometricVector GeometricVector::operator*(const double num) {
	double origx, origy, origz;

	origx = vectorCoords.getx();
	origy = vectorCoords.gety();
	origz = vectorCoords.getz();

	double resx, resy, resz;

	resx = origx * num;
	resy = origy * num;
	resz = origz * num;
	
	GeometricVector res(resx, resy, resz);

	return res;
}

bool operator==(const GeometricVector& vector1, const GeometricVector& vector2) {
	double vec1X, vec1Y, vec1Z;
	double vec2X, vec2Y, vec2Z;

	vec1X = vector1.getComponentX();
	vec1Y = vector1.getComponentY();
	vec1Z = vector1.getComponentZ();

	vec2X = vector2.getComponentX();
	vec2Y = vector2.getComponentY();
	vec2Z = vector2.getComponentZ();

	if((vec1X == vec2X) && (vec1Y == vec2Y) && (vec1Z == vec2Z)) {
		return true;
	} else {
		return false;
	}
}
std::ostream& operator<<(std::ostream& os, const GeometricVector& vec) {
	double origx, origy, origz;
	origx = vec.vectorCoords.getx();
	origy = vec.vectorCoords.gety();
	origz = vec.vectorCoords.getz();

	//os << "Vector " << vec.getVectorName() << ": " << std::endl;
	//os << "X: " << vec.vectorCoords.getx() << std::endl;
	//os << "Y: " << vec.vectorCoords.gety() << std::endl;
	//os << "Z: " << vec.vectorCoords.getz() << std::endl;
	if(!vec.getVectorName().empty())
	{
		os << vec.getVectorName() << " = (" << origx << ", " << origy << ", " << origz << ")" << std::endl;
	} else {
		
		os << "(" << origx << ", " << origy << ", " << origz << ")" << std::endl;
	}

	return os;
	
}
double GeometricVector::getComponentX() const {
	return vectorCoords.getx();
}
double GeometricVector::getComponentY() const {
	
	return vectorCoords.gety();
}
double GeometricVector::getComponentZ() const {
	return vectorCoords.getz();
}

// GEOMETRIC LINE
GeometricLine::GeometricLine() {
	name = "";
	
}

GeometricLine::GeometricLine(const GeometricPoint& newPoint, const GeometricVector& dVector, const std::string& lineName) {
	point = newPoint;
	directingVector = dVector;

	name = lineName;
}

GeometricPoint GeometricLine::getPoint() const {
	return point;
}

GeometricVector GeometricLine::getDirectingVector() const {
	return directingVector;
	
}

std::string GeometricLine::getLineName() const {
	return name;
}

// GEOMETRIC PLANE
GeometricPlane::GeometricPlane() {
	name = "";
}

GeometricPlane::GeometricPlane(const GeometricPoint& newPoint, const GeometricVector& newNormal, const std::string& planeName) {
	point = newPoint;
	normal = newNormal;
	name = planeName;

	int A, B, C;
	A = normal.getComponentX();
	B = normal.getComponentY();
	C = normal.getComponentZ();

	int x0, y0, z0;
	x0 = point.getx();
	y0 = point.gety();
	z0 = point.getz();

	D = (-1) * (A * x0 + B * y0 + C * z0);
}

double GeometricPlane::getCoefficientD() const {
	return D;
}

GeometricPoint GeometricPlane::getPoint() const {
	return point;
}

GeometricVector GeometricPlane::getNormal() const {
	return normal;
}
