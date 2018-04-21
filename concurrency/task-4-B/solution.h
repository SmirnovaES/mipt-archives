#pragma once

#include "arena_allocator.h"

#include <atomic>
#include <limits>
#include <mutex>

template <typename T>
struct ElementTraits {
    static T Min() {
        return std::numeric_limits<T>::min();
    }
    static T Max() {
        return std::numeric_limits<T>::max();
    }
};

class SpinLock {
public:
    explicit SpinLock() {
        locked.store(false);
    }

    void Lock() {
        while(locked.exchange(true)) {
            std::this_thread::yield();
        }
    }

    void Unlock() {
        locked.store(false);
    }


    // adapters for BasicLockable concept

    void lock() {
        Lock();
    }

    void unlock() {
        Unlock();
    }

private:
    std::atomic<bool> locked;
};

template <typename T>
class OptimisticLinkedSet {
private:
    struct Node {
        T element_;
        std::atomic<Node*> next_;
        SpinLock lock_{};
        std::atomic<bool> marked_{false};

        Node(const T& element, Node* next = nullptr)
                : element_(element),
                  next_(next) {
        }
    };

    struct Edge {
        Node* pred_;
        Node* curr_;

        Edge(Node* pred, Node* curr)
                : pred_(pred),
                  curr_(curr) {
        }
    };

public:
    explicit OptimisticLinkedSet(ArenaAllocator& allocator)
            : allocator_(allocator) {
        CreateEmptyList();
        list_size_.store(0);
    }

    bool Insert(const T& element) {
        while(true) {
            Edge curr_edge = Locate(element);
            std::lock_guard<SpinLock> lock_pred(curr_edge.pred_->lock_);
            std::lock_guard<SpinLock> lock_curr(curr_edge.curr_->lock_);
            if (Validate(curr_edge)) {
                if (curr_edge.curr_->element_ == element) {
                    return false;
                }
                list_size_.fetch_add(1);
                Node *new_node = allocator_.New<Node>(element, curr_edge.curr_);
                curr_edge.pred_->next_.store(new_node);
                return true;
            }
        }
    }

    bool Remove(const T& element) {
        while (true) {
            Edge curr_edge = Locate(element);
            std::lock_guard<SpinLock> lock_pred(curr_edge.pred_->lock_);
            std::lock_guard<SpinLock> lock_curr(curr_edge.curr_->lock_);
            if (Validate(curr_edge)) {
                if (curr_edge.curr_->element_ != element) {
                    return false;
                }
                list_size_.fetch_sub(1);
                curr_edge.curr_->marked_.store(true);
                curr_edge.pred_->next_.store(curr_edge.curr_->next_);
                return true;
            }
        }
    }

    bool Contains(const T& element) const {
        Edge curr_edge = Locate(element);
        std::lock_guard<SpinLock> lock_pred(curr_edge.pred_->lock_);
        std::lock_guard<SpinLock> lock_curr(curr_edge.curr_->lock_);
        return (!curr_edge.curr_->marked_.load()) && curr_edge.curr_->element_ == element;
    }

    std::size_t Size() const {
        return list_size_.load();
    }

private:
    void CreateEmptyList() {
        head_ = allocator_.New<Node>(ElementTraits<T>::Min());
        head_->next_ = allocator_.New<Node>(ElementTraits<T>::Max());
    }

    Edge Locate(const T& element) const {
        Node* curr_node = head_;
        while (curr_node->next_.load()->element_ < element) {
            curr_node = curr_node->next_;
        }
        return Edge{curr_node, curr_node->next_};
    }

    bool Validate(const Edge& edge) const {
        return edge.pred_->next_ == edge.curr_ && !edge.pred_->marked_.load() && !edge.curr_->marked_.load();
    }

private:
    ArenaAllocator& allocator_;
    Node* head_{nullptr};
    std::atomic<size_t> list_size_;
};

template <typename T> using ConcurrentSet = OptimisticLinkedSet<T>;