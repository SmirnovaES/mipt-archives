#include "../tests/Flow.h"

Flow::Flow() {}

Flow::Flow(const vector<vector<int>>& new_flow, const vector<vector<int>>& new_capacity):
        flow(new_flow), capacity(new_capacity) {}

Flow::Flow(const vector<vector<int>>& new_capacity): capacity(new_capacity) {
    flow.assign(new_capacity.size(), vector<int>(new_capacity.size(), 0));
}

void Flow::get_min_way(int start, int finish, vector<int>& curr_way) {
    curr_way.clear();
    int curr_v;
    unsigned int size = capacity.size();
    queue<int> queue;
    vector<int> answer;
    bool finish_found = false;

    vector<int> parents(size, -1);
    vector<int> distance(size, -1);

    queue.push(start);
    distance[start] = 0;

    while (queue.size() != 0) {
        curr_v = queue.front();
        queue.pop();

        for (int i = 0; i < size; i++) {
            if (capacity[curr_v][i] - flow[curr_v][i] > 0 && distance[i] == -1) {
                queue.push(i);
                distance[i] = distance[curr_v] + 1;
                parents[i] = curr_v;
                if (i == finish) {
                    finish_found = true;
                    int curr_end = finish;
                    while (curr_end != start) {
                        curr_way.push_back(curr_end);
                        curr_end = parents[curr_end];
                    }
                    curr_way.push_back(start);
                    break;
                }
            }
        }
        if (finish_found) break;
    }
}


int Flow::find_max_flow(int start, int finish) {
    int max_flow = 0;
    vector<int> curr_way;
    get_min_way(start, finish, curr_way);

    while (curr_way.size() != 0) {
        int curr_min_flow = INT_MAX;
        for (int i = 1; i < curr_way.size(); i++) {
            if (capacity[curr_way[i]][curr_way[i - 1]] - flow[curr_way[i]][curr_way[i - 1]] < curr_min_flow) {
                curr_min_flow = capacity[curr_way[i]][curr_way[i - 1]] - flow[curr_way[i]][curr_way[i - 1]];
            }
        }
        max_flow += curr_min_flow;

        for (int i = 1; i < curr_way.size(); i++) {
            flow[curr_way[i]][curr_way[i - 1]] += curr_min_flow;
            flow[curr_way[i - 1]][curr_way[i]] -= curr_min_flow;
        }
        get_min_way(start, finish, curr_way);
    }
    return max_flow;
}

int Flow::get_flow(int x, int y) const {
    return flow[x][y];
}

int Flow::get_capacity(int x, int y) const {
    return capacity[x][y];
}
