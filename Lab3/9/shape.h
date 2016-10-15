#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "geomVector.h"
#include "myMatrix.h"

class spoint {
public:
	spoint(double newx, double newy, double newz);

	double x, y, z;

	void operator=(spoint &ptn1);
	myvector getRadiusVector();
	void fromVector(myvector vec);
	
};

class shape {
public:
	shape();
	~shape();

	virtual void mkShape() = 0; /*< Pure virtual function -- makes an abstract class */
	virtual void moveShape(myvector moveVector) = 0;
	virtual void rotateShape(double xrot, double yrot, double zrot) = 0;

private:
protected:
	int numberOfVectices;
	int numberOfFaces;
	int numberOfEdges;
};

class sphere : public shape {
public:
	sphere();
	~sphere();

	void mkShape();
	void mkShape(spoint center, double radius);
	void moveShape(myvector moveVector);
	void rotateShape(double xrot, double yrot, double zrot);
private:
	spoint ptCenter;
	double rad;
};

class pyramid : public shape {
public:
	pyramid();
	~pyramid();

	void mkShape();
	void mkShape(spoint top, std::vector <spoint> basePts);
	void moveShape(myvector moveVector);
	void rotateShape(double xrot, double yrot, double zrot);
private:
	spoint ptTop; /*<Top of the pyramid */
	std::vector <spoint> basespoints;
};

class parallelepiped : public shape {
public:
	parallelepiped();
	~parallelepiped();

	void mkShape();
	void mkShape(std::vector <spoint> vertices);
	void moveShape(myvector moveVector);
	void rotateShape(double xrot, double yrot, double zrot);
protected:
	std::vector <spoint> ptVectices;
	spoint ptCenter;
};

class cube : public parallelepiped { /*< Cube is a three-dimensional solid object bounded by six square faces, with three meeting at each vertex */
public:
	cube();
	~cube();

	void mkShape();
	void mkShape(std::vector <spoint> vertices);
	void moveShape(myvector moveVector);
	void rotateShape(double xrot, double yrot, double zrot);
private:
};

class cuboid : public parallelepiped { /*< Just a simple rectangular box */
public:
	cuboid();
	~cuboid();

	void mkShape();
	void mkShape(std::vector <spoint> vertices);
	void moveShape(myvector moveVector);
	void rotateShape(double xrot, double yrot, double zrot);
private:
};
