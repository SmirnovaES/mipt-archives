#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PrefixFunction.h"

using testing::Eq;

namespace {
    class ClassDeclaration: public testing::Test {
    public:
        PrefixFunction obj;
        ClassDeclaration () {
            obj;
        }
    };
}

TEST_F(ClassDeclaration, BuildingTest) {
    string s = "abcabcd";
    PrefixFunction pf(s);
    EXPECT_EQ(vector<int>({0, 0, 0, 1, 2, 3, 0}), pf.get_prefix_function());
}