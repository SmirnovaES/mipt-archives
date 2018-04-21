#include "../tests/SegmentTree.h"

Vertice::Vertice(): stats(make_pair(INT_MAX, INT_MAX)), left_border(INT_MAX), right_border(INT_MAX) {}

Vertice::Vertice(int left, int right, pair<int, int> new_stats): left_border(left), right_border(right), stats(new_stats) {}

int SegmentTree::find_size(int n) {
    int size = 1;
    while (size < n) {
        size *= 2;
    }
    return size;
}

pair<int, int> SegmentTree::get_min_stats(pair<int, int> pair1, pair<int, int> pair2) {
    vector<int> values{pair1.first, pair1.second, pair2.first, pair2.second};
    std::sort(values.begin(), values.end());
    return make_pair(values[0], values[1]);
};

pair<int, int> SegmentTree::get_order_statistics(int left_border, int right_border, int curr_vert) {
    if (left_border <= data[curr_vert].left_border && right_border >= data[curr_vert].right_border) {
        return data[curr_vert].stats;
    }
    if (left_border > data[curr_vert].right_border || right_border < data[curr_vert].left_border) {
        return make_pair(INT_MAX, INT_MAX);
    }
    return get_min_stats(get_order_statistics(left_border, right_border, curr_vert * 2 + 1),
                         get_order_statistics(left_border, right_border, curr_vert * 2 + 2));
}

SegmentTree::SegmentTree(): size(0) {}

SegmentTree::SegmentTree(const vector<int>& new_data) {
    size = find_size(new_data.size());
    data.resize(2 * size - 1);
    data.assign(2 * size - 1, Vertice());
    for (int i = size - 1; i < size + new_data.size() - 1; ++i) {
        data[i].stats = make_pair(new_data[i - size + 1], INT_MAX);
        data[i].left_border = i - size + 1;
        data[i].right_border = i - size + 1;
    }
    for (int i = size - 2; i >= 0; --i) {
        data[i].stats = get_min_stats(data[2 * i + 1].stats, data[2 * i + 2].stats);
        data[i].left_border = data[2 * i + 1].left_border;
        if (data[2 * i + 2].right_border == INT_MAX) {
            data[i].right_border = data[2 * i + 1].right_border;
        } else {
            data[i].right_border = data[2 * i + 2].right_border;

        }
    }
}

int SegmentTree::get_second_order_statistics(int left_border, int right_border) {
    return get_order_statistics(left_border - 1, right_border - 1, 0).second;
}

pair<int, int> SegmentTree::get_borders(int vert) {
    return make_pair(data[vert].left_border, data[vert].right_border);
}