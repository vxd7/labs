#include "shape.h"

spoint::spoint(double newx, double newy, double newz)
{
	x = newx;
	y = newy;
	z = newz;
}

void spoint::operator=(spoint &ptn1)
{
	x = ptn1.x;
	y = ptn1.y;
	z = ptn1.z;
}
myvector spoint::getRadiusVector()
{
	return myvector(x, y, z);
}

void spoint::fromVector(myvector vec)
{
	x = vec.getVectorCoords().getx();
	y = vec.getVectorCoords().gety();
	z = vec.getVectorCoords().getz();
}

/*
 * ----- Sphere -----
 */

/**
 * Make a generic sphere,
 * i.e. position of the center is at (0,0,0)
 * and radius is 1
 */
void sphere::mkShape()
{
	mkShape(spoint(0.0, 0.0, 0.0), 1.0);
}

void sphere::mkShape(spoint center, double radius)
{
	ptCenter = center;
	rad = radius;
}

void sphere::moveShape(myvector moveVector)
{
	ptCenter.fromVector(ptCenter.getRadiusVector() + moveVector);
}

void sphere::rotateShape(double xrot, double yrot, double zrot)
{
	myMatrix rotX, rotY, rotZ;
	myMatrix centerVecMatrix;

	centerVecMatrix.makeMatrixFromVector(ptCenter.getRadiusVector());

	rotX.makeRotMatrix("X", xrot);
	rotY.makeRotMatrix("Y", yrot);
	rotZ.makeRotMatrix("Z", zrot);

	myMatrix res = rotX * rotY * rotZ * centerVecMatrix;

	ptCenter.x = res.matrix[0][0];
	ptCenter.y = res.matrix[1][0];
	ptCenter.z = res.matrix[2][0];
	
}

/**
 * ----- Pyramid -----
 */

