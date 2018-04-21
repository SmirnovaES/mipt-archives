#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using std::vector;
using std::pair;
using std::make_pair;

struct Vertice {
    Vertice();
    Vertice(int left, int right, pair<int, int> new_stats);
    int left_border;
    int right_border;
    pair<int, int> stats;
};

class SegmentTree {
private:
    vector<Vertice> data;
    int size;

    int find_size(int n);

    pair<int, int> get_min_stats(pair<int, int> pair1, pair<int, int> pair2);

    pair<int, int> get_order_statistics(int left_border, int right_border, int curr_vert);
public:
    SegmentTree();

    SegmentTree(const vector<int>& new_data);

    int get_second_order_statistics(int left_border, int right_border);

    pair<int, int> get_borders(int vert);
};
