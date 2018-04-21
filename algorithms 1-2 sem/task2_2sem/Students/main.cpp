#include <iostream>
#include <map>
#include <set>
#include <cstring>
#include <vector>

using namespace std;

class Student {
public:
    void set_mark(string exam, int mark) {
        marks[exam] = mark;
    }

    void set_name(string student_name) {
        name = student_name;
    }

    int get_mark(string exam) const{
        return marks.find(exam)->second;
    }

    string get_name() const{
        return name;
    }

    int get_number_of_exams() {
        return marks.size();
    }

    bool can_be_deducted(int k) const{
        int completed_exams = 0;
        for (auto it : marks) {
            if (it.second > 2) {
                completed_exams++;
            }
        }
        if (completed_exams > k) {
            return false;
        } else {
            return true;
        }
    }

    bool operator<(const Student& student) const {
        return name < student.name;
    }
private:
    map <string, int> marks;
    string name;
};

class Group{
public:
    void deduct(int border) {
        typename set<Student>::iterator it = students.begin();
        while (it != students.end()) {
            if(it->can_be_deducted(border)) {
                cout << "Student " << it->get_name() << " is DEDUCTED." << endl;
                auto next = it++;
                students.erase(next);
            } else {
                cout << "Student " << it->get_name() << " is not deducted." << endl;
                it++;
            }
        }
    }
    void add_student(const Student& student) {
        students.insert(student);
    }
private:
    set <Student> students;
};

int main() {
    Group group;
    Student student1, student2, student3;

    student1.set_name("Ivan");
    student1.set_mark("matan", 2);
    student1.set_mark("algem", 1);
    student1.set_mark("oktch", 6);
    student1.set_mark("history", 10);

    student2.set_name("Mihail");
    student2.set_mark("matan", 2);
    student2.set_mark("algem", 4);
    student2.set_mark("oktch", 7);
    student2.set_mark("history", 5);

    student3.set_name("Markov");
    student3.set_mark("matan", 2);
    student3.set_mark("algem", 2);
    student3.set_mark("oktch", 2);
    student3.set_mark("history", 2);

    group.add_student(student1);
    group.add_student(student2);
    group.add_student(student3);

    group.deduct(2);

    return 0;
}
