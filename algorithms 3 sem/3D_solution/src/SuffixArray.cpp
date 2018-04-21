#include "../tests/SuffixArray.h"

void SuffixArray::build_suffix_array() {
    const int alphabetSize = 256;
    const int stringSize = 1000;
    int number_of_classes = 1;
    vector<int> substring_class(stringSize, 0);
    vector<int> new_substring_class(stringSize, 0);
    vector<int> letter_entry(stringSize, 0);
    vector<int> indexes(stringSize, 0);
    vector<int> new_indexes(stringSize, 0);

    substring_class.assign(stringSize, 0);
    letter_entry.assign(stringSize, 0);

    for (int i = 0; i < main_string.length(); ++i) {
        ++letter_entry[main_string[i]];
    }
    for (int i = 1; i < alphabetSize; ++i) {
        letter_entry[i] += letter_entry[i - 1];
    }
    for (int i = 0; i < main_string.length(); ++i) {
        indexes[--letter_entry[main_string[i]]] = i;
    }

    substring_class[indexes[0]] = 0;
    for (int i = 1; i < main_string.length(); ++i) {
        if (main_string[indexes[i - 1]] != main_string[indexes[i]]) {
            ++number_of_classes;
        }
        substring_class[indexes[i]] = number_of_classes - 1;
    }

    for (int deep = 1; deep < main_string.length(); deep *= 2) {
        for (int i = 0; i < main_string.length(); ++i) {
            new_indexes[i] = indexes[i] - deep;
            if (new_indexes[i] < 0) {
                new_indexes[i] += main_string.length();
            }
        }

        for (int i = 0; i < number_of_classes; ++i) {
            letter_entry[i] = 0;
        }
        for (int i = 0; i < main_string.length(); ++i) {
            ++letter_entry[substring_class[new_indexes[i]]];
        }
        for (int i = 1; i < number_of_classes; ++i) {
            letter_entry[i] += letter_entry[i - 1];
        }
        for (int i = main_string.length() - 1; i >= 0; --i) {
            int curr_index = --letter_entry[substring_class[new_indexes[i]]];
            indexes[curr_index] = new_indexes[i];
        }

        number_of_classes = 1;

        new_substring_class[indexes[0]] = 0;
        for (int i = 1; i < main_string.length(); ++i) {
            int mid1 = (indexes[i] + deep) % main_string.length();
            int mid2 = (indexes[i - 1] + deep) % main_string.length();
            if (substring_class[indexes[i]] != substring_class[indexes[i - 1]]
                || substring_class[mid1] != substring_class[mid2]) {
                ++number_of_classes;
            }
            new_substring_class[indexes[i]] = number_of_classes - 1;
        }

        substring_class = new_substring_class;
    }

    for (int i = 0; i < main_string.length(); ++i) {
        suffix_array.push_back(indexes[i]);
    }
}

void SuffixArray::build_lcp_array() {

    std::vector<int> rank(main_string.length());
    lcp_array.resize(main_string.length());

    for (int i = 0; i < main_string.length(); ++i) {
        rank[suffix_array[i]] = i;
    }

    int curr_value = 0;
    for (int i = 0; i < main_string.length(); ++i) {
        if (curr_value > 0) {
            curr_value--;
        }
        if (rank[i] == main_string.length() - 1) {
            lcp_array[main_string.length() - 1] = -1;
            curr_value = 0;
        } else {
            while (main_string.length() > std::max(i + curr_value, suffix_array[rank[i] + 1] + curr_value) &&
                   main_string[i + curr_value] == main_string[suffix_array[rank[i] + 1] + curr_value]) {
                curr_value++;
            }
            lcp_array[rank[i]] = curr_value;
        }
    }
}

SuffixArray::SuffixArray(): main_string("") {}

SuffixArray::SuffixArray(const string& new_string) {
    main_string = new_string + "$";
    build_suffix_array();
    build_lcp_array();
}

vector<int>& SuffixArray::get_suffix_array() {
    return suffix_array;
}

int SuffixArray::get_number_of_substrings() {
    int number_of_substrings = 0;
    for (int i = 1; i < suffix_array.size(); ++i) {
        number_of_substrings += suffix_array.size() - 1 - suffix_array[i];
    }
    for (int i = 1; i < lcp_array.size() - 1; ++i) {
        number_of_substrings -= lcp_array[i];
    }
    return number_of_substrings;
}

