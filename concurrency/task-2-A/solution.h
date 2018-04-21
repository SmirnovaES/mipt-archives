#include <mutex>
#include <condition_variable>

template <class ConditionVariable = std::condition_variable>
class CyclicBarrier {
public:
    CyclicBarrier(size_t num_threads) {
        num_of_threads = num_threads;
        queue_size = 0;
        num_ready = 0;
        is_ready = true;
    }

    void Pass() {
        std::unique_lock<std::mutex> lock(local_mutex);
        while (!is_ready) {
            cv_for_turn.wait(lock);
        }
        ++queue_size;
        while (queue_size < num_of_threads) {
            cv_for_queue.wait(lock);
        }
        is_ready = false;
        ++num_ready;
        cv_for_queue.notify_one();
        if (num_ready == num_of_threads) {
            queue_size = 0;
            num_ready = 0;
            is_ready = true;
            cv_for_turn.notify_all();
        }
        return;
    }
private:
    std::mutex local_mutex;
    size_t num_of_threads;
    size_t queue_size;
    size_t num_ready;
    ConditionVariable cv_for_queue;
    ConditionVariable cv_for_turn;
    bool is_ready;
};
