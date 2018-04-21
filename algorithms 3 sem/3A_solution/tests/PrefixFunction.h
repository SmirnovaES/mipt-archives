#include <vector>
#include <string>

#ifndef PREFIXFUNCTION_PREFIXFUNCTION_H
#define PREFIXFUNCTION_PREFIXFUNCTION_H

using std::vector;
using std::string;

class PrefixFunction {
private:
    string data;
    vector<int> prefix_function;
    int pattern_length;
public:
    PrefixFunction(const string& main_string, const string& pattern);

    PrefixFunction(const string& main_string);

    PrefixFunction();

    void get_indexes_of_substring(vector<int>& indexes);

    vector<int>& get_prefix_function();

};


#endif //PREFIXFUNCTION_PREFIXFUNCTION_H
