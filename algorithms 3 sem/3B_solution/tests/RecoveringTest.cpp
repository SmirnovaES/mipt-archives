#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Transformations.h"

using testing::Eq;

namespace {
    class ClassDeclaration2: public testing::Test {
    public:
        Transformations obj;
        ClassDeclaration2 () {
            obj;
        }
    };
}

TEST_F(ClassDeclaration2, RecoveringTest) {
    vector<int> v1{0, 1, 2, 3, 0};
    vector<int> v2{5, 3, 2, 1, 0};
    Transformations transf1(v1, true);
    Transformations transf2(v2, false);
    string s1, s2;
    transf1.prefix_function_to_string(s1);
    transf2.z_function_to_prefix_function();
    transf2.prefix_function_to_string(s2);
    EXPECT_EQ("aaaab", s1);
    EXPECT_EQ("aaaab", s2);
}
