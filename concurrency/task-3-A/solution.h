#include <cstdio>
#include <deque>
#include <mutex>
#include <condition_variable>

template <class T, class Container = std::deque<T>>
class BlockingQueue {
public:
    explicit BlockingQueue(const size_t& capacity) {
        queue_capacity = capacity;
        curr_size = 0;
        is_shut_down = false;
    }
    void Put(T&& element) {
        std::unique_lock<std::mutex> lock(local_mutex);
        while(!is_shut_down && curr_size >= queue_capacity) {
            cv_for_put.wait(lock);
        }
        if (is_shut_down) {
            throw std::runtime_error("The queue is shut down");
        }
        data.push_back(std::move(element));
        ++curr_size;
        cv_for_get.notify_one();
        lock.unlock();
    }
    bool Get(T& result) {
        std::unique_lock<std::mutex> lock(local_mutex);
        if (is_shut_down && curr_size == 0) {
            lock.unlock();
            return false;
        }
        while(curr_size == 0) {
            cv_for_get.wait(lock);
        }
        result = std::move(data.front());
        data.pop_front();
        --curr_size;
        cv_for_put.notify_one();
        lock.unlock();
        return true;
    }
    void Shutdown() {
        std::unique_lock<std::mutex> lock(local_mutex);
        is_shut_down = true;
        cv_for_get.notify_all();
        lock.unlock();
    }
private:
    Container data;
    bool is_shut_down;
    size_t queue_capacity;
    size_t curr_size;
    std::mutex local_mutex;
    std::condition_variable cv_for_put;
    std::condition_variable cv_for_get;
};