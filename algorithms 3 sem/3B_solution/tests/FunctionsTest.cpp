#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Transformations.h"

using testing::Eq;

namespace {
    class ClassDeclaration: public testing::Test {
    public:
        Transformations obj;
        ClassDeclaration () {
            obj;
        }
    };
}

TEST_F(ClassDeclaration, FunctionsTest) {
    string s1 = "aabaaab", s2 = "aaabaab";
    Transformations transf1(s1);
    Transformations transf2(s2);

    EXPECT_EQ(vector<int>({0, 1, 0, 1, 2, 2, 3}), transf1.get_prefix_function());
    EXPECT_EQ(vector<int>({0, 2, 1, 0, 2, 1, 0}), transf2.get_z_function());
}
