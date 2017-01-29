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
	double distPointPlane(const GeometricPoint& point, const GeometricPlane& plane);
	double dist2Lines(const GeometricLine& line1, const GeometricLine& line2);
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

	double getComponent(const componentName& compName) const;
	std::string getPointName() const;

	void setAllComponents(const double newx, const double newy, const double newz);
	void setComponent(const componentName& compName, const double newComponent);
	double getx() const;
	double gety() const;
	double getz() const;
	
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
	GeometricVector(const GeometricPoint& pt);
	GeometricVector(const double x, const double y, const double z);
	GeometricVector(const double x, const double y, const double z, const std::string& vectorName);

	double getVectorSize() const;
	GeometricPoint getVectorCoords() const;
	std::string getVectorName() const;

	void setVectorCoords(const GeometricPoint& newVectorCoords);
	void setVectorName(const std::string& newName);

	GeometricVector operator+(const GeometricVector& vec);
	GeometricVector operator-(const GeometricVector& vec);
	GeometricVector operator*(const double num);

	friend std::ostream& operator<<(std::ostream& os, const GeometricVector& vec);

	double getComponentX() const;
	double getComponentY() const;
	double getComponentZ() const;

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
	GeometricLine(const GeometricPoint& newPoint, const GeometricVector& dVector, const std::string& lineName);
	
	std::string getLineName() const;
	
};

/********************
 * GEOMETRIC PLANE  *
 ********************/
class GeometricPlane {
private:
	std::string name;

	GeometricPoint point;
	GeometricVector normal;

	double D; //Plane coeff.
public:
	GeometricPlane();
	GeometricPlane(const GeometricPoint& newPoint, const GeometricVector& newNormal, const std::string& planeName);


	double getCoefficientD() const;
	GeometricVector getNormal() const; 
	
};
