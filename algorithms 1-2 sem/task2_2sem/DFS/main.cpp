#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>

std::vector<bool> visited;

void dfs(int v, const std::vector<std::vector <int>>& tasks, std::vector<int>& visited, std::vector<int>& time_out, int& time) {
    visited[v] = true;
    for (int i = 0; i < visited.size(); i++) {
        if (tasks[v][i] == 1 && !visited[i]) {
            dfs(i, tasks, visited, time_out, time);
        }
    }
    time_out[v] = time++;
}

int main() {
    int num_of_tasks;

    std::cin >> num_of_tasks;

    //initializing graph's matrix
    std::vector <std::vector <int>> tasks;
    for (int i = 0; i < num_of_tasks; i++) {
        std::vector<int> curr_vec;
        tasks.push_back(curr_vec);
        for (int j = 0; j < num_of_tasks; j++) {
            tasks[i].push_back(0);
        }
    }

    //filling graph's matrix
    std::string curr_task;
    std::getline(std::cin, curr_task);
    for (int i = 0; i < num_of_tasks; i++) {
        int curr_i;
        std::getline(std::cin, curr_task);
        std::istringstream curr(curr_task);
        while (curr >> curr_i) {
            if (curr_i == 0) {
                std::cout << 0;
                exit(0);
            }
            tasks[curr_i - 1][i] = 1;
        }
    }

    std::vector<int> visited;
    visited.assign(num_of_tasks, false);

    std::vector<int> time_out;
    time_out.assign(num_of_tasks, 0);
    int time = 0;

    for (int i = 0; i < num_of_tasks; i++) {
		if (!visited[i]) {
            dfs(i, tasks, visited, time_out, time);
        }
    }

    bool avaliable_to_do = true;

    for (int i = 0; i < num_of_tasks; i++) {
        for (int j = 0; j < num_of_tasks; j++) {
            if (time_out[i] > time_out[j] && tasks[j][i] == 1) {
                avaliable_to_do = false;
                std::cout << 0;
                break;
            }
        }
        if (!avaliable_to_do) break;
    }
    if (avaliable_to_do) {
        for (int i = num_of_tasks; i >= 0; i--) {
            for (int j = 0; j < num_of_tasks; j++) {
                if (time_out[j] == i) {
                    std::cout << j + 1 << " ";
                }
            }
        }
    }

    return 0;
}
