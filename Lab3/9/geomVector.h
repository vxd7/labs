#pragma once
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

private:
	double x;
	double y;
	double z;
};

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
