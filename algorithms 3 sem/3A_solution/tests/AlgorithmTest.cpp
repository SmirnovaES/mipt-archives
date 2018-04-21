#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PrefixFunction.h"

using testing::Eq;

namespace {
    class ClassDeclaration2: public testing::Test {
    public:
        PrefixFunction obj;
        ClassDeclaration2 () {
            obj;
        }
    };
}

TEST_F(ClassDeclaration2, AlgorithmTest) {
    string s = "abacababa", pattern = "aba";
    PrefixFunction pf(s, pattern);
    vector<int> indexes;
    pf.get_indexes_of_substring(indexes);
    EXPECT_EQ(vector<int>({0, 4, 6}), indexes);
}