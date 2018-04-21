/*
int main() {
    int n, m;
    std::cin >> n >> m;
    vector<int> a;
    for (int i = 0; i < n; i++) {
        int k;
        std::cin >> k;
        a.push_back(k);
    }
    SegmentTree st(a);
    for (int i = 0; i < m; i++) {
        int left, right;
        std::cin >> left >> right;
        std::cout << st.get_second_order_statistics(left, right) << std::endl;
    }
    return 0;
}*/

#include <iostream>
#include <vector>
#include <fstream>
#include "tests/SegmentTree.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}