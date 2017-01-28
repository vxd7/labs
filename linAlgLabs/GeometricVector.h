#pragma once

#include <string>
#include <sstream>
#include <vector>

#define DEFAULT_DIM 3

class GeometricPoint;
class GeometricVector;
class GeometricLine;
class GeometricPlane;

/******************
 * SOME FUNCTIONS *
 ******************/
namespace vectorAlgebra {

	/*
	 * Vector products
	 */
	double scalarProduct(const GeometricVector& vector1, const GeometricVector& vector2); // Скалярное произведение
	GeometricVector crossProduct(const GeometricVector& vector1, const GeometricVector& vector2); // Векторное произведение
	double tripleProduct(const GeometricVector& vector1, const GeometricVector& vector2, const GeometricVector& vector3); // Смешанное произведение

	/*
	 * Misc functions
	 */
	double angleBetweenVectors(const GeometricVector& vector1, const GeometricVector& vector2);
	double distPointPlane(GeometricPoint point, GeometricPlane plane);
	double dist2Lines(GeometricLine line1, GeometricLine line2);
}

/*******************
 * GEOMETRIC POINT *
 *******************/
enum componentName {X_COMP = 0, Y_COMP, Z_COMP};

class GeometricPoint {
private:
	std::string name;

	//int dimensionCount;
	std::vector<double> pointCoords;

public:
	GeometricPoint();
	//GeometricPoint(const int newDimensionCount, const std::vector<double>& newPointCoords, const std::string& pointName);
	GeometricPoint(const double newx, const double newy, const double newz, const std::string& pointName);

	void setAllComponents(const double newx, const double newy, const double newz);
	double getComponent(const componentName& compName) const;
	void setComponent(const componentName& compName, const double newComponent);
};

/********************
 * GEOMETRIC VECTOR *
 ********************/
class GeometricVector {
private:
	GeometricPoint vectorCoords;
	std::string name;

public:
	GeometricVector();
	GeometricVector(const double x, const double y, const double z, const std::string& vectorName);

	double getVectorSize() const;
	GeometricPoint getVectorCoords() const;
	std::string getVectorName() const;

	void setVectorCoords(const GeometricPoint& vectorCoords);
	void setVectorName(const std::string& newName);

	GeometricVector operator+(const GeometricVector& vec);
	GeometricVector operator-(const GeometricVector& vec);
	GeometricVector operator*(const double num);

	friend std::ostream& operator<<(std::ostream& os, const GeometricVector& vec);

};

/********************
 * GEOMETRIC LINE   *
 ********************/
class GeometricLine {
private:
	std::string name;

	GeometricPoint point;
	GeometricVector directingVector;
public:
	GeometricLine();
	GeometricLine(const GeometricPoint& point, const GeometricVector& vec, const std::string& lineName);

	std::string getLineName;
	
};

/********************
 * GEOMETRIC PLANE  *
 ********************/
class GeometricPlane {
private:
	std::string name;

	GeometricPoint point;
	GeometricVector normal;

	std::vector<double> planeEquationCoefficients;
public:
	GeometricPlane();
	GeometricPlane(const GeometricPoint& point, const GeometricVector& normal, const std::string& planeName);
	
};
