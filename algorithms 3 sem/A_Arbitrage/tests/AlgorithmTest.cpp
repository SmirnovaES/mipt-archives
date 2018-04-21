#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Arbitrage.h"

using testing::Eq;

namespace {
    class ClassDeclaration: public testing::Test {
    public:
        Arbitrage obj;
        ClassDeclaration () {
            obj;
        }
    };
}

TEST_F(ClassDeclaration, AlgorithmTest) {
    std::istringstream ss("4 32.1 1.50 78.66 0.03 0.04 2.43 0.67 21.22 51.89 0.01 -1 0.02");
    Arbitrage arb;
    ss >> arb;
    EXPECT_EQ(true, arb.has_arbitrage());
}