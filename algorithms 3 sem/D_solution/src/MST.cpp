#include "../tests/MST.h"

MST::MST() {}

MST::MST(const vector<Edge>& new_edges, const vector<int>& new_trees): edges(new_edges), trees(new_trees) {}

std::istream& operator>>(std::istream& in, MST& mst) {
    int num_of_vertices, num_of_edges;

    in >> num_of_vertices >> num_of_edges;
    mst.edges.resize(num_of_edges);
    mst.trees.resize(num_of_vertices);

    for (int i = 0; i < mst.edges.size(); ++i) {
        in >> mst.edges[i].start_vertice >> mst.edges[i].end_vertice >> mst.edges[i].weight;
        mst.edges[i].start_vertice--;
        mst.edges[i].end_vertice--;
    }
    std::sort(mst.edges.begin(), mst.edges.end(), [] (Edge edge1, Edge edge2) {
        return edge1.weight < edge2.weight;
    });
    for (int i = 0; i < mst.trees.size(); ++i) {
        mst.trees[i] = i;
    }
    return in;
}

int MST::get_MST_size() {
    int MST_size = 0;
    for (int i = 0; i < edges.size(); ++i) {
        if (trees[edges[i].start_vertice] != trees[edges[i].end_vertice]) {
            int curr_old_tree = trees[edges[i].end_vertice];
            for (int j = 0; j < trees.size(); ++j) {
                if (trees[j] == curr_old_tree) {
                    trees[j] = trees[edges[i].start_vertice];
                }
            }
            MST_size += edges[i].weight;
        }
    }
    return MST_size;
}

Edge& MST::get_edge(int start, int finish) {
    for (int i = 0; i < edges.size(); i++) {
        if (edges[i].start_vertice == start - 1 && edges[i].end_vertice == finish - 1) {
            return edges[i];
        }
    }
}

int MST::get_tree(int i) {
    return trees[i];
}