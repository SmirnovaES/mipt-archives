#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>

class String{
public:
    String() {
        data = NULL;
        length = 0;
        capacity = 0;
    }

    String(const char* new_data) {
        data = new char[strlen(new_data) * 2];
        length = strlen(new_data);
        capacity = length * 2;
        strcpy(data, new_data);
    }

    String(const String& str) {
        data = new char[str.capacity];
        capacity = str.capacity;
        length = str.length;
        strcpy(data, str.data);
    }

    String(const std::string& str) {
        data = new char[str.length()];
        length = str.length();
        capacity = length;
        strcpy(data, str.c_str());
    }

    int get_length() const{
        return length;
    }

    int get_capacity() const{
        return capacity;
    }

    char get_char(int i) const{
        return data[i];
    }

    const char* c_str() const{
        return data;
    }

    void set_length(int new_length) {
        length = new_length;
    }

    void set_capacity(int new_capacity) {
        capacity = new_capacity;
    }

    void set_data(int len, const char* str) {
        data = new char[len];
        strcpy(data, str);
    }

    String operator= (const String& str) {
        if (str.capacity > capacity){
            char* test = (char*) realloc(data, str.capacity * sizeof(char));
            if (test == NULL) {
                std::cout << "Error: can't allocate memory.\n";
                return 0;
            } else {
                data = test;
            }
            capacity = str.capacity;
        }
        strcpy(data, str.c_str());
        length = str.length;
        return *this;
    }

    bool operator== (const String& str) {
        if (!strcmp(data, str.c_str())) return true;
        return false;
    }

    bool operator< (const String& str) {
        if (strcmp(data, str.c_str()) < 0) return true;
        return false;
    }

    bool operator> (const String& str) {
        if (strcmp(data, str.c_str()) > 0) return true;
        return false;
    }

    bool operator<= (const String& str) {
        if (*this > str) return true;
        return false;
    }

    bool operator>= (const String& str) {
        if (*this < str) return true;
        return false;
    }

    String operator+ (const String& str) {
        String sum;
        sum.capacity = this->get_capacity() + str.capacity;
        sum.length = this->get_length() + str.length;
        sum.data = new char[sum.capacity];
        strcpy(sum.data, this->data);
        strcpy(sum.data + this->length, str.data);
        return sum;
    }

    void insert_ch(int index, char ch) {
        if (capacity < length + 1) {
            if (data == NULL) {
                data = (char*) malloc((length + 1) * sizeof(char));
                capacity = length + 1;
            } else {
            char* test = (char*) realloc(data, (capacity + 1) * 2 * sizeof(char));
            if (test == NULL) {
                std::cout << "Error: can't allocate memory.\n";
                return;
            } else {
                data = test;
            }
            capacity = (capacity + 1) * 2;
            }
        }
        length++;
        memmove(data + (index + 1) * sizeof(char), data + index * sizeof(char), (length - index) * sizeof(char));
        data[index] = ch;
    }

    void delete_last_ch() {
        if(length == 0) {
            std::cout << "Error: string is empty.\n";
            return;
        }
        data [length-- - 1] = 0;
        if(length * 2 < capacity) {
            capacity = capacity / 2;
            char* test = (char*) realloc(data, capacity  * sizeof(char));
            if (test == NULL) {
                std::cout << "Error: can't allocate memory.\n";
                return;
            } else {
                data = test;
            }
        }
    }

    void delete_str(int first_ch, int len) {
        if (first_ch < 0 || len < 0) {
            std::cout << "Error: wrong data.\n";
            return;
        }
        if(first_ch + len > length) {
            std::cout << "Warning: 'len' is more than string length.\n";
            len = length - first_ch;
        }
        memmove(data + first_ch * sizeof(char), data + (first_ch + len) * sizeof(char), (length - first_ch - len) * sizeof(char));
        free(data + first_ch + len);
        for (int i = 0; i < len; i++) {
            delete_last_ch();
        }
        length -= len;
        if(length * 2 < capacity) {
            capacity = capacity / 2;
            char* test = (char*) realloc(data, capacity  * sizeof(char));
            if (test == NULL) {
                std::cout << "Error: can't allocate memory.\n";
                return;
            } else {
                data = test;
            }
        }
    }

    void append(char ch) {
        if (capacity < length + 1) {
            if (data == NULL) {
                data = (char*) malloc((length + 1) * sizeof(char));
                capacity = length + 1;
            } else {
                char* test = (char*) realloc(data, capacity * 2 * sizeof(char));
                if (test == NULL) {
                    std::cout << "Error: can't allocate memory.\n";
                    return;
                } else {
                    data = test;
                }
                capacity = capacity * 2;
            }
        }
        data[length++] = ch;
    }

    ~String() {
        delete[] data;
    }

private:
    char* data;
    int length;
    int capacity;
};

std::ofstream& operator<< (std::ofstream& output, const String& str) {
    if (str.c_str() == NULL) {
        output << "Error: string is not defined.\n";
        return output;
    }
    for (int i = 0; i < str.get_length(); i++) {
        output << str.get_char(i);
    }
    //output << str.c_str();
    return output;
}

std::ostream& operator<< (std::ostream& output, const String& str) {
    if (str.c_str() == NULL) {
        output << "Error: string is not defined.\n";
        return output;
    }
    for (int i = 0; i < str.get_length(); i++) {
        output << str.get_char(i);
    }
    //output << str.c_str();
    return output;
}

std::ifstream& operator>> (std::ifstream& input, String& str) {
    char curr;
    input.get(curr);
    while (curr != ' ' && curr != '\n') {
        str.append(curr);
        input.get(curr);
    }
    return input;
}

std::istream& operator>> (std::istream& input, String& str) {
    char curr;
    input.get(curr);
    while (curr != ' ' && curr != '\n') {
        str.append(curr);
        input.get(curr);
    }
    return input;
}

int main() {
    //checking String(std::string)
    std::string a = "C++ string";
    String b(a);
    std::cout << b << std::endl;
    //checking input-output
    String* c = new String();
    std::cin >> *c;
    std::cout << *c << std::endl;
    String str("This is my string.");
    std::cout << str << std::endl;
    //append() is working because of operator>>
    //checking delete_last_ch()
    str.delete_last_ch();
    std::cout << str << std::endl;
    //checking delete_str(int, int)
    str.delete_str(0, 3);
    std::cout << str << std::endl;
    //checking insert_ch(int, char)
    str.insert_ch(4, 't');
    std::cout << str << std::endl;
    return 0;
}
