#include <iostream>
#include <vector>
#include <ctime>

int main()
{
	std::srand(std::time(0));
	int m1r, m1c, m2r, m2c;
	std::cout << "Matrix 1" << std::endl;
	std::cout << "ROWS: ";
	std::cin >> m1r;
	std::cout << "COLS: ";
	std::cin >> m1c;
	std::cout <<std::endl;


	std::cout << "Matrix 2" << std::endl;
	std::cout << "ROWS: ";
	std::cin >> m2r;
	std::cout << "COLS: ";
	std::cin >> m2c;
	std::cout <<std::endl;

	if(m1c != m2r) {
		std::cerr << "Incorrect sizes! Can't multiply!" << std::endl;
		exit(1);
	}

	std::vector <std::vector<int>> m1;
	std::vector <std::vector<int>> m2;
	std::vector <std::vector<int>> res;

	m1.resize(m1r);
	for(size_t i = 0; i < m1r; i++) {
		m1[i].resize(m1c);
	}

	m2.resize(m2c);
	for(size_t i = 0; i < m2c; i++) {
		m2[i].resize(m2r);
	}

	res.resize(m1r);
	for(size_t i = 0; i < m1r; i++) {
		res[i].resize(m2c);
	}

	std::cout << m1.size() << " " << m1[0].size() << std::endl;

	/**
	 * Input everything
	 */
	std::cout << "Matrix 1 input: " << std::endl;
	for(size_t i = 0; i < m1r; i++) {
		for(size_t j = 0; j < m1c; j++) {
			//std::cout << "m1[" << i << "][" << j << "] = ";
			//std::cin >> m1[i][j];
			m1[i][j] = std::rand() % 100 + 1;
		}
		//std::cout << std::endl;
	}

	std::cout << "Matrix 2 input: " << std::endl;
	for(size_t i = 0; i < m2c; i++) {
		for(size_t j = 0; j < m2r; j++) {
			//std::cout << "m2[" << j << "][" << i << "] = ";
			//std::cin >> m2[i][j];
			m2[i][j] = std::rand() % 100 + 1;
		}
	}

	/**
	 * Test output everything
	 */
	std::cout << std::endl;
	std::cout << "---Matrix 1:--- " << std::endl;
	for(size_t i = 0; i < m1r; i++) {
		for(size_t j = 0; j < m1c; j++) {
			std::cout << "m1[" << i << "][" << j << "] = " << m1[i][j] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << "---Matrix 2:--- " << std::endl;
	for(size_t i = 0; i < m2c; i++) {
		for(size_t j = 0; j < m2r; j++) {
			std::cout << "m2[" << j << "][" << i << "] = " << m2[i][j] << " ";
		}
		std::cout << std::endl;
	}

	/**
	 * Actually multiply
	 */
	for(size_t i = 0; i < m1r; i++) {
		for(size_t k = 0; k < m2c; k++) {
			size_t j;
			int sum = 0;
			for(j = 0; j < m2r; j++) {
				sum += m1[i][j] * m2[k][j];
			}
			res[i][k] = sum;
		}
	}

	/**
	 * Output the result
	 */
	std::cout << std::endl;
	std::cout << "---RES:--- " << std::endl;
	for(size_t i = 0; i < res.size(); i++) {
		for(size_t j = 0; j < res[i].size(); j++) {
			std::cout << "res[" << i << "][" << j << "] = " << res[i][j] << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}
