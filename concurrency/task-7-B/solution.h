#pragma once

#include <thread>
#include <atomic>

///////////////////////////////////////////////////////////////////////

template <typename T, template <typename U> class Atomic = std::atomic>
class LockFreeQueue {
    struct Node {
        T element_{};
        Atomic<Node*> next_{nullptr};

        explicit Node(T element, Node* next = nullptr)
                : element_(std::move(element))
                , next_(next) {
        }

        explicit Node() {
        }
    };

public:
    explicit LockFreeQueue() {
        Node* dummy = new Node{};
        head_ = dummy;
        tail_ = dummy;
        trash_head_ = dummy;
    }

    ~LockFreeQueue() {
        Node* curr_head = trash_head_.load();
        while(curr_head != nullptr) {
            Node* to_delete = curr_head;
            curr_head = curr_head->next_.load();
            delete to_delete;
        }
    }

    void Enqueue(T element) {
        threads_in_queue.fetch_add(1);
        Node* new_tail = new Node(element);
        Node* curr_tail;
        while (true) {
            curr_tail = tail_.load();
            if (!curr_tail->next_.load()) {
                Node* null_ptr = nullptr;
                if (curr_tail->next_.compare_exchange_strong(null_ptr, new_tail)) {
                    break;
                }
            } else {
                tail_.compare_exchange_strong(curr_tail, curr_tail->next_.load());
            }
        }
        tail_.compare_exchange_strong(curr_tail, new_tail);
        threads_in_queue.fetch_sub(1);
    }

    bool Dequeue(T& element) {
        threads_in_queue.fetch_add(1);
        while (true) {
            Node* curr_head = head_.load();
            Node* curr_tail = tail_.load();
            if (curr_head == curr_tail) {
                if (!curr_head->next_.load()) {
                    threads_in_queue.fetch_sub(1);
                    return false;
                } else {
                    tail_.compare_exchange_strong(curr_head, curr_head->next_.load());
                }
            } else {
                if (head_.compare_exchange_strong(curr_head, curr_head->next_.load())) {
                    element = curr_head->next_.load()->element_;

                    try_delete_trash(curr_head);
                    return true;
                }
            }
        }
    }

    void try_delete_trash(Node* curr_head) {
        if (threads_in_queue.load() == 1) {
            Node* old_trash_head = trash_head_.exchange(curr_head);
            if (threads_in_queue.load() == 1) {
                while (old_trash_head != curr_head) {
                    Node* to_delete = old_trash_head;
                    old_trash_head = old_trash_head->next_.load();
                    delete to_delete;
                }
            } else {
                trash_head_.exchange(old_trash_head);
            }
        }
        threads_in_queue.fetch_sub(1);
    }

private:
    Atomic<Node*> head_{nullptr};
    Atomic<Node*> tail_{nullptr};
    Atomic<Node*> trash_head_{nullptr};
    Atomic<int> threads_in_queue{0};
};

///////////////////////////////////////////////////////////////////////
