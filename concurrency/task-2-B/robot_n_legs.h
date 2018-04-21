#include <iostream>
#include <condition_variable>
#include <thread>
#include <vector>
#include "Semaphore.h"

class Robot {
public:
    Robot(size_t num_of_legs = 2) {
        num_legs = num_of_legs;
        legs = std::vector<Semaphore>(num_of_legs);
        legs[0].Leave();
    }

    void Step(const std::size_t foot) {
        legs[foot].Enter();
        std::cout << "foot " << foot << std::endl;
        legs[(foot + 1) % num_legs].Leave();
    }

private:
    std::vector<Semaphore> legs;
    size_t num_legs;
};
