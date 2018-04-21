#include "../tests/PrefixFunction.h"

PrefixFunction::PrefixFunction(const string& main_string, const string& pattern) {
    data = pattern + "$" + main_string;
    pattern_length = pattern.length();
    prefix_function.resize(data.length());
    for (int i = 1; i < data.length(); ++i) {
        int curr_length = prefix_function[i - 1];
        while (curr_length > 0 && data[i] != data[curr_length]) {
            curr_length = prefix_function[curr_length - 1];
        }
        if (data[i] == data[curr_length]) {
            ++curr_length;
        }
        prefix_function[i] = curr_length;
    }
}

PrefixFunction::PrefixFunction(const string& main_string) {
    data = main_string;
    prefix_function.resize(data.length());
    for (int i = 1; i < data.length(); ++i) {
        int curr_length = prefix_function[i - 1];
        while (curr_length > 0 && data[i] != data[curr_length]) {
            curr_length = prefix_function[curr_length - 1];
        }
        if (data[i] == data[curr_length]) {
            ++curr_length;
        }
        prefix_function[i] = curr_length;
    }
}

PrefixFunction::PrefixFunction(): data("") {}

void PrefixFunction::get_indexes_of_substring(vector<int>& indexes) {
    for (int i = pattern_length + 1; i < data.length(); ++i) {
        if (prefix_function[i] == pattern_length) {
            indexes.push_back(i - 2 * pattern_length);
        }
    }
}

vector<int>& PrefixFunction::get_prefix_function() {
    return prefix_function;
}
