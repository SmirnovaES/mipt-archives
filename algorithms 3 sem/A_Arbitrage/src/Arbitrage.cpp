#include "../tests/Arbitrage.h"


Arbitrage::Arbitrage() {}

std::istream& operator>>(std::istream& in, Arbitrage& arb) {
    int size;
    in >> size;
    arb.matrix.resize(size);
    double curr_number;
    for (int i = 0; i < size; ++i) {
        arb.matrix[i].resize(size);
        for (int j = 0; j < size; ++j) {
            if (i == j) {
                arb.matrix[i][j] = 1;
            } else {
                in >> curr_number;
                arb.matrix[i][j] = 1 / curr_number;
            }
        }
    }
    arb.matrix_copy = arb.matrix;
    return in;
}

void Arbitrage::generate_min_distance() {
    for (int k = 0; k < matrix_copy.size(); ++k) {
        for (int i = 0; i < matrix_copy.size(); ++i) {
            for (int j = 0; j < matrix_copy.size(); ++j) {
                if (matrix_copy[i][k] != -1 && matrix_copy[k][j] != -1) {
                    if (matrix_copy[i][j] == -1) {
                        matrix_copy[i][j] = matrix_copy[i][k] * matrix_copy[k][j];
                    } else if (matrix_copy[i][k] * matrix_copy[k][j] < matrix_copy[i][j]) {
                        matrix_copy[i][j] = matrix_copy[i][k] * matrix_copy[k][j];
                    }
                }
            }
        }
    }
}

bool Arbitrage::has_arbitrage() {
    generate_min_distance();
    double curr_arbitrage;
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix.size(); ++j) {
            curr_arbitrage = matrix[i][j] * matrix_copy[j][i];
            if (curr_arbitrage > 0 && curr_arbitrage < 1) return true;
        }
    }
    return false;
}

vector<double>& Arbitrage::operator[](int row) {
    return matrix[row];
}