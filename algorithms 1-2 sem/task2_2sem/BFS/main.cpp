#include <iostream>
#include <vector>
#include <sstream>

int main() {
    int num_of_types;
    int start, finish;
    int min_dist;

    std::cin >> num_of_types;
    std::cin >> start >> finish;
    start--;
    finish--;

    //initializing graph's matrix
    std::vector <std::vector <int>> types;
    for (int i = 0; i < num_of_types; i++) {
        std::vector<int> curr_vec;
        types.push_back(curr_vec);
        for (int j = 0; j < num_of_types; j++) {
            types[i].push_back(0);
        }
    }

    //filling graph's matrix
    std::string curr_task;
    std::getline(std::cin, curr_task);
    for (int i = 0; i < num_of_types; i++) {
        int curr_i;
        std::getline(std::cin, curr_task);
        std::istringstream curr(curr_task);
        while (curr >> curr_i) {
            types[i][--curr_i] = 1;
        }
    }

    //BFS
    std::vector<int> queue;
    queue.push_back(start);

    std::vector<int> distance;
    for (int i = 0; i < num_of_types; i++) {
        distance.push_back(-1);
    }
    distance[start] = 0;

    int curr_v;
    while (queue.size() != 0) {
        curr_v = queue[0];
        for (int i = 0; i < num_of_types; i++) {
            if (types[curr_v][i] == 1 && distance[i] == -1) {
                queue.push_back(i);
                distance[i] = distance[curr_v] + 1;
                if (i == finish) min_dist = distance[i];
            }
        }
        queue.erase(queue.begin());
    }


    //receiving answer
    std::vector<int> answer;
    answer.push_back(finish);
    int curr_end = finish;
    while(min_dist != 0) {
        for (int i = 0; i < num_of_types; i++) {
            if (distance[i] == min_dist - 1 && types[i][curr_end] == 1) {
                min_dist--;
                answer.insert(answer.begin(), i);
                curr_end = i;
            }
        }
    }

    //printing answer
    for(int i = 0; i < answer.size(); i++) {
        std::cout << answer[i] + 1 << " ";
    }

    return 0;
}
