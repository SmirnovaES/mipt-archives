#include <iostream>
#include <condition_variable>
#include <thread>

class Robot {
public:
    Robot() {
        turn = true;
    }
    void StepLeft() {
        std::unique_lock<std::mutex> lock(local_mutex);
        while (!turn) {
            cv_for_left.wait(lock);
        }
        std::cout << "left" << std::endl;
        turn = false;
        cv_for_right.notify_one();
    }

    void StepRight() {
        std::unique_lock<std::mutex> lock(local_mutex);
        while (turn) {
            cv_for_right.wait(lock);
        }
        std::cout << "right" << std::endl;
        turn = true;
        cv_for_left.notify_one();
    }

private:
    std::condition_variable cv_for_left;
    std::condition_variable cv_for_right;
    std::mutex local_mutex;
    bool turn; //true -- left, false -- right
};
