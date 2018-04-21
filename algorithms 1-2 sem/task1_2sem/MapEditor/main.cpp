#include <iostream>
#include <vector>
#include <string>

class GameObject {
public:
    GameObject(int new_x, int new_y): x(new_x), y(new_y) {}

    int get_x() const{
        return x;
    }

    int get_y() const{
        return y;
    }

    void set_x(int new_x) {
        x = new_x;
    }

    void set_y(int new_y) {
        y = new_y;
    }

    //void move(int new_x, int new_y);

    virtual char get_symbol() const = 0;

    virtual void print_info() const = 0;

    virtual ~GameObject() {};
private:
    int x, y;
};

class Creature: public GameObject {
public:
    Creature(int new_x, int new_y, int new_hp): GameObject(new_x, new_y), hp(new_hp) {}

    int get_hp() const {
        return hp;
    }

    virtual ~Creature() {};
private:
    int hp;
};

class Terrain: public GameObject {
public:
    Terrain(int new_x, int new_y, int new_size): GameObject(new_x, new_y), size(new_size) {}

    int get_size() const{
        return size;
    }

    virtual ~Terrain() {};
private:
    int size;
};

class Hero: public Creature {
public:
    Hero(const std::string& new_name, int new_x, int new_y, int new_hp) : Creature(new_x, new_y, new_hp), name(new_name) {}

    char get_symbol() const override {
        return name[0];
    }

    void print_info() const override {
        std::cout << "Great hero " << name << " with hp " << this->get_hp() << " at (" << this->get_x() << ", " << this->get_y() << ").\n";
    }

private:
    std::string name;
};

class Monster: public Creature {
public:
    Monster(int new_x, int new_y, int new_hp): Creature(new_x, new_y, new_hp) {}

	char get_symbol() const override{
        return 'm';
	}

	void print_info() const override{
        std::cout << "Some monster with hp " << this->get_hp() << " at (" << this->get_x() << ", " << this->get_y() << ").\n";
	}
};

class Lake: public Terrain {
public:
    Lake(int new_x, int new_y, int new_size, int new_depth): Terrain(new_x, new_y, new_size), depth(new_depth) {}

	int get_depth() const {
        return depth;
	}

	char get_symbol() const override {
        return 'w';
	}

	void print_info() const override {
         std::cout << "Clean lake of depth " << depth << " at (" << this->get_x() << ", " << this->get_y() << ") size " << this->get_size() << ".\n";
	}
private:
    int depth;
};

class Forest: public Terrain {
public:
    Forest(int new_x, int new_y, int new_size): Terrain(new_x, new_y, new_size) {}

	char get_symbol() const override {
        return 'f';
	}

	void print_info() const override {
        std::cout <<  "Forest at (" << this->get_x() << ", " << this->get_y() << ") size " << this->get_size() << ".\n";
	}
};

class Mountain: public Terrain {
public:
    Mountain(int new_x, int new_y, int new_size, int new_height) : Terrain(new_x, new_y, new_size), height(new_height) {}

	int get_height() {
        return height;
    }

	char get_symbol() const override {
        return 'M';
	}

	void print_info() const override {
        std::cout <<  "Big mountain " << height << " feet high at (" << this->get_x() << ", " << this->get_y() << ") size " << this->get_size() << ".\n";
	}

private:
    int height;
};

class World {
public:
    World(): width(0), height(0) {}

    World(int new_width, int new_height) {
        for (int i = 0; i < new_height; ++i) {
            map.push_back("");
            for (int j = 0; j < new_width; ++j)
                map[i] += ".";
        }
        width = new_width;
        height = new_height;
    }

    ~World() {
        delete[] &objects;
    }

    void show() const {
        for (unsigned int i = 0; i < map.size(); i++) {
            for (unsigned int j = 0; j < map[i].size(); j++) {
                std::cout << map[i][j] << ' ';
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    void move(int id, int new_x, int new_y) {
        GameObject* curr_obj = objects[id];
        int curr_x = curr_obj->get_x();
        int curr_y = curr_obj->get_y();
        //char curr_symbol = curr_obj->get_symbol();
        int curr_size;
        if (dynamic_cast<Terrain*>(curr_obj) != NULL) {
            curr_size = dynamic_cast<Terrain*>(curr_obj)->get_size();
        } else {
            curr_size = 1;
        }
        for (int i = curr_y; i < curr_y + curr_size && i < height; i++) {
            for (int j = curr_x; j < curr_x + curr_size && j < width; j++) {
                map[i][j] = '.';
            }
        }
        curr_obj->set_x(new_x);
        curr_obj->set_y(new_y);
        render(id);
    }

    void dump() const {
        for (unsigned int i = 0; i < objects.size(); i++) {
            std::cout << "Object id: " << i << ". ";
            objects[i]->print_info();
        }
    }

    void add_object(GameObject* new_object) {
        objects.push_back(new_object);
        render(objects.size() - 1);
    }

private:
    void render(int id) {
        GameObject* curr_obj = objects[id];
        int curr_x = curr_obj->get_x();
        int curr_y = curr_obj->get_y();
        char curr_symbol = curr_obj->get_symbol();
        int curr_size;
        if (dynamic_cast<Terrain*>(curr_obj) != NULL) {
            curr_size = dynamic_cast<Terrain*>(curr_obj)->get_size();
        } else {
            curr_size = 1;
        }

        for (int i = curr_y; i < curr_y + curr_size && i < height; i++) {
            for (int j = curr_x; j < curr_x + curr_size && j < width; j++) {
                map[i][j] = curr_symbol;
            }
        }
    }
    int width, height;
    std::vector <GameObject*> objects;
    std::vector <std::string> map;
    World(const World&);
    void operator= (const World&);

};

void print_help() {
    std::cout << "map - creates a new map with user's width and height;\n"
				<< "show  - shows current map;\n"
				<< "create - creates a new object;\n"
				<< "dump - shows description of all objects on the map;\n"
				<< "move - moves object;\n"
				<< "help - shows commands description;\n"
				<< "quit - exits the editor.\n";
}

int main() {
    std::string curr_input;
    World* world;
    bool map_created = false;
    while(true) {
        std::cout << "> ";
        std::cin >> curr_input;
        if (curr_input == "map") {
            if (map_created) {
                std::cout << "Map has already been created.\n";
            } else {
                int new_x, new_y;
                std::cin >> new_x >> new_y;
                world = new World(new_x, new_y);
                map_created = true;

            }
        } else if (curr_input == "show") {
            world->show();
        } else if (curr_input == "create") {
            std::string type, str;
            std::cin >> type;
            if (type == "hero") {
                std::string hero_name;
                int new_x, new_y, new_hp;
                std::cin >> hero_name >> str >> new_x >> new_y >> str >> new_hp;
                //Hero new_hero(hero_name, new_x, new_y, new_hp);
                GameObject* new_hero = new Hero(hero_name, new_x, new_y, new_hp);
                world->add_object(new_hero);
            } else if (type == "monster") {
                int new_x, new_y, new_hp;
                std::cin >> str >> new_x >> new_y >> str >> new_hp;
                GameObject* new_monster = new Monster(new_x, new_y, new_hp);
                world->add_object(new_monster);
            } else if (type == "lake") {
                int new_x, new_y, new_depth, new_size;
                std::cin >> str >> new_depth >> str >> new_x >> new_y >> str >> new_size;
                GameObject* new_lake = new Lake(new_x, new_y, new_size, new_depth);
                world->add_object(new_lake);
            } else if (type == "mountain") {
                int new_x, new_y, new_height, new_size;
                std::cin >> str >> new_height >> str >> new_x >> new_y >> str >> new_size;
                GameObject* new_mountain = new Mountain(new_x, new_y, new_size, new_height);
                world->add_object(new_mountain);
            } else if (type  == "forest") {
                int new_x, new_y, new_size;
                std::cin >> str >> new_x >> new_y >> str >> new_size;
                GameObject* new_forest = new Forest(new_x, new_y, new_size);
                world->add_object(new_forest);
            } else {
                std::cout << "Error: there's no such type of object.\n";
            }
        } else if (curr_input == "dump") {
            world->dump();
        } else if (curr_input == "move") {
            int id, new_x, new_y;
            std::cin >> id >> new_x >> new_y;
            world->move(id, new_x, new_y);
        } else if (curr_input == "help") {
            print_help();
        } else if (curr_input == "quit") {
            std::cout << "Bye!\n";
            break;
        } else {
            std::cout << "Error: there's no such command. Enter 'help' for help.\n";
        }
    }
    return 0;
}
