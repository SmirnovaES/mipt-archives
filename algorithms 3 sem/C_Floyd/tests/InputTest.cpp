#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Graph.h"

using testing::Eq;

namespace {
    class ClassDeclaration2: public testing::Test {
    public:
        Graph obj2;
        ClassDeclaration2 () {
            obj2;
        }
    };
}

TEST_F(ClassDeclaration2, InputTest) {
    std::istringstream ss("5 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25");
    Graph graph;
    ss >> graph;

    EXPECT_EQ(1, graph[0][0]);
    EXPECT_EQ(2, graph[0][1]);
    EXPECT_EQ(3, graph[0][2]);
    EXPECT_EQ(4, graph[0][3]);
    EXPECT_EQ(5, graph[0][4]);
    EXPECT_EQ(6, graph[1][0]);
    EXPECT_EQ(7, graph[1][1]);
    EXPECT_EQ(8, graph[1][2]);
    EXPECT_EQ(9, graph[1][3]);
    EXPECT_EQ(10, graph[1][4]);
    EXPECT_EQ(11, graph[2][0]);
    EXPECT_EQ(12, graph[2][1]);
    EXPECT_EQ(13, graph[2][2]);
    EXPECT_EQ(14, graph[2][3]);
    EXPECT_EQ(15, graph[2][4]);
    EXPECT_EQ(16, graph[3][0]);
    EXPECT_EQ(17, graph[3][1]);
    EXPECT_EQ(18, graph[3][2]);
    EXPECT_EQ(19, graph[3][3]);
    EXPECT_EQ(20, graph[3][4]);
    EXPECT_EQ(21, graph[4][0]);
    EXPECT_EQ(22, graph[4][1]);
    EXPECT_EQ(23, graph[4][2]);
    EXPECT_EQ(24, graph[4][3]);
    EXPECT_EQ(25, graph[4][4]);
}
