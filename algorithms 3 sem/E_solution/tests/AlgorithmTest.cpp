
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Flow.h"

using testing::Eq;

namespace {
    class ClassDeclaration2: public testing::Test {
    public:
        Flow obj;
        ClassDeclaration2 () {
            obj;
        }
    };
}

TEST_F(ClassDeclaration2, AlgorithmTest) {
    int start = 0, finish = 3;
    vector<vector<int>> capacity;
    capacity.push_back({0, 20, 10, 0});
    capacity.push_back({20, 0, 5, 10});
    capacity.push_back({10, 5, 0, 20});
    capacity.push_back({0, 10, 20, 0});
    Flow flow(capacity);
    EXPECT_EQ(25, flow.find_max_flow(start, finish));
}
