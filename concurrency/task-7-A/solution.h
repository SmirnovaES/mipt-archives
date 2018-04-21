#pragma once

#include <atomic>
#include <thread>

///////////////////////////////////////////////////////////////////////

template <typename T>
class LockFreeStack {
    struct Node {
        Node(const T& new_element): element(new_element), next(nullptr) {}
        T element;
        std::atomic<Node*> next;
    };

 public:
    explicit LockFreeStack(): top_(nullptr), trash_head_(nullptr) {
    }

    ~LockFreeStack() {
        Node* curr_top = top_.load();
        while (curr_top != nullptr) {
            Node* to_delete = curr_top;
            curr_top = curr_top->next.load();
            delete to_delete;
        }
        curr_top = trash_head_.load();
        while (curr_top != nullptr) {
            Node* to_delete = curr_top;
            curr_top = curr_top->next.load();
            delete to_delete;
        }
    }

    void Push(T element) {
        Node* new_top = new Node(element);

        Node* curr_top = top_.load();
        new_top->next.store(curr_top);

        while (!top_.compare_exchange_weak(curr_top, new_top)) {
            new_top->next.store(curr_top);
        }
    }

    bool Pop(T& element) {
        Node* curr_top = top_.load();

        while(true) {
            if (curr_top == nullptr) {
                return false;
            }
            if (top_.compare_exchange_weak(curr_top, curr_top->next.load())) {
                element = curr_top->element;
                Node* curr_head = trash_head_.load();
                curr_top->next.store(curr_head);

                while (!trash_head_.compare_exchange_weak(curr_head, curr_top)) {
                    curr_top->next.store(curr_head);
                }
                return true;
            }
        }
    }

 private:
    std::atomic<Node*> top_;
    std::atomic<Node*> trash_head_;
};

///////////////////////////////////////////////////////////////////////

template <typename T>
using ConcurrentStack = LockFreeStack<T>;

///////////////////////////////////////////////////////////////////////
