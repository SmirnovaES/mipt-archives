#include <iostream>
#include <string>
#include <vector>

class Human {
public:
    Human() {
        set_id();
        name = "";
    }

    Human(const std::string& human_name) {
        name = human_name;
        set_id();
    }

    void set_id() {
        static int curr_id = 1;
        id = curr_id++;
    }

    int get_id() const{
        return id;
    }

    std::string get_name() {
        return name;
    }

    virtual std::string get_type() {
        return "human";
    };

    virtual ~Human() {};

private:
    std::string name;
    int id;
};

class Student: public Human {
    public:
    Student(const std::string& st_name): Human(st_name) {

    }

    std::string get_type() {
        return "student";
    }
};

class Worker: public Human {
    public:
    Worker(const std::string& wk_name): Human(wk_name){

    }

    std::string get_type() {
        return "worker";
    }
};

class Building {
public:
    virtual bool is_allowed(const Human* h) const{
        return true;
    };
    virtual ~Building() {};
};

class StudyingCampus: public Building {
public:
    bool is_allowed(const Human* h) const {
        if (dynamic_cast<const Student*>(h) != NULL || dynamic_cast<const Worker*>(h) != NULL) return true;
        return false;
    }
};

class LaboratoryCampus: public Building {
public:
    void set_permission(const Human* st){
        admitted_id.push_back(st->get_id());
    }

    bool is_allowed(const Human* h) {
        if(dynamic_cast<const Student*>(h) != NULL) {
            if(!is_student_allowed(h)) {
                set_permission(h);
                return false;
            } else return true;
        } else if (dynamic_cast<const Worker*>(h) != NULL) {
            return true;
        }
        return false;
    }

    bool is_student_allowed(const Human* st) const{
        for (unsigned int i = 0; i < admitted_id.size(); i++) {
            if (admitted_id[i] == st->get_id()) return true;
        }
        return false;
    }

private:
    std::vector <int> admitted_id;
};

int main() {
    Human* student = new Student("Ivan");
    Human* worker = new Worker("Salnikov");
    Human* human = new Human("Vasya");
    Building* lab = new LaboratoryCampus();
    Building* campus = new StudyingCampus();
    if (lab->is_allowed(worker)) {
        std::cout << worker->get_name() << " is allowed to lab\n";
    } else {
        std::cout << worker->get_name() << " is not allowed to lab\n";
    }
    if (lab->is_allowed(student)) {
        std::cout << student->get_name() << " is allowed to lab\n";
    } else {
        std::cout << student->get_name() << " is not allowed to lab\n";
    }
    if (lab->is_allowed(student)) {
        std::cout << student->get_name() << " is allowed to lab\n";
    } else {
        std::cout << student->get_name() << " is not allowed to lab\n";
    }
    if (lab->is_allowed(human)) {
        std::cout << human->get_name() << " is allowed to lab\n";
    } else {
        std::cout << human->get_name() << " is not allowed to lab\n";
    }
    if (campus->is_allowed(worker)) {
        std::cout << worker->get_name() << " is allowed to campus\n";
    } else {
        std::cout << worker->get_name() << " is not allowed to campus\n";
    }
    if (campus->is_allowed(student)) {
        std::cout << student->get_name() << " is allowed to campus\n";
    } else {
        std::cout << student->get_name() << " is not allowed to campus\n";
    }
    if (campus->is_allowed(human)) {
        std::cout << human->get_name() << " is allowed to campus\n";
    } else {
        std::cout << human->get_name() << " is not allowed to campus\n";
    }
    return 0;
}
