#include "shape.h"

spoint shape::rotate_point(spoint& sp, double xrot, double yrot, double zrot)
{
	myMatrix rotX, rotY, rotZ;
	myMatrix centerVecMatrix;

	centerVecMatrix.makeMatrixFromVector(sp.getRadiusVector());

	rotX.makeRotMatrix("X", xrot);
	rotY.makeRotMatrix("Y", yrot);
	rotZ.makeRotMatrix("Z", zrot);

	myMatrix res = rotX * centerVecMatrix;
	res = rotY * res;
	res = rotZ * res;

	spoint resPoint;
	resPoint.x = res.matrix[0][0];
	resPoint.y = res.matrix[1][0];
	resPoint.z = res.matrix[2][0];
	
	return resPoint;
}

spoint::spoint()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}
spoint::spoint(double newx, double newy, double newz)
{
	x = newx;
	y = newy;
	z = newz;
}

//void spoint::operator=(spoint &ptn1)
//{
//	x = ptn1.x;
//	y = ptn1.y;
//	z = ptn1.z;
//}
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
void spoint::setAllCoords(double newX, double newY, double newZ)
{
	x = newX;
	y = newY;
	z = newZ;
}

/*
 * ----- Sphere -----
 */


sphere::sphere()
{
	
}

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
	ptCenter = rotate_point(ptCenter, xrot, yrot, zrot);
	
}

void sphere::printShape()
{
	std::cout << "Sphere" << std::endl;
	std::cout << "Center: (" << ptCenter.x << ", " << ptCenter.y << ", " << ptCenter.z << ")" << std::endl;
	std::cout << "Radius: " << rad << std::endl;
}
/**
 * ----- Pyramid -----
 */

pyramid::pyramid()
{
	
}

/**
 * Make a generic pyramid
 * Square base
 */
void pyramid::mkShape()
{
	spoint bp[5];
	bp[1].setAllCoords(1.0, 0.0, 0.0);
	bp[2].setAllCoords(0.0, 0.0, 1.0);
	bp[3].setAllCoords(-1.0, 0.0, 0.0);
	bp[4].setAllCoords(0.0, 0.0, -1.0);

	basepoints.push_back(bp[1]);
	basepoints.push_back(bp[2]);
	basepoints.push_back(bp[3]);
	basepoints.push_back(bp[4]);

	ptTop.setAllCoords(0.0, 1.0, 0.0);
	
}
void pyramid::mkShape(spoint top, std::vector <spoint> basePts)
{
	if(basePts.size() < 3) {
		std::cerr << "Error! Pyramid can't have less than 3 basepoints!";
	}

	basepoints = basePts;
	ptTop = top;
}
void pyramid::moveShape(myvector moveVector)
{
	/**
	 * Move all the basepoints
	 */
	for(size_t i = 0; i < basepoints.size(); ++i) {
		basepoints[i].fromVector(basepoints[i].getRadiusVector() + moveVector);
	}

	/**
	 * Move the top
	 */
	ptTop.fromVector(ptTop.getRadiusVector() + moveVector);
	
}
void pyramid::rotateShape(double xrot, double yrot, double zrot)
{
	/**
	 * Rotate all the points of the base
	 */
	for(size_t i = 0; i < basepoints.size(); ++i) {
		basepoints[i] = rotate_point(basepoints[i], xrot, yrot, zrot);
	}

	/**
	 * Rotate the top point
	 */
	ptTop = rotate_point(ptTop, xrot, yrot, zrot);
	
}

void pyramid::printShape()
{
	std::cout << "Pyramid: " << std::endl;
	std::cout << "basepoints:" << std::endl;
	std::cout << "-----------" << std::endl;

	for(size_t i = 0; i < basepoints.size(); ++i) {

		std::cout << "Point " << i << ": " << "(" << basepoints[i].x << ", " << basepoints[i].y << ", " << 
			basepoints[i].z << ")" << std::endl;
	}
	std::cout << "-----------" << std::endl;
	std::cout << "Top: " << "(" << ptTop.x << ", " << ptTop.y << ", " << ptTop.z << ")" << std::endl;
}
