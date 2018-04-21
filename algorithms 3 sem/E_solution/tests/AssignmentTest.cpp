

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Flow.h"

using testing::Eq;

namespace {
    class ClassDeclaration: public testing::Test {
    public:
        Flow obj;
        ClassDeclaration () {
            obj;
        }
    };
}

TEST_F(ClassDeclaration, AssignmentTest) {
    vector<vector<int>> capacity;
    capacity.push_back({0, 5, 9});
    capacity.push_back({100, 0, 2});
    capacity.push_back({100, 100, 0});
    Flow flow(capacity);
    EXPECT_EQ(0, flow.get_capacity(0, 0));
    EXPECT_EQ(5, flow.get_capacity(0, 1));
    EXPECT_EQ(9, flow.get_capacity(0, 2));
    EXPECT_EQ(100, flow.get_capacity(1, 0));
    EXPECT_EQ(0, flow.get_capacity(1, 1));
    EXPECT_EQ(2, flow.get_capacity(1, 2));
    EXPECT_EQ(100, flow.get_capacity(2, 0));
    EXPECT_EQ(100, flow.get_capacity(2, 1));
    EXPECT_EQ(0, flow.get_capacity(2, 2));
}

TEST_F(ClassDeclaration, AssignmentTest2) {
    vector<vector<int>> capacity;
    vector<vector<int>> flow;
    capacity.push_back({5, 2});
    capacity.push_back({3, 8});
    flow.push_back({3, 1});
    flow.push_back({1, 0});
    Flow _flow(flow, capacity);
    EXPECT_EQ(5, _flow.get_capacity(0, 0));
    EXPECT_EQ(2, _flow.get_capacity(0, 1));
    EXPECT_EQ(3, _flow.get_capacity(1, 0));
    EXPECT_EQ(8, _flow.get_capacity(1, 1));
    EXPECT_EQ(3, _flow.get_flow(0, 0));
    EXPECT_EQ(1, _flow.get_flow(0, 1));
    EXPECT_EQ(1, _flow.get_flow(1, 0));
    EXPECT_EQ(0, _flow.get_flow(1, 1));

}