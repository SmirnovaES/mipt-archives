#include <iostream>
#include "../tests/Graph.h"

Graph::Graph(): size(0) {}

Graph::Graph(const vector<vector<int>>& data) {
    matrix = data;
    size = data.size();
}

void Graph::generate_min_distance() {
    for (int k = 0; k < size; ++k) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (matrix[i][k] + matrix[k][j] < matrix[i][j]) {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                }
            }
        }
    }
}

std::ostream& operator<< (std::ostream& out, const Graph& graph) {
    for (int i = 0; i < graph.size; ++i) {
        for (int j = 0; j < graph.size; ++j) {
            std::cout << graph.matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return out;
}

std::istream& operator>> (std::istream& in, Graph& graph) {
    in >> graph.size;
    graph.matrix.resize(graph.size);
    for (int i = 0; i < graph.size; ++i) {
        graph.matrix[i].resize(graph.size);
        for (int j = 0; j < graph.size; ++j) {
            in >> graph.matrix[i][j];
        }
    }
    return in;
}


vector<int>& Graph::operator[](int row) {
    return matrix[row];
}
