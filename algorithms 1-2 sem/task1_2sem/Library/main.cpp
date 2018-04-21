#include <iostream>
#include <string>
#include <vector>
#include <set>


using namespace std;

class LibraryObject{
public:
     void add_autor(const string& autor) {
        autors.push_back(autor);
    }

    void set_name(const string& new_name) {
        name = new_name;
    }

    void set_pub_house(const string& new_pub_house) {
        pub_house = new_pub_house;
    }

    void set_issue_year(int new_issue_year) {
        issue_year = new_issue_year;
    }

    void set_pages(int new_pages) {
        pages = new_pages;
    }

    void set_content(const string& new_content) {
        content = new_content;
    }

    void set_status(const string& new_status) {
        status = new_status;
    }

    void set_id() {
        static int curr_id = 1;
        id = curr_id++;
    }

    void set_type(const string& new_type) {
        type = new_type;
    }

    vector <string> get_autors() const{
        return autors;
    }

    string get_name() const{
        return name;
    }

    string get_pub_house() const{
        return pub_house;
    }

    int get_issue_year() const{
        return issue_year;
    }

    int get_pages() const{
        return pages;
    }

    string get_content() const{
         return content;
    }

    string get_status() const{
        return status;
    }

    int get_id() const{
        return id;
    }

    string get_type() const{
        return type;
    }

    bool operator<(const LibraryObject& obj) const {
        return name < obj.name;
    }

    virtual ~LibraryObject() {};


private:
    vector <string> autors;
    string name;
    string pub_house;
    int issue_year;
    int pages;
    string content;
    string status;
    int id;
    string type;
};


class Book: public LibraryObject{
public:
    Book(const string& book_name, const string& book_first_autor, const string& book_pub_house, int book_issue_year) {
        set_name(book_name);
        add_autor(book_first_autor);
        set_pub_house(book_pub_house);
        set_issue_year(book_issue_year);
        set_id();
        set_type("Book");
        set_status("In stock");
    }
private:

};

class Magazine: public LibraryObject {
public:
    Magazine(const string& mag_name, const string& mag_first_autor, const string& mag_pub_house, int mag_issue_year, int mag_period) {
        set_name(mag_name);
        add_autor(mag_first_autor);
        set_pub_house(mag_pub_house);
        set_issue_year(mag_issue_year);
        set_period(mag_period);
    }

    void set_period(int new_period) {
        period = new_period;
    }

    int get_period() {
        return period;
    }

private:
    int period;
};


class CollectedWorks{
public:

    CollectedWorks(const string& cw_name, const string& cw_autor, const LibraryObject& cw_first_book) {
        name = cw_name;
        autor = cw_autor;
        books.push_back(cw_first_book);
    }

    void add_book(const LibraryObject& new_book) {
        books.push_back(new_book);
    }

    void delete_book(const string& book_name) {
        for (int i = 0; i < books.size(); i++) {
            if (books[i].get_name() == book_name) {
                books.erase(books.begin() + i);
                break;
            }
        }
    }

    void set_autor(const string& new_autor) {
        autor = new_autor;
    }

    void set_name(const string& new_name) {
        name = new_name;
    }

    string get_autor() {
        return autor;
    }

    string get_name() {
        return name;
    }

    int get_size() {
        return books.size();
    }

private:
    vector <LibraryObject> books;
    string autor;
    string name;
};

void print_info(const LibraryObject& obj) {
    cout << "Object is founded." << endl;
    cout << "Type: " << obj.get_type() << endl;
    cout << "Name: " << obj.get_name() << endl;
    cout << "ID: " << obj.get_id() << endl;
    cout << "Autors: ";
    vector <string> autors = obj.get_autors();
    for (int i = 0; i < autors.size(); i++) {
        cout << autors[i];
        if (i != autors.size() - 1){
                cout << ", ";
            } else {
                cout << endl;
            }
    }
    cout << "Issue year: " << obj.get_issue_year() << endl;
    cout << "Public house: " << obj.get_pub_house() << endl;
    cout << "Status: " << obj.get_status() << endl;
}

class Library {
public:
    void add_data(const LibraryObject& obj) {
        data.push_back(obj);
    }

    void get_info_by_name(const string& obj_name) {
        bool flag = false;
        for (auto it : data) {
            if (it.get_name() == obj_name) {
                print_info(it);
               // print_info(it.get_name(), it.get_id(), it.get_autors(), it.get_issue_year(), it.get_pub_house(), it.get_status(), it.get_type());
                flag = true;
            }
        }
        if (!flag) {
            cout << "Object is not founded.";
        }
    }

    void get_info_by_autor(const string& obj_autor) {
        bool flag = false;
        for (auto it : data) {
            vector <string> autors = it.get_autors();
            for (int i = 0; i < autors.size(); i++) {
                if (autors[i] == obj_autor) {
                    print_info(it);
                    flag = true;
                    break;
                }
            }
        }
        if (!flag) {
            cout << "Object is not founded.";
        }
    }

    void get_info_by_issue_year(int obj_issue_year) {
        bool flag = false;
        for (auto it : data) {
            if (it.get_issue_year() == obj_issue_year) {
                print_info(it);
                flag = true;
            }
        }
        if (!flag) {
            cout << "Object is not founded.";
        }
    }

    void get_info_by_pub_house(const string& obj_pub_house) {
        bool flag = false;
        for (auto it : data) {
            if (it.get_pub_house() == obj_pub_house) {
                print_info(it);
                flag = true;
            }
        }
        if (!flag) {
            cout << "Object is not founded.";
        }
    }

    void get_info_by_id(int obj_id) {
        bool flag = false;
        for (auto it : data) {
            if (it.get_id() == obj_id) {
                print_info(it);
                flag = true;
            }
        }
        if (!flag) {
            cout << "Object is not founded.";
        }
    }

    void give_book(int id) {
        for (int i = 0; i < data.size(); i++) {
            if (data[i].get_id() == id && data[i].get_status() != "Issued") {
                cout << "The book named " << data[i].get_name() << " is issued." << endl;
                data[i].set_status("Issued");
                break;
            }
        }
    }

    void return_book(int id) {
        for (int i = 0; i < data.size(); i++) {
            if (data[i].get_id() == id) {
                cout << "The book is returned." << endl;
                data[i].set_status("In stock");
            }
        }
    }

    void delete_book(int id) {
        for (int i = 0; i < data.size(); i++) {
            if (data[i].get_id() == id) {
                data.erase(data.begin() + i);
            }
        }
    }
private:
    vector <LibraryObject> data;
};

int main() {
    Library* library = new Library();
    LibraryObject* book = new Book("Cool book", "Me", "Fizteh", 2016);
    LibraryObject* book2 = new Book("Cool book 2", "Me", "Fizteh", 2017);
    LibraryObject* magaz = new Magazine("Cool magazine", "Me", "Fizteh", 2015, 5);
    library->add_data(*book);
    library->add_data(*book2);
    library->give_book(1);
    library->give_book(2);
    library->get_info_by_name("Cool book 2");
    library->return_book(2);
    library->get_info_by_autor("Me");
    CollectedWorks* cw = new CollectedWorks("By me", "Me", *book);
    cw->add_book(*book2);
    return 0;
}
