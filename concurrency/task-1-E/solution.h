#include <atomic>
#include <vector>
#include <thread>

class PetersonMutex{
public:
    void lock(std::size_t current_thread) {
        want[current_thread].store(true);
        victim.store(current_thread);
        while(want[1 - current_thread].load() && victim.load() == current_thread) {
            std::this_thread::yield();
        }
        blocking_thread.store(current_thread);
    }

    void unlock(std::size_t current_thread) {
        want[current_thread].store(false);
    }

    bool get_blocking_thread() {
        return blocking_thread.load();
    }
private:
    std::atomic_bool want[2];
    std::atomic_size_t victim;
    std::atomic_bool blocking_thread;
};

class TreeMutex {
public:
    TreeMutex(std::size_t n_threads) {
        mutexes = std::vector<PetersonMutex>(get_tree_size(n_threads));
    }

    void lock(std::size_t current_thread) {
        std::size_t current_position = mutexes.size() / 2 + current_thread / 2;
        bool local_position = (current_thread % 2 != 0);
        while(true) {
            mutexes[current_position].lock(local_position);
            if (current_position == 0) {
                break;
            }
            local_position = (current_position % 2 == 0);
            current_position = (current_position - 1) / 2;
        }
    }

    void unlock(std::size_t current_thread) {
        std::size_t current_position = 0;
        while (current_position <= mutexes.size() / 2 + current_thread / 2) {
            bool local_position = mutexes[current_position].get_blocking_thread();
            std::size_t old_position = current_position;
            current_position = current_position * 2 + 1 + local_position;
            mutexes[old_position].unlock(local_position);
        }
    }

private:
    std::vector<PetersonMutex> mutexes;
    std::size_t get_tree_size(std::size_t n_threads) {
        std::size_t size = 1;
        while (size < n_threads) {
            size *= 2;
        }
        return 2*size - 1;
    }
};