#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "MST.h"

using testing::Eq;

namespace {
    class ClassDeclaration: public testing::Test {
    public:
        MST obj;
        ClassDeclaration () {
            obj;
        }
    };
}

TEST_F(ClassDeclaration, AssignmentTest) {
    std::istringstream ss("4 4 1 2 1 2 3 2 3 4 5 4 1 4");
    MST mst;
    ss >> mst;
    EXPECT_EQ(1, mst.get_edge(1, 2).weight);
    EXPECT_EQ(2, mst.get_edge(2, 3).weight);
    EXPECT_EQ(5, mst.get_edge(3, 4).weight);
    EXPECT_EQ(4, mst.get_edge(4, 1).weight);
}