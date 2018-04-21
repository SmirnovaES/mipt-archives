#include <iostream>
#include <vector>
#include <fstream>
#include "tests/Flow.h"


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
/*int main() {
    freopen("i.in", "r", stdin);
    freopen("o.out", "w", stdout);
    vector<vector<int> > matrix;
    vector<vector<int> > flow;
    int start, finish;
    int num_of_edges;
    int size;
    std::cin >> size;
    while (size) {
        matrix.resize(size);
        flow.resize(size);
        for(int i = 0; i < size; i++) {
            matrix[i].assign(size, 0);
            flow[i].assign(size, 0);
        }
        std::cin >> start >> finish >> num_of_edges;
        --start;
        --finish;
        int vertex1, vertex2, capacity;
        for (int i = 0; i < num_of_edges; i++) {
            std::cin >> vertex1 >> vertex2 >> capacity;
            --vertex1;
            --vertex2;
            matrix[vertex1][vertex2] += capacity;
            matrix[vertex2][vertex1] += capacity;
        }
        std::cout << find_max_flow(matrix, flow, start, finish) << std::endl;
        std::cin >> size;
    }
    return 0;
}*/