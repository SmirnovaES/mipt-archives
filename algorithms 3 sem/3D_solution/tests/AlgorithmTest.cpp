#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "SuffixArray.h"

using testing::Eq;

namespace {
    class ClassDeclaration2: public testing::Test {
    public:
        SuffixArray obj;
        ClassDeclaration2 () {
            obj;
        }
    };
}

TEST_F(ClassDeclaration2, AssignmentTest) {
    string s = "abab";
    SuffixArray suffixArray(s);
    EXPECT_EQ(7, suffixArray.get_number_of_substrings());
}

