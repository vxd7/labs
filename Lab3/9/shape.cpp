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
myvector spoint::getVectorForm()
{
	return myvector(
}

/*
 * ----- Sphere -----
 */
void sphere::mkShape(spoint center, double radius)
{
	ptCenter = center;
	rad = radius;
}

void sphere::moveShape(myvector moveVector)
{
	
}
