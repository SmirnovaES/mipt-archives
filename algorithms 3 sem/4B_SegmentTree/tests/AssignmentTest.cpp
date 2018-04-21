#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "SegmentTree.h"

using testing::Eq;

namespace {
    class ClassDeclaration2: public testing::Test {
    public:
        SegmentTree obj;
        ClassDeclaration2 () {
            obj;
        }
    };
}

TEST_F(ClassDeclaration2, AssignmentTest) {
    vector<int> data{1, 2, 3, 4, 5};
    SegmentTree segmentTree(data);

    EXPECT_EQ(make_pair(2, 3), segmentTree.get_borders(4));
    EXPECT_EQ(make_pair(0, 4), segmentTree.get_borders(0));
}