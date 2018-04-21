#include <iostream>
#include <vector>
#include <climits>
#include <math.h>


template <typename type> class Matrix {
public:
    Matrix(int new_height = 0, int new_width = 0) {
        height = new_height;
        width = new_width;
        data.resize(height);
        for (int i = 0; i < height; i++) {
            data[i].resize(width);
        }
    }

    Matrix(const std::vector <std::vector <type>>& new_data) {
        height = new_data.size();
        width = new_data[0].size();
        data.resize(height);
        for (int i = 0; i < height; i++) {
            data[i].resize(width);
            for (int j = 0; j < width; j++) {
                data[i][j] = new_data[i][j];
            }
        }
    }

    Matrix(const Matrix& A) {
        height = A.get_height();
        width = A.get_width();
        data.resize(height);
        for (int i = 0; i < height; i++) {
            data[i].resize(width);
            for (int j = 0; j < width; j++) {
                data[i][j] = A.data[i][j];
            }
        }
    }

    int get_width() const{
        return width;
    }

    int get_height() const{
        return height;
    }

    Matrix& operator= (const Matrix& A) {
		height = A.get_height();
		width = A.get_width();

		data.resize(height);

		for (int i = 0; i < height; ++i) {
            data[i].resize(width);
			for (int j = 0; j < width; ++j) {
				data[i][j] = A.data[i][j];
			}
		}
		return *this;
	}

	bool operator== (const Matrix& A) {
        if (height != A.get_height() || width != A.get_width()) return false;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (data[i][j] != A.data[i][j]) return false;
            }
        }
        return true;
	}

	std::vector<type>& operator[] (int row) {
		return data[row];
	}

	const std::vector<type>& operator[] (int row) const {
        return data[row];
	}

    Matrix operator+ (const Matrix& A) {
        if (height != A.get_height() || width != A.get_width()) {
           std::cerr << "Error: wrong matrix sizes.\n";
        }
        Matrix res(A.get_height(), A.get_width());
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                res[i][j] = data[i][j] + A[i][j];
            }
        }
        return res;
    }

    Matrix& operator+= (const Matrix& A) {
        *this = *this + A;
        return *this;
    }

    Matrix operator- (const Matrix& A) {
        if (height != A.get_height() || width != A.get_width()) {
           std::cerr << "Error: wrong matrix sizes.\n";
        }
        Matrix res(A.get_height(), A.get_width());
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                res[i][j] = data[i][j] - A[i][j];
            }
        }
        return res;
    }

    Matrix& operator-= (const Matrix& A) {
        *this = *this - A;
        return this;
    }

    Matrix operator* (const Matrix& A) {
        if (width != A.get_height()) {
            std::cerr << "Error: wrong matrix sizes.\n";
        }
        Matrix res(A.get_height(), A.get_width());
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < A.get_width(); j++) {
                int curr_ans = 0;
                for (int k = 0; k < width; k++) {
                    curr_ans += data[i][k] * A[k][j];
                }
                res[i][j] = curr_ans;
            }
        }
        return res;
    }

    Matrix& operator*= (const Matrix& A) {
        *this = *this * A;
        return this;
    }

    Matrix operator* (type x) {
        Matrix res(*this);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                res.data[i][j] *= x;
            }
        }
        return res;
    }

    Matrix get_degree(int deg) {
		if (height != width) {
			std::cerr << "Error: wrong matrix sizes.\n";
		}

		Matrix<type> res;
		int maxdeg = 0;
        while(true) {
            if (pow(2, maxdeg) > deg) {
                break;
            }
            maxdeg++;
        }

		std::vector<Matrix<type>> vect(maxdeg);

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
			res = res * vect[maxdeg];
			deg -= pow(2, maxdeg);
		}
		return res;
	}

    friend type get_determinant(Matrix A) {
        if (A.height != A.width) {
            std::cerr << "Error: wrong matrix sizes.\n";
        }
        type det = static_cast<type>(0);
        if (A.height == 1 && A.width == 1) return A.data[0][0];
		for (int i = 0; i < A.height; ++i) {
			det += A.data[0][i] * static_cast<type>(pow(-1.0, i)) * get_determinant(A.get_cofactor(0, i));
		}
		return det;
    }

    Matrix get_reverse() {
        if (get_determinant(*this) == static_cast<type>(0)) {
           std::cerr << "Error: can not reverse matrix.\n";
        }
        Matrix res(height, width);
		res = (this->get_allied() * (1 / get_determinant(*this))).get_transposition();
		return res;
    }

    Matrix get_transposition() {
        Matrix transp(height, width);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                transp[i][j] = data[j][i];
            }
        }
        return transp;
    }

    type get_trace() {
        if (height != width) {
           std::cerr << "Error: wrong matrix size.\n";
        }
        type trace = static_cast<type>(0);
        for (int i = 0; i < height; i++) {
            trace += data[i][i];
        }
        return trace;
    }

    Matrix operator/ (const Matrix& A) {
        return *this * A.get_reverse();
    }

    friend std::ostream& operator<< (std::ostream& out, const Matrix& A) {
        for (int i = 0; i < A.get_height(); i++) {
            for (int j = 0; j < A.get_width(); j++) {
                out << A[i][j] << " ";
            }
            out << std::endl;
        }
        return out;
    }

    friend std::istream& operator>> (std::istream& in, Matrix& A) {
        for (int i = 0; i < A.get_height(); ++i)
            for (int j = 0; j < A.get_width(); ++j)
                in >> A[i][j];
        return in;
    }


private:
    std::vector <std::vector <type>> data;
    int width, height;

    Matrix get_cofactor(int row, int column) {
        Matrix res(height - 1, width - 1);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (i < row && j < column) {
                    res.data[i][j] = data[i][j];
                } else if (i < row && j > column) {
                    res.data[i][j - 1] = data[i][j];
                } else if (i > row && j < column) {
                    res.data[i - 1][j] = data[i][j];
                } else if (i > row && j > column) {
                    res.data[i - 1][j - 1] = data[i][j];
                }
            }
        }
        return res;
    }

    Matrix get_allied() {
		Matrix res(height, width);
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				res[i][j] = static_cast<type>(pow(-1.0, i + j)) * get_determinant(get_cofactor(i, j));
			}
		}
		return res;
	}
};



int main() {
    int rows_1 = 0;
    int columns_1 = 0;
    int i, j, k;
	std::cout << "Enter number of rows and columns of matrix A:\n";
	std::cin >> rows_1 >> columns_1;
	Matrix<float> A(rows_1, columns_1);
	std::cout << "Enter matrix values:\n" ;
	std::cin >> A;

	int rows_2 = 0;
	int columns_2 = 0;
	std::cout << "Enter number of rows and columns of matrix B:\n";
	std::cin >> rows_2 >> columns_2;
	Matrix<float> B(rows_2, columns_2);
	std::cout << "Enter matrix values:\n" ;
	std::cin >> B;


	std::cout << "Enter index of element which you would like to see:\n";
	std::cin >> i >> j;

	std::cout << "Enter random number:\n";
	std::cin >> k;


    std::cout << "Determinant of matrix A is " << get_determinant(A) << std::endl;
	std::cout << "Trace of matrix A is " << A.get_trace() << std::endl;
	std::cout << "Transposition of matrix A is \n" << A.get_transposition() << std::endl;
	std::cout << "Inverse of matrix A is \n" << A.get_reverse() << std::endl;
	std::cout << "A + B = \n" << A + B << std::endl;
	std::cout << "A - B = \n" << A - B << std::endl;
	std::cout << "A * B = \n" << A * B << std::endl;
	std::cout << "Matrix A in " << k << " degree is \n" << std::endl << A.get_degree(k) << std::endl;
	std::cout << "A[" << i << "][" << j << "] = " << A[i][j] << std::endl << std::endl;
	std::cout << "A * " << k << " = \n" << A * k << std::endl;
}
