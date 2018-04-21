#include <vector>
#include <queue>
#include <limits.h>

#ifndef MAXFLOW_FLOW_H
#define MAXFLOW_FLOW_H

using std::vector;
using std::queue;

class Flow {
private:
    vector<vector<int>> flow;
    vector<vector<int>> capacity;
public:
    Flow();

    Flow(const vector<vector<int>>& new_flow, const vector<vector<int>>& new_capacity);

    Flow(const vector<vector<int>>& new_capacity);

    int get_flow(int x, int y) const;

    int get_capacity(int x, int y) const;

    void get_min_way(int start, int finish, vector<int>& curr_way);

    int find_max_flow(int start, int finish);
};


#endif //MAXFLOW_FLOW_H
