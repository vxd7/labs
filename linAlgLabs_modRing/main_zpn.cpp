#include "vectorZpN.h"
#include <iostream>
#include <fstream>
#include <vector>

int main() {

	std::ifstream fin;
	fin.open("input.txt");


	int p, n, numberOfVectors;
	fin >> p >> n >> numberOfVectors;

	std::vector<VectorZpN> vecs;

	for(size_t i = 0; i < numberOfVectors; ++i) {
		int component;
		std::vector<int> vectorComps;

		for(size_t j = 0; j < n; ++j) {
			fin >> component;
			vectorComps.push_back(component);
		}

		VectorZpN tmpVec(n, p, vectorComps);
		vecs.push_back(tmpVec);
		
	}

	modFunc::isLinDep(vecs);
	
}
