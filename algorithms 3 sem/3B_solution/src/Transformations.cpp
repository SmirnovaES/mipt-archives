#include "../tests/Transformations.h"
Transformations::Transformations(): main_string("") {}

Transformations::Transformations(const vector<int>& new_prefix_function, const vector<int>& new_z_function, const string& new_string):
        prefix_function(new_prefix_function), z_function(new_z_function), main_string(new_string) {}

Transformations::Transformations(const string& new_string) {
    main_string = new_string;
    string_to_prefix_function();
    string_to_z_function();
}

Transformations::Transformations(const vector<int>& new_prefix_function, const vector<int>& new_z_function):
        prefix_function(new_prefix_function), z_function(new_z_function) {}

void Transformations::string_to_prefix_function() {
    prefix_function.resize(main_string.size());
    for (int i = 1; i < main_string.length(); ++i) {
        int curr_length = prefix_function[i - 1];
        while (curr_length > 0 && main_string[i] != main_string[curr_length]) {
            curr_length = prefix_function[curr_length - 1];
        }
        if (main_string[i] == main_string[curr_length]) {
            curr_length++;
        }
        prefix_function[i] = curr_length;
    }
}

void Transformations::prefix_function_to_string(string& recovered_string) {
    recovered_string = "";
    char curr_char = 'a';
    for (int i = 0; i < prefix_function.size(); ++i) {
        if (prefix_function[i] == 0) {
            if (i == 0) {
                recovered_string += curr_char;
            } else {
                for (char min_char = 'b'; min_char != curr_char + 1; ++min_char) {
                    int curr_index = i - 1;
                    while (prefix_function[curr_index] > 0 &&
                           recovered_string[prefix_function[curr_index]] != min_char) {
                        curr_index = prefix_function[curr_index] - 1;
                    }
                    if (min_char != recovered_string[prefix_function[curr_index]]) {
                        recovered_string += min_char;
                        break;
                    }
                }
                if (recovered_string.length() != i + 1)
                    recovered_string += ++curr_char;
            }
        } else {
            recovered_string += recovered_string[prefix_function[i] - 1];
        }
    }
}

void Transformations::string_to_z_function() {
    int left_border = 0;
    int right_border = 0;
    z_function.resize(main_string.length());
    for (int i = 0; i < main_string.length(); ++i) {
        z_function[i] = std::min(z_function[i - left_border], right_border - i);
        while (i + z_function[i] < main_string.length() &&
               main_string[z_function[i]] == main_string[i + z_function[i]]) {
            z_function[i]++;
            if (right_border <= z_function[i] + i) {
                left_border = i;
                right_border = z_function[i] + i;
            }
        }
    }
    z_function[0] = 0;
}

void Transformations::z_function_to_prefix_function() {
    prefix_function.resize(z_function.size());
    prefix_function.assign(z_function.size(), 0);
    for (int i = 1; i < z_function.size(); ++i) {
        for (int j = z_function[i] - 1; j >= 0; --j) {
            if (prefix_function[i + j] == 0) {
                prefix_function[i + j] = j + 1;
            } else {
                break;
            }
        }
    }
}

vector<int>& Transformations::get_prefix_function() {
    return prefix_function;
}

vector<int>& Transformations::get_z_function() {
    return z_function;
}

Transformations::Transformations(const vector<int> &new_function, bool isPrefix) {
    if (isPrefix) {
        prefix_function = new_function;
    } else {
        z_function = new_function;
    }
}
