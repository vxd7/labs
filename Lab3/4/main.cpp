#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

class point {
public:
	double getx() const;
	double gety() const;
	double getz() const;

	void setx(const double newx);
	void sety(const double newy);
	void setz(const double newz);
	void setxyz(const double newx, const double newy, const double newz);

	point();
	point(const double newx, const double newy, const double newz);

	~point();
private:
	double x;
	double y;
	double z;
};

double point::getx() const
{
	return x;
}
double point::gety() const
{
	return y;
}
double point::getz() const
{
	return z;
}

void point::setx(const double newx)
{
	x = newx;
}
void point::sety(const double newy)
{
	y = newy;
}
void point::setz(const double newz)
{
	z = newz;
}

void point::setxyz(const double newx, const double newy, const double newz)
{
	x = newx;
	y = newy;
	z = newz;
}

point::point()
{
	x = 0;
	y = 0;
	z = 0;
}
point::point(const double newx, const double newy, const double newz)
{
	setxyz(newx, newy, newz);
}

point::~point()
{
	
}

//////////////////////////////////////////////////////////////////////
class myvector {
public:
	double getVectorSize() const;
	point getVectorCoords() const;
	std::string getVectorName() const;

	void setVectorCoords(const point& vecStart);
	void setVectorName(const std::string& newName);

	double scProd(const myvector& vec); /**< Scalar product */
	void crProd(const myvector& vec); /**< Cross product */

	myvector operator+(const myvector& vec);
	myvector operator-(const myvector& vec);
	myvector operator*(const double num);

	friend std::ostream& operator<<(std::ostream& os, const myvector& vec);
	myvector();
	myvector(const double x, const double y, const double z, std::string newName = "");
	~myvector();


private:
	double size;
	point vectorCoords;
	std::string name;

	double calculateSize();
};

double myvector::getVectorSize() const
{
	return size;
}

point myvector::getVectorCoords() const
{
	return point(vectorCoords.getx(), vectorCoords.gety(), vectorCoords.getz());
}

void myvector::setVectorCoords(const point& vecStart)
{
	vectorCoords.setxyz(vecStart.getx(), vecStart.gety(), vecStart.getz());
	calculateSize();
}

double myvector::scProd(const myvector& vec) /**< Scalar product */
{
	double origx, origy, origz;
	double newx, newy, newz;

	origx = vectorCoords.getx();
	origy = vectorCoords.gety();
	origz = vectorCoords.getz();

	newx = vec.vectorCoords.getx();
	newy = vec.vectorCoords.gety();
	newz = vec.vectorCoords.getz();

	return (origx * newx + origy * newy + origz * newz);
	
}
void myvector::crProd(const myvector& vec) /**< Cross product */
{
	double origx, origy, origz;
	double newx, newy, newz;

	origx = vectorCoords.getx();
	origy = vectorCoords.gety();
	origz = vectorCoords.getz();

	newx = vec.vectorCoords.getx();
	newy = vec.vectorCoords.gety();
	newz = vec.vectorCoords.getz();

	double crProd_x, crProd_y, crProd_z;
	crProd_x = origz * newy - origy * newz;
	crProd_y = origx * newz - origz * newx;
	crProd_z = origy * newx - origx * newy;

	crProd_x *= (-1);
	crProd_y *= (-1);
	crProd_z *= (-1);

	vectorCoords.setxyz(crProd_x, crProd_y, crProd_z);
	calculateSize(); /* Renew the size of the vector */

}

myvector myvector::operator+(const myvector& vec)
{
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

	myvector res(resx, resy, resz);
	res.calculateSize();

	return res;

}
myvector myvector::operator-(const myvector& vec)
{
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

	myvector res(resx, resy, resz);
	res.calculateSize();

	return res;
}
myvector myvector::operator*(const double num)
{
	double origx, origy, origz;

	origx = vectorCoords.getx();
	origy = vectorCoords.gety();
	origz = vectorCoords.getz();

	double resx, resy, resz;

	resx = origx * num;
	resy = origy * num;
	resz = origz * num;

	myvector res(resx, resy, resz);
	res.calculateSize();

	return res;
}

myvector::myvector()
{
	
}
myvector::myvector(const double x, const double y, const double z, std::string newName)
{

	name = newName;
	vectorCoords.setxyz(x, y, z);
	calculateSize();
	
}
myvector::~myvector()
{
	
}

double myvector::calculateSize()
{
	double origx, origy, origz;
	origx = vectorCoords.getx();
	origy = vectorCoords.gety();
	origz = vectorCoords.getz();

	size = std::sqrt(std::pow(origx, 2.0) + std::pow(origy, 2.0) + std::pow(origz, 2.0));

	return size;
}

std::ostream& operator<<(std::ostream& os, const myvector& vec)
{
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

void myvector::setVectorName(const std::string& newName)
{
	name = newName;
}

std::string myvector::getVectorName() const
{
	return name;
}

int main()
{
	myvector vec1(6.0, 7.0, 10.0, "vec1");
	myvector vec2(8.0, 5.0, 9.0, "vec2");

	std::cout << vec1 << vec2;

	//std::cout <<"(" << vec1.getVectorName() << ", " << vec2.getVectorName() << ") = " << vec1.scProd(vec2) << std::endl;
	//vec1.crProd(vec2);
	//std::cout << "[" << vec1.getVectorName() << ", " << vec2.getVectorName() << "] = " << vec1;

	myvector vec3 = vec1 + vec2;
	vec3.setVectorName("VEC#3");
	std::cout << vec1 << vec2 << vec3;

	return 0;
}
