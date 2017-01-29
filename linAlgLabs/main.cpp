#include <iostream>
#include "GeometricVector.h"

int main() {
	GeometricVector v1(1.0, 2.0, 3.0, "v1");
	GeometricVector v2(34.0, 23.9, 12.3, "v2");
	GeometricVector v3(11.355, 56.444, 33.2,"v3");

	std::cout << v1 << v2 << v3;
	std::cout << std::endl;

	GeometricVector sumV1V2 = v1 + v2;
	sumV1V2.setVectorName("Sum of v1 and v2");
	std::cout << sumV1V2;

	GeometricVector subV1V2 = v1 - v2;
	subV1V2.setVectorName("V1 - V2");
	std::cout << subV1V2;

	GeometricVector mulV1Num = v1 * 55.0;
	mulV1Num.setVectorName("v1 * 55");
	std::cout << mulV1Num;

	std::cout << "Scalar product of v1 and v2 ";
	std::cout << vectorAlgebra::scalarProduct(v1,v2) << std::endl;

	std::cout << vectorAlgebra::crossProduct(v1, v2) << std::endl;

	std::cout << "Triple prod of v1, v2,v3: " << vectorAlgebra::tripleProduct(v1, v2, v3);

	GeometricVector planeNormal(1.0, -1.0, 0.0);
	GeometricPoint planePt(1.0,1.0,1.0, "pt");
	GeometricPlane myplane(planePt, planeNormal, "");

	GeometricPoint P(2.0, 0.0, 1.0, "");

	std::cout << std::endl;
	std::cout << "dist Point Plane: " << vectorAlgebra::distPointPlane(P, myplane);

	std::cout << std::endl << "dist line line: ";

	GeometricPoint line1pt(1.0, 0.0, 0.0, "pt");
	GeometricVector line1vec(1.0, 0.0, 0.0);

	GeometricPoint line2pt(0.0, 2.0, 1.0, "pt");
	GeometricVector line2vec(0.0, 0.0, 1.0);

	GeometricLine l1(line1pt, line1vec, "l");
	GeometricLine l2(line2pt, line2vec, "l");

	std::cout << vectorAlgebra::dist2Lines(l1, l2);

	// GeometricVector vec1(1.0, 2.0, 3.0);
	// GeometricVector vec2(1.0, 1.0, 1.0);
	// GeometricVector vec3(1.0, 2.0, 1.0);
	GeometricVector vec1(1.0, 1.0, 1.0);
	GeometricVector vec2(1.0, 3.0, 1.0);
	GeometricVector vec3(2.0, 2.0, 2.0);

	std::cout << std::endl;
	if(vectorAlgebra::vec3Complanary(vec1, vec2, vec3)) {
		std::cout << "Complanary";
	} else {
		std::cout << "Not complanary";
	}



	return 0;
}
