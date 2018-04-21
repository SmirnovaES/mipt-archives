#include <vector>
#include <string>

#ifndef TRANSFORMATIONS_TRANSFORMATIONS_H
#define TRANSFORMATIONS_TRANSFORMATIONS_H

using std::string;
using std::vector;

class Transformations {
private:
    vector<int> prefix_function;
    vector<int> z_function;
    string main_string;
public:
    Transformations();

    Transformations(const vector<int>& new_prefix_function, const vector<int>& new_z_function, const string& new_string);

    Transformations(const string& new_string);

    Transformations(const vector<int>& new_prefix_function, const vector<int>& new_z_function);

    Transformations(const vector<int>& new_function, bool isPrefix);

    void string_to_prefix_function();

    void prefix_function_to_string(string& recovered_string);

    void string_to_z_function();

    void z_function_to_prefix_function();

    vector<int>& get_prefix_function();

    vector<int>& get_z_function();

};


#endif //TRANSFORMATIONS_TRANSFORMATIONS_H
