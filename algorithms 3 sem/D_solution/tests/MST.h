#include <fstream>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

#ifndef D_MST_MST_H
#define D_MST_MST_H

using std::vector;
using std::shared_ptr;

struct Edge {
    int weight;
    int start_vertice;
    int end_vertice;
};

class MST {
private:
    vector<Edge> edges;
    vector<int> trees;
public:

    MST();

    MST(const vector<Edge>& new_edges, const vector<int>& new_trees);

    friend std::istream& operator>>(std::istream& in, MST& mst);

    int get_MST_size();

    Edge& get_edge(int start, int finish);

    int get_tree(int i);
};


#endif //D_MST_MST_H
