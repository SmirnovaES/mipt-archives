#include <iostream>
#include <memory>
#include <vector>

class Node {
public:
    Node(int new_value = 0): value(new_value), parent(NULL), left(NULL), right(NULL) {}

    void set_value(int new_value) {
        value = new_value;
    }

    void set_left(std::shared_ptr<Node> new_node) {
        left = new_node;
    }

    void set_right(std::shared_ptr<Node> new_node) {
        right = new_node;
    }

    void set_parent(std::shared_ptr<Node> new_node) {
        parent = new_node;
    }

    int get_value() const {
        return value;
    }

    std::shared_ptr<Node> get_right() const {
        return right;
    }

    std::shared_ptr<Node> get_left() const {
        return left;
    }

    std::shared_ptr<Node> get_parent() const {
        return parent;
    }

private:
    int value;
    std::shared_ptr<Node> parent;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
};

class BST{
public:
    BST(const std::vector<int>& values) {
        head = std::make_shared<Node>(values[0]);
        for (int i = 1; i < values.size(); i++) {
            this->add_value(values[i]);
        }
    }

    void add_value(int new_value) {
        std::shared_ptr<Node> new_node = std::make_shared<Node>(new_value);
        std::shared_ptr<Node> curr_node = head;
        while (curr_node != NULL) {
            if (curr_node->get_value() > new_value) {
                if (curr_node->get_left() == NULL) {
                    curr_node->set_left(new_node);
                    new_node->set_parent(curr_node);
                    return;
                } else {
                    curr_node = curr_node->get_left();
                }
            }
            if (curr_node->get_value() < new_value) {
                if (curr_node->get_right() == NULL) {
                    curr_node->set_right(new_node);
                    new_node->set_parent(curr_node);
                    return;
                } else {
                    curr_node = curr_node->get_right();
                }
            }
        }
        std::cout << "Error: can't add element\n";
    }

    std::shared_ptr<Node> get_min(std::shared_ptr<Node> curr_node) {
        if (curr_node->get_left() == NULL) return curr_node;
        return get_min(curr_node->get_left());
    }

    std::shared_ptr<Node> search_value(std::shared_ptr<Node> curr_node, int value) {
        if (curr_node == NULL) return curr_node;
        if (curr_node->get_value() == value) {
            return curr_node;
        } else if (curr_node->get_value() > value) {
            return search_value(curr_node->get_left(), value);
        } else return search_value(curr_node->get_right(), value);
    }

    std::shared_ptr<Node> search_value(int value) {
        return search_value(head, value);
    }

    std::shared_ptr<Node> find_next_to(int value) {
        std::shared_ptr<Node> curr_ans = NULL;
        std::shared_ptr<Node> curr_node = head;
        while (curr_node != NULL) {
            if (curr_node->get_value() < value) {
                if (curr_node->get_right() != NULL) {
                    curr_node = curr_node->get_right();
                } else {
                    return curr_ans;
                }
            } else if (curr_node->get_value() >= value) {
                curr_ans = curr_node;
                if (curr_node->get_left() != NULL) {
                    curr_node = curr_node->get_left();
                } else return curr_ans;
            }
        }
    }
private:
    std::shared_ptr<Node> head;
};

void get_data(std::vector<int>& values) {
    std::cout << "Enter the head value and than other values:\n";

    for (int i = 0; i < values.size(); i++) {
        std::cin >> values[i];
    }
}

void print_answer(const std::shared_ptr<Node>& search) {
    if (search == NULL) {
        std::cout << "There's no such element.\n";
    } else {
        std::cout << "The next element is " << search->get_value();
    }
}

int main() {
    int number, size;
    std::cout << "Enter the number and the size of the tree:\n";
    std::cin >> number >> size;
    if (size == 0) {
        std::cout << "There can't be such element, because there's no elements at all.\n";
        return 0;
    }
    std::vector<int> values(size);
    get_data(values);

    BST bst(values);

    std::shared_ptr<Node> search = bst.find_next_to(number);
    print_answer(search);

    return 0;
}
