#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human{
public:
    Human(const string& first_name, const string& second_name) {
        name = first_name;
        surname = second_name;
    }
    virtual void print_name();
    string get_name();
    string get_surname();
    virtual ~Human() {};
private:
    string name;
    string surname;
};

class Mister: public Human {
public:
    Mister(const string& first_name, const string& second_name): Human(first_name, second_name) {};
    void print_name();
};


class Miss: public Human {
public:
    Miss(const string& first_name, const string& second_name): Human(first_name, second_name) {};
    void print_name();
};

class Child: public Human {
public:
    Child(const string& first_name, const string& second_name): Human(first_name, second_name) {};
    void print_name();
};

void Human::print_name() {
    cout << name << " " << surname << endl;
}

string Human::get_name() {
    return name;
}

string Human::get_surname() {
    return surname;
}

void Miss::print_name() {
    cout << "Miss" << " " << get_surname() << endl;
}

void Mister::print_name() {
    cout << "Mister" << " " << get_surname() << endl;
}

void Child::print_name() {
    cout << get_name() << endl;
}



int main() {
    Human* man = new Mister("Johny", "Will");
    Human* woman = new Miss("Sandra", "Will");
    Human* kid = new Child("Mark", "Will");
    man->print_name();
    woman->print_name();
    kid->print_name();
    delete man;
    delete woman;
    delete kid;
    return 0;
}
