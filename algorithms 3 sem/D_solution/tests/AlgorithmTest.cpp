#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "MST.h"

using testing::Eq;

namespace {
    class ClassDeclaration2: public testing::Test {
    public:
        MST obj;
        ClassDeclaration2 () {
            obj;
        }
    };
}

TEST_F(ClassDeclaration2, AlgorithmTest) {
    std::istringstream ss("4 4 1 2 1 2 3 2 3 4 5 4 1 4");
    MST mst;
    ss >> mst;
    EXPECT_EQ(7, mst.get_MST_size());
}