#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "SuffixArray.h"

using testing::Eq;

namespace {
    class ClassDeclaration: public testing::Test {
    public:
        SuffixArray obj;
        ClassDeclaration () {
            obj;
        }
    };
}

TEST_F(ClassDeclaration, AssignmentTest) {
    string s = "abaab";
    SuffixArray suffixArray(s);
    EXPECT_EQ(vector<int>({5, 2, 3, 0, 4, 1}), suffixArray.get_suffix_array());
}