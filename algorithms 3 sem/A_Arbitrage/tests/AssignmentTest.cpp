#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Arbitrage.h"

using testing::Eq;

namespace {
    class ClassDeclaration2: public testing::Test {
    public:
        Arbitrage obj;
        ClassDeclaration2 () {
            obj;
        }
    };
}

TEST_F(ClassDeclaration2, AssignmentTest) {
    std::istringstream ss("3 2 1 32 4 8 16");
    Arbitrage arb;
    ss >> arb;
    EXPECT_EQ(1.0, arb[0][0]);
    EXPECT_EQ(1.0, arb[1][1]);
    EXPECT_EQ(1.0, arb[2][2]);
    EXPECT_EQ(1.0 / 2, arb[0][1]);
    EXPECT_EQ(1.0, arb[0][2]);
    EXPECT_EQ(1.0 / 32, arb[1][0]);
    EXPECT_EQ(1.0 / 4, arb[1][2]);
    EXPECT_EQ(1.0 / 8, arb[2][0]);
    EXPECT_EQ(1.0 / 16, arb[2][1]);
}
