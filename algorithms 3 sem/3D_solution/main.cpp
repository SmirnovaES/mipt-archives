/*#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;

void build_suffix_array(vector<int>& suffix_array, const string& curr_string) {
    const int alphabetSize = 256;
    const int stringSize = 1000;
    int number_of_classes = 1;
    vector<int> substring_class(stringSize, 0);
    vector<int> new_substring_class(stringSize, 0);
    vector<int> letter_entry(stringSize, 0);
    vector<int> indexes (stringSize, 0);
    vector<int> new_indexes(stringSize, 0);

    substring_class.assign(stringSize, 0);
    letter_entry.assign(stringSize, 0);

    for (int i = 0; i < curr_string.length(); ++i){
        ++letter_entry[curr_string[i]];
    }
    for (int i = 1; i < alphabetSize; ++i){
        letter_entry[i] += letter_entry[i - 1];
    }
    for (int i = 0; i < curr_string.length(); ++i){
        indexes[--letter_entry[curr_string[i]]] = i;
    }

    substring_class[indexes[0]] = 0;
    for (int i = 1; i < curr_string.length(); ++i) {
        if (curr_string[indexes[i - 1]] != curr_string[indexes[i]]) {
            ++number_of_classes;
        }
        substring_class[indexes[i]] = number_of_classes - 1;
    }

    for (int deep = 1; deep < curr_string.length(); deep *= 2) {
        for (int i = 0; i < curr_string.length(); ++i) {
            new_indexes[i] = indexes[i] - deep;
            if (new_indexes[i] < 0) {
                new_indexes[i] += curr_string.length();
            }
        }

        for (int i = 0; i < number_of_classes; ++i) {
            letter_entry[i] = 0;
        }
        for (int i = 0; i < curr_string.length(); ++i) {
            ++letter_entry[substring_class[new_indexes[i]]];
        }
        for (int i = 1; i < number_of_classes; ++i) {
            letter_entry[i] += letter_entry[i - 1];
        }
        for (int i = curr_string.length() - 1; i >=0; --i) {
            int curr_index = --letter_entry[substring_class[new_indexes[i]]];
            indexes[curr_index] = new_indexes[i];
        }

        number_of_classes = 1;

        new_substring_class[indexes[0]] = 0;
        for (int i = 1; i < curr_string.length(); ++i) {
            int mid1 = (indexes[i] + deep) % curr_string.length();
            int mid2 = (indexes[i - 1] + deep) % curr_string.length();
            if (substring_class[indexes[i]] != substring_class[indexes[i - 1]]
                || substring_class[mid1] != substring_class[mid2]){
                ++number_of_classes;
            }
            new_substring_class[indexes[i]] = number_of_classes - 1;
        }

        substring_class = new_substring_class;
    }

    for (int i = 0; i < curr_string.length(); ++i) {
        suffix_array.push_back(indexes[i]);
    }
}

void build_lcp_array(const string& curr_string, const vector<int>& suffix_array, vector<int>& lcp_array) {
    std::vector<int> rank(curr_string.length());
    lcp_array.resize(curr_string.length());

    for (int i = 0; i < curr_string.length(); ++i) {
        rank[suffix_array[i]] = i;
    }

    int curr_value = 0;
    for (int i = 0; i < curr_string.length(); ++i) {
        if (curr_value > 0) {
            curr_value--;
        }
        if (rank[i] == curr_string.length() - 1) {
            lcp_array[curr_string.length() - 1] = -1;
            curr_value = 0;
        } else {
            while (curr_string.length() > std::max(i + curr_value, suffix_array[rank[i] + 1] + curr_value) &&
                   curr_string[i + curr_value] == curr_string[suffix_array[rank[i] + 1] + curr_value]) {
                curr_value++;
            }
            lcp_array[rank[i]] = curr_value;
        }
    }
}

int get_number_of_substrings(const vector<int>& suffix_array, const vector<int>& lcp_array) {
    int number_of_substrings = 0;
    for (int i = 1; i < suffix_array.size(); ++i) {
        number_of_substrings += suffix_array.size() - 1 - suffix_array[i];
    }
    for (int i = 1; i < lcp_array.size() - 1; ++i){
        number_of_substrings -= lcp_array[i];
    }
    return number_of_substrings;
}

int main() {
    string input;
    vector<int> suffix_array;
    vector<int> lcp_array;

    std::cin >> input;
    input += '$';

    build_suffix_array(suffix_array, input);
    build_lcp_array(input, suffix_array, lcp_array);

    std::cout << get_number_of_substrings(suffix_array, lcp_array);
    return 0;
}*/

#include <iostream>
#include <vector>
#include <fstream>
#include "tests/SuffixArray.h"


#include <gtest/gtest.h>
#include <gmock/gmock.h>



int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}