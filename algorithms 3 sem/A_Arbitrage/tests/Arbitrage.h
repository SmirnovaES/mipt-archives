#include <iostream>
#include <vector>

#ifndef ARBITRAGE_ARBITRAGE_H
#define ARBITRAGE_ARBITRAGE_H


using std::vector;

class Arbitrage {
private:
    vector<vector<double>> matrix;
    vector<vector<double>> matrix_copy;
    void generate_min_distance();
public:

    Arbitrage();

    friend std::istream& operator>>(std::istream& in, Arbitrage& arb);

    bool has_arbitrage();

    vector<double>& operator[](int row);
};


#endif //ARBITRAGE_ARBITRAGE_H
