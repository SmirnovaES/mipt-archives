#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "SegmentTree.h"

using testing::Eq;

namespace {
    class ClassDeclaration: public testing::Test {
    public:
        SegmentTree obj;
        ClassDeclaration () {
            obj;
        }
    };
}

TEST_F(ClassDeclaration, AlgorithmTest) {
    vector<int> data{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    SegmentTree segmentTree(data);

    EXPECT_EQ(2, segmentTree.get_second_order_statistics(1, 2));
    EXPECT_EQ(2, segmentTree.get_second_order_statistics(1, 10));
    EXPECT_EQ(3, segmentTree.get_second_order_statistics(2, 7));
}