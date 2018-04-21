#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void handle_define(string s, vector <string> &str1, vector <string> &str2) {
    int first = s.find(' ');
    int last = s.find(' ', first + 1);
    str1.push_back(s.substr(first + 1, last - first - 1));
    str2.push_back(s.substr(last + 1, s.size() - 1 - last));
}

void push_string(string s, ofstream &output, vector <string> str1, vector <string> str2) {
    for (unsigned int i = 0; i < str1.size(); i++) {
        int curr_pos = 0;
        while (s.find(str1[i], curr_pos) != string::npos && s.find("#define") == string::npos) {
            int position = s.find(str1[i], curr_pos);
            s.replace(position, str1[i].size(), str2[i]);
            curr_pos = position + str1[i].size();
        }
    }
    cout << s << endl;
    output << s << endl;
}

void clear_two_slash(string s, ofstream &output) {
    int start = s.find("//");
    s.replace(start, s.size(), "");
    output << s;
    cout << s;
    if (s != "") {
        output << endl;
        cout << endl;
    }
}

void clear_slash_star(ifstream &input, ofstream &output, string curr) {
    while(curr.find("*/") == string::npos) {
        if (curr.find("/*") != string::npos) {
            int start = curr.find("/*");
            curr.replace(start, curr.size(), "");
            output << curr;
            cout << curr;
            if (curr != "") {
                output << endl;
                cout << endl;
            }
        }
        getline(input, curr);
    }
    int finish = curr.find("*/");
    curr.replace(0, finish + 2, "");
    output << curr;
    cout << curr;
    if (curr != "") {
        output << endl;
        cout << endl;
    }
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    string curr;
    vector <string> str1;
    vector <string> str2;
    while(getline(input, curr)) {
        if(curr.find("#define") != string::npos) {
            handle_define(curr, str1, str2);
        } else if(curr.find("//") != string::npos) {
            clear_two_slash(curr, output);
        } else if(curr.find("/*") != string::npos) {
            clear_slash_star(input, output, curr);
        } else {
            push_string(curr, output, str1, str2);
        }
    }
    input.close();
    output.close();
    return 0;
}
