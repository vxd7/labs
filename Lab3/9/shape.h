#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "geomVector.h"
#include "myMatrix.h"

class spoint {
public:
	spoint();
	spoint(double newx, double newy, double newz);

	double x, y, z;

	//void operator=(spoint &ptn1);
	myvector getRadiusVector();
	void fromVector(myvector vec);

	void setAllCoords(double newX, double newY, double newZ);
	
};

class shape {
public:

	virtual void mkShape() = 0; /*< Pure virtual function -- makes an abstract class */
	virtual void moveShape(myvector moveVector) = 0;
	virtual void rotateShape(double xrot, double yrot, double zrot) = 0;
	virtual void printShape() = 0;

private:
protected:
	int numberOfVectices;
	int numberOfFaces;
	int numberOfEdges;

	spoint rotate_point(spoint& sp, double xrot, double yrot, double zrot);
};

class sphere : public shape {
public:
	sphere();

	void mkShape();
	void mkShape(spoint center, double radius);
	void moveShape(myvector moveVector);
	void rotateShape(double xrot, double yrot, double zrot);

	void printShape();
private:
	spoint ptCenter;
	double rad;
};

class pyramid : public shape {
public:
	pyramid();

	void mkShape();
	void mkShape(spoint top, std::vector <spoint> basePts);
	void moveShape(myvector moveVector);
	void rotateShape(double xrot, double yrot, double zrot);

	void printShape();
private:
	spoint ptTop; /*<Top of the pyramid */
	std::vector <spoint> basepoints;
};

class parallelepiped : public shape {
public:
	parallelepiped();

	void mkShape();
	void mkShape(std::vector <spoint> vertices);
	void moveShape(myvector moveVector);
	void rotateShape(double xrot, double yrot, double zrot);

	void printShape();
protected:
	std::vector <spoint> ptVectices;
	spoint ptCenter;
};

class cube : public parallelepiped { /*< Cube is a three-dimensional solid object bounded by six square faces, with three meeting at each vertex */
public:
	cube();

	void mkShape();
	void mkShape(std::vector <spoint> vertices);
	void moveShape(myvector moveVector);
	void rotateShape(double xrot, double yrot, double zrot);

	void printShape();
private:
};

class cuboid : public parallelepiped { /*< Just a simple rectangular box */
public:
	cuboid();

	void mkShape();
	void mkShape(std::vector <spoint> vertices);
	void moveShape(myvector moveVector);
	void rotateShape(double xrot, double yrot, double zrot);

	void printShape();
private:
};
