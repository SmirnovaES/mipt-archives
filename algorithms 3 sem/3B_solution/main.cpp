#include <iostream>
#include <vector>
#include <fstream>
#include "tests/Transformations.h"


#include <gtest/gtest.h>
#include <gmock/gmock.h>

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}