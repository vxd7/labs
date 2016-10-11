#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "geomVector.h"

class spoint {
public:
	double x, y;
};

class shape {
public:
	shape();
	~shape();

	virtual void mkShape() = 0; /*< Pure virtual function -- makes an abstract class */
	virtual void moveShape(myvector moveVector) = 0;
	virtual void rotateShape() = 0;

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

	void mkShape(spoint center, double rad);
	void moveShape(myvector moveVector);
	void rotateShape();
private:
	spoint ptCenter;
	double rad;
};

class pyramid : public shape {
public:
	pyramid();
	~pyramid();

	void mkShape(spoint top, std::vector <spoint> basePts);
	void moveShape(myvector moveVector);
	void rotateShape();
private:
	spoint ptTop; /*<Top of the pyramid */
	std::vector <spoint> basespoints;
};

class parallelepiped : public shape {
public:
	parallelepiped();
	~parallelepiped();

	void mkShape(std::vector <spoint> vertices);
	void moveShape(myvector moveVector);
	void rotateShape();
protected:
	std::vector <spoint> ptVectices;
	spoint ptCenter;
};

class cube : public parallelepiped { /*< Cube is a three-dimensional solid object bounded by six square faces, with three meeting at each vertex */
public:
	cube();
	~cube();

	void mkShape(std::vector <spoint> vertices);
	void moveShape(myvector moveVector);
	void rotateShape();
private:
	spoint ptCenter;
};

class cuboid : public parallelepiped { /*< Just a simple rectangular box */
public:
	cuboid();
	~cuboid();

	void mkShape(std::vector <spoint> vertices);
	void moveShape(myvector moveVector);
	void rotateShape();
private:
	spoint ptCenter;
};
