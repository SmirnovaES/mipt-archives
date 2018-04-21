#include <string>
#include <iostream>
#include <vector>
#include <stack>

using std::vector;
using std::string;
using std::stack;

void fill_new_reg(vector<bool>& new_reg, const vector<int>& indices, int length, int start_length, int k) {
    if (new_reg[length % k]) return;
    new_reg[length % k] = true;
    for (int i = 0; i < indices.size(); i++) {
        fill_new_reg(new_reg, indices, (length + indices[i]) % k, start_length, k);
    }
}

vector<bool> parse_input(const string& input, int k) throw(int) {
    stack<vector<bool>> reg_expr;
    for (int c = 0; c < input.size(); c++) {
        char curr_symbol = input[c];
        if (curr_symbol == 'a' || curr_symbol == 'b' || curr_symbol == 'c') {
            vector<bool> tmp(k, false);
            tmp[1] = true;
            reg_expr.push(tmp);
        } else if (curr_symbol == '1') {
            vector<bool> tmp(k, false);
            tmp[0] = true;
            reg_expr.push(tmp);
        } else if (curr_symbol == '+') {
            if (reg_expr.size() < 2) {
                throw 1;
            } else {
                vector<bool> curr_reg1 = reg_expr.top();
                reg_expr.pop();
                vector<bool> curr_reg2 = reg_expr.top();
                reg_expr.pop();
                vector<bool> new_reg(k, false);
                for (int i = 0; i < k; i++) {
                    if (curr_reg1[i] || curr_reg2[i]) {
                        new_reg[i] = true;
                    }
                }
                reg_expr.push(new_reg);
            }
        } else if (curr_symbol == '.') {
            if (reg_expr.size() < 2) {
                throw 1;
            } else {
                vector<bool> curr_reg1 = reg_expr.top();
                reg_expr.pop();
                vector<bool> curr_reg2 = reg_expr.top();
                reg_expr.pop();
                vector<bool> new_reg(k, false);
                for (int i = 0; i < k; i++) {
                    if (curr_reg1[i]) {
                        for (int j = 0; j < k; j++) {
                            if (curr_reg2[j]) {
                                new_reg[(i + j) % k] = true;
                            }
                        }
                    }
                }
                reg_expr.push(new_reg);
            }

        } else if (curr_symbol == '*') {
            if (reg_expr.size() < 1) {
                throw 1;
            }
            vector<bool> curr_reg = reg_expr.top();
            reg_expr.pop();
            vector<bool> new_reg(k, false);

            vector<int> indices;
            for (int i = 0; i < curr_reg.size(); i++) {
                if (curr_reg[i]) {
                    indices.push_back(i);
                }
            }

            new_reg[0] = true;
            for (int i = 0; i < indices.size(); i++) {
                fill_new_reg(new_reg, indices, indices[i], indices[i], k);
            }

            reg_expr.push(new_reg);
        } else {
            throw 1;
        }
    }
    if (reg_expr.size() != 1) {
        throw 1;
    } else {
        return reg_expr.top();
    }
}

int main () {
    int k, l;
    string input;

    std::cin >> input >> k >> l;

    try {
        vector<bool> answer = parse_input(input, k);
        if (answer[l]) {
            std::cout << "YES";
        } else {
            std::cout << "NO";
        }
    } catch(int i) {
        std::cerr << "ERROR: WRONG EXPRESSION";
    }

}