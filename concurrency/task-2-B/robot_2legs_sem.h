#include <iostream>
#include <condition_variable>
#include <thread>
#include "Semaphore.h"

class Robot {
public:
    Robot() {
        left.Leave();
    }
    void StepLeft() {
        left.Enter();
        std::cout << "left" << std::endl;
        right.Leave();
    }

    void StepRight() {
        right.Enter();
        std::cout << "right" << std::endl;
        left.Leave();
    }

private:
    Semaphore right;
    Semaphore left;
};
