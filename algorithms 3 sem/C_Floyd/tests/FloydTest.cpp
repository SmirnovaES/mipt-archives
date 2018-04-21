#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Graph.h"

using testing::Eq;

namespace {
    class ClassDeclaration: public testing::Test {
    public:
        Graph obj;
        ClassDeclaration () {
            obj;
        }
    };
}

TEST_F(ClassDeclaration, FloydTest) {
    std::stringstream ss;
    vector<vector<int>> data;
    data.push_back({0, 5, 9, 100});
    data.push_back({100, 0, 2, 8});
    data.push_back({100, 100, 0, 7});
    data.push_back({4, 100, 100, 0});
    Graph graph(data);
    graph.generate_min_distance();

    EXPECT_EQ(0, graph[0][0]);
    EXPECT_EQ(5, graph[0][1]);
    EXPECT_EQ(7, graph[0][2]);
    EXPECT_EQ(13, graph[0][3]);
    EXPECT_EQ(12, graph[1][0]);
    EXPECT_EQ(0, graph[1][1]);
    EXPECT_EQ(2, graph[1][2]);
    EXPECT_EQ(8, graph[1][3]);
    EXPECT_EQ(11, graph[2][0]);
    EXPECT_EQ(16, graph[2][1]);
    EXPECT_EQ(0, graph[2][2]);
    EXPECT_EQ(7, graph[2][3]);
    EXPECT_EQ(4, graph[3][0]);
    EXPECT_EQ(9, graph[3][1]);
    EXPECT_EQ(11, graph[3][2]);
    EXPECT_EQ(0, graph[3][3]);
}