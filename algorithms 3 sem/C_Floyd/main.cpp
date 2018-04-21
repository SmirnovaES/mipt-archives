#include <iostream>
#include <vector>
#include <fstream>
#include "tests/Graph.h"


#include <gtest/gtest.h>
#include <gmock/gmock.h>


//int main() {
//    Graph graph;
//    std::cin >> graph;
//    graph.generate_min_distance();
//    std::cout << graph;
//    return 0;
//}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}