#include "vectorZp.h"
#include <iostream>

int main() {
	int mod = 199;
	VectorZp vec1(100, -100, 289, mod);
	VectorZp vec2(1000, 1000, 1000, mod);

	std::cout << modFunc::scalarProductZp(vec1, vec2);

	//----------------
	std::cout << std::endl;
	VectorZp vv1(160, 50, 165, mod);
	VectorZp vv2(87, 59, -155, mod);
	VectorZp vv3(181, 165, 146, mod);
	VectorZp vv4(82, 84, 80, mod);
	VectorZp vv5(23, -119, -92, mod);
	VectorZp vv6(35, -60, -33, mod);
	VectorZp vv7(40, 102, 61, mod);
	
	std::vector<VectorZp> vecs;
	vecs.push_back(vv1);
	vecs.push_back(vv2);
	vecs.push_back(vv3);
	vecs.push_back(vv4);
	vecs.push_back(vv5);
	vecs.push_back(vv6);
	vecs.push_back(vv7);

	if(modFunc::isLinDep(vecs)) {
		std::cout << "DEP";
	} else {
		std::cout << "NON DEP";
	}

	return 0;
}
