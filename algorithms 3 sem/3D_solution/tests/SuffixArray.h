#include <vector>
#include <string>

#ifndef SUFFARRAY_SUFFIXARRAY_H
#define SUFFARRAY_SUFFIXARRAY_H

using std::vector;
using std::string;

class SuffixArray {
private:
    vector<int> suffix_array;
    vector<int> lcp_array;
    string main_string;

    void build_suffix_array();

    void build_lcp_array();
public:
    SuffixArray();

    SuffixArray(const string& new_string);

    vector<int>& get_suffix_array();

    int get_number_of_substrings();

};
#endif //SUFFARRAY_SUFFIXARRAY_H
