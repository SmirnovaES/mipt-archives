#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <ostream>
#include <cstdlib>
#include <string>


class BigInt{
public:
    BigInt() {}
    BigInt(int number) {
        if (number >= 10) {
            int digit;
            int power = 10;
            while (number != number % (power / 10)) {
                digit = (number % power - number % (power / 10)) / (power / 10);
                data.insert(data.begin(), digit);
                power *= 10;
            }
        } else {
            data.push_back(number);
        }
    }

    BigInt(const BigInt& x) {
        for (int i = 0; i < x.get_size(); i++) {
            data.push_back(x.get_digit(i));
        }
    }

    void insert_d(int digit) {
        data.insert(data.begin(), digit);
    }

    void insert_to_end(int digit) {
        data.push_back(digit);
    }

    void delete_digit(int digit) {
        data.erase(data.begin() + digit);
    }

    int get_size() const{
        return data.size();
    }

    int get_digit(int digit) const{
        return data[digit];
    }

private:
    std::vector <int> data;
};

std::ofstream& operator<< (std::ofstream& output, const BigInt& a) {
    for(int i = 0; i < a.get_size(); i++) {
        output << a.get_digit(i);
    }
    return output;
}

std::ostream& operator<< (std::ostream& output, const BigInt& a) {
    for(int i = 0; i < a.get_size(); i++) {
        output << a.get_digit(i);
    }
    return output;
}

std::ifstream& operator>> (std::ifstream& input, BigInt& a) {
    std::string s;
    input >> s;
    for (int i = 0; i < s.size(); i++) {
        a.insert_to_end(s[i] - '0');
    }
    return input;
}

BigInt operator- (const BigInt& a, const BigInt& b) { //a must me more than b
    BigInt dif;
    int prev_digit = 0;
    for (int i = 0; i < a.get_size(); i++) {
        if (i < b.get_size()) {
            if (a.get_digit(a.get_size() - i - 1) < b.get_digit(b.get_size() - i - 1) + prev_digit) {
                dif.insert_d(10 + a.get_digit(a.get_size() - i - 1) - b.get_digit(b.get_size() - i - 1) - prev_digit);
                prev_digit = 1;
            } else if (a.get_digit(a.get_size() - i - 1) - b.get_digit(b.get_size() - i - 1) - prev_digit < 0) {
                dif.insert_d(10 + a.get_digit(a.get_size() - i - 1) - b.get_digit(b.get_size() - i - 1) - prev_digit);
                prev_digit = 1;
            } else {
                dif.insert_d(a.get_digit(a.get_size() - i - 1) - b.get_digit(b.get_size() - i - 1) - prev_digit);
                prev_digit = 0;
            }
        }  else if (a.get_digit(a.get_size() - i - 1) - prev_digit < 0) {
            dif.insert_d(10 + a.get_digit(a.get_size() - i - 1) - prev_digit);
            prev_digit = 1;
        } else {
            dif.insert_d(a.get_digit(a.get_size() - i - 1) - prev_digit);
            prev_digit = 0;
        }
    }
    int j = 0;
    while (dif.get_digit(j) == 0  && dif.get_size() != 1) dif.delete_digit(j);
    return dif;
}

BigInt operator+ (const BigInt& a, const BigInt& b) {
    BigInt sum;
    int new_digit;
    int prev_digit = 0;
    for (int i = 0; i < a.get_size() || i < b.get_size(); i++) {
        if (i < b.get_size() && i < a.get_size()) {
            new_digit = a.get_digit(a.get_size() - i - 1) + b.get_digit(b.get_size() - i - 1) + prev_digit;
        } else  if (i < a.get_size()) {
            new_digit = a.get_digit(a.get_size() - i - 1) + prev_digit;
        } else if (i < b.get_size()) {
            new_digit = b.get_digit(b.get_size() - i - 1) + prev_digit;
        }
        sum.insert_d(new_digit % 10);
        prev_digit = new_digit / 10;
    }
    if (prev_digit > 0) sum.insert_d(prev_digit);
    return sum;
}

BigInt operator* (const BigInt& a, const BigInt& b) {
    BigInt op(0);
    int power = 0;
    for (int i = 0; i < b.get_size(); i++) {
        BigInt curr_ans;
        int curr_dig;
        int prev_dig = 0;
        for (int j = 0; j < a.get_size(); j++) {
            curr_dig = b.get_digit(b.get_size() - i - 1) * a.get_digit(a.get_size() - j - 1) + prev_dig;
            curr_ans.insert_d(curr_dig % 10);
            prev_dig = curr_dig / 10;
        }
        if (prev_dig > 0) curr_ans.insert_d(prev_dig);
        for (int k = 0; k < power; k++) {
            curr_ans.insert_to_end(0);
        }
        op = op + curr_ans;
        power++;
    }
    int j = 0;
    while (op.get_digit(j) == 0  && op.get_size() != 1) op.delete_digit(j);
    return op;
}

BigInt operator* (const BigInt& a, int b) {
    BigInt b1(b);
    return a * b1;
}

bool operator< (const BigInt& a, const BigInt& b) {
    if (a.get_size() < b.get_size()) return true;
    if (a.get_size() > b.get_size()) return false;
    for (int i = 0; i < a.get_size(); i++) {
        if (a.get_digit(i) < b.get_digit(i)) return true;
        if (a.get_digit(i) > b.get_digit(i)) return false;
    }
    return false;
}

bool operator== (const BigInt& a, const BigInt& b) {
    if (a < b || b < a) return false;
    return true;
}

bool operator> (const BigInt& a, const BigInt& b) {
    if (a < b || a == b) return false;
    return true;
}

bool operator<= (const BigInt& a, const BigInt& b) {
    if (a > b) return false;
    return true;
}

bool operator>= (const BigInt& a, const BigInt& b) {
    if (a < b) return false;
    return true;
}

BigInt operator/ (const BigInt& a, const BigInt& b) {
    if (a < b) {
        BigInt quot(0);
        return quot;
    }
    BigInt quot;
    BigInt curr_div;
    for (int i = 0; i < b.get_size(); i++) {
        curr_div.insert_to_end(a.get_digit(i));
    }
    for (int i = 0; i < b.get_size(); i++) {
        if (curr_div.get_digit(i) > b.get_digit(i)) {
            break;
        }
        if (curr_div.get_digit(i) < b.get_digit(i)) {
            curr_div.insert_to_end(a.get_digit(b.get_size()));
            break;
        }
    }
    int k = curr_div.get_size() - 1;
    while (k != a.get_size()) {
        int i = 0;
        while (b * i <= curr_div) i++;
        quot.insert_to_end(--i);
        curr_div = curr_div - (b * i);
        if (k != a.get_size() - 1) curr_div.insert_to_end(a.get_digit(++k));
        else break;
        int j = 0;
        while (curr_div.get_digit(j) == 0  && curr_div.get_size() != 1) curr_div.delete_digit(j);
    }
    return quot;
}

BigInt operator% (const BigInt& a, const BigInt& b) {
    if (a < b) {
        return a;
    }
    BigInt quot;
    BigInt curr_div;
    for (int i = 0; i < b.get_size(); i++) {
        curr_div.insert_to_end(a.get_digit(i));
    }
    for (int i = 0; i < b.get_size(); i++) {
        if (curr_div.get_digit(i) > b.get_digit(i)) {
            break;
        }
        if (curr_div.get_digit(i) < b.get_digit(i)) {
            curr_div.insert_to_end(a.get_digit(b.get_size()));
            break;
        }
    }
    int k = curr_div.get_size() - 1;
    while (k != a.get_size()) {
        int i = 0;
        while (b * i <= curr_div) i++;
        quot.insert_to_end(--i);
        curr_div = curr_div - (b * i);
        if (k != a.get_size() - 1) curr_div.insert_to_end(a.get_digit(++k));
        else break;
        int j = 0;
        while (curr_div.get_digit(j) == 0  && curr_div.get_size() != 1) curr_div.delete_digit(j);
    }
    return curr_div;
}

BigInt operator+ (const BigInt& a, int b) {
    BigInt b1(b);
    return a + b1;
}

BigInt operator- (const BigInt& a, int b) {
    BigInt b1(b);
    return a - b1;
}

BigInt operator/ (const BigInt& a, int b) {
    BigInt b1(b);
    return a / b1;
}

BigInt operator% (const BigInt& a, int b) {
    BigInt b1(b);
    return a % b1;
}

int main() {
    std::ifstream input("INPUT.TXT");
    std::ofstream output("OUTPUT.TXT");
    BigInt n, m;
    input >> n;
    input >> m;
    output << n % m;
    input.close();
    output.close();
    return 0;
}
