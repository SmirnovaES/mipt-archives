#include <iostream>
#include <vector>
#include <cmath>




class SmallMatrix {
public:
	int data[4][4];

	SmallMatrix operator* (const SmallMatrix& A) {
		SmallMatrix res;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
                res.data[i][j] = 0;
				for (int k = 0; k < 4; k++) {
					res.data[i][j] += this->data[i][k] * A.data[k][j];
				}
			}
		}
		return res;
	}

	SmallMatrix get_degree(int deg) {
		SmallMatrix res;
		int maxdeg = 0;
        while(true) {
            if (pow(2, maxdeg) > deg) {
                break;
            }
            maxdeg++;
        }
		std::vector<SmallMatrix> vect(maxdeg);

		vect[0] = *this;
		for (int i = 1; i < maxdeg; i++) {
			vect[i] = vect[i - 1] * vect[i - 1];
		}
		res = vect[maxdeg - 1];
		deg -= pow(2, maxdeg - 1);
		while (deg > 0){
		    maxdeg = 0;
            while(true) {
                if (pow(2, maxdeg) > deg) {
                    break;
                }
                maxdeg++;
            }
			res = res * vect[maxdeg - 1];
			deg -= pow(2, maxdeg - 1);
		}
		return res;
	}
};

int get_degree_of_two(int a) {
	int deg = 0;
	while (true) {
        if (pow (2, deg) > a) return --deg;
        deg++;
	}
}

SmallMatrix get_base_matrix() {
	SmallMatrix base;

	base.data[0][0] = 0;
	base.data[0][1] = 1;
	base.data[0][2] = 0;
	base.data[0][3] = 0;

	base.data[1][0] = 2;
	base.data[1][1] = 0;
	base.data[1][2] = 1;
	base.data[1][3] = 0;

	base.data[2][0] = 0;
	base.data[2][1] = 2;
	base.data[2][2] = 0;
	base.data[2][3] = 2;

	base.data[3][0] = 0;
	base.data[3][1] = 0;
	base.data[3][2] = 1;
	base.data[3][3] = 0;

	return base;
}

int main() {
	int n;
	std::cin >> n;
	SmallMatrix matr = get_base_matrix();
	matr = matr.get_degree(n - 1);

	unsigned long long res = 0;

	std::vector<int> n0;
	n0.push_back(0);
	n0.push_back(2);
	n0.push_back(4);
	n0.push_back(1);
	for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res += ((unsigned long long) matr.data[i][j]) * n0[j];
        }
	}
	std::cout << res << std::endl;

}

