#include <vector>
#include <istream>
#include <ostream>

#ifndef FLOYD_GRAPH_H
#define FLOYD_GRAPH_H

using std::vector;

class Graph{
private:
    vector<vector<int>> matrix;
    int size;
public:
    Graph();

    Graph(const vector<vector<int>>& data);

    vector<int>& operator[] (int row);

    void generate_min_distance();

    friend std::ostream& operator<< (std::ostream& out, const Graph& graph);

    friend std::istream& operator>> (std::istream& in, Graph& graph);

};



#endif //FLOYD_GRAPH_H
