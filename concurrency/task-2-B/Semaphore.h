#ifndef SEMAPHORE
#define SEMAPHORE

#include <condition_variable>
#include <thread>

class Semaphore {
public:
    Semaphore() {
        counter = 0;
    }
    void Enter() {
        std::unique_lock<std::mutex> lock(local_mutex);
        while(counter <= 0) {
            cv.wait(lock);
        }
        counter--;
    }

    void Leave() {
        std::lock_guard<std::mutex> lock(local_mutex);
        counter++;
        cv.notify_one();
    }

private:
    std::mutex local_mutex;
    size_t counter;
    std::condition_variable cv;
};
