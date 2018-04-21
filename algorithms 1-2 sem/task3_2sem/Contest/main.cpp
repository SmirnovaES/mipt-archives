#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

void add_student(const std::vector<int>& points, std::map<std::string, std::pair<std::vector<int>, int>>& solved_tasks, const std::string& name, int task) {
    if (solved_tasks.find(name) != solved_tasks.end()) {
        auto curr_student = solved_tasks.find(name);
        curr_student->second.first.push_back(task);
        curr_student->second.second += points[task];
    } else {
        solved_tasks[name].first.push_back(task);
        solved_tasks[name].second = points[task];
    }
}

void print_students_info(const std::map<std::string, std::pair<std::vector<int>, int>>& solved_tasks, const std::string& name) {
    auto curr_student = solved_tasks.find(name);
    if (curr_student == solved_tasks.end()) {
        std::cout << "Error: there's no such student.\n";
    } else {
        std::cout << curr_student->second.first.size() << " " << curr_student->second.second << "\n";
    }
}

void studs_by_tasks(const std::map<std::string, std::pair<std::vector<int>, int>>& solved_tasks) {
    std::map<int, std::vector<std::string>> students_and_tasks;
    for (auto it : solved_tasks) {
        students_and_tasks[it.second.first.size()].push_back(it.first);
    }
    for (auto it : students_and_tasks) {
        std::sort(it.second.begin(), it.second.end());
    }
    for (auto it : students_and_tasks) {
        for (auto it2 : it.second) {
            std::cout << it2 << " " << it.first << "\n";
        }
    }
}

void studs_by_balls(const std::map<std::string, std::pair<std::vector<int>, int>>& solved_tasks) {
    std::map<int, std::vector<std::string>> students_and_sums;
    for (auto it : solved_tasks) {
        students_and_sums[it.second.second].push_back(it.first);
    }
    for (auto it : students_and_sums) {
        std::sort(it.second.begin(), it.second.end());
    }
    for (auto it : students_and_sums) {
        for (auto it2 : it.second) {
            std::cout << it2 << " " << it.first << "\n";
        }
    }
}

void studs_more_tasks(const std::map<std::string, std::pair<std::vector<int>, int>>& solved_tasks, int bound) {
    std::map<int, std::vector<std::string>> students_and_tasks;
    for (auto it : solved_tasks) {
        if (it.second.first.size() >= bound) {
            students_and_tasks[it.second.first.size()].push_back(it.first);
        }
    }
    for (auto it : students_and_tasks) {
        std::sort(it.second.begin(), it.second.end());
    }
    for (auto it : students_and_tasks) {
        for (auto it2 : it.second) {
            std::cout << it2 << " " << it.first << "\n";
        }
    }
}

void studs_more_balls(const std::map<std::string, std::pair<std::vector<int>, int>>& solved_tasks, int bound) {
    std::map<int, std::vector<std::string>> students_and_sums;
    for (auto it : solved_tasks) {
        if (it.second.second >= bound) {
            students_and_sums[it.second.second].push_back(it.first);
        }
    }
    for (auto it : students_and_sums) {
        std::sort(it.second.begin(), it.second.end());
    }
    for (auto it : students_and_sums) {
        for (auto it2 : it.second) {
            std::cout << it2 << " " << it.first << "\n";
        }
    }
}

void tasks_by_solutions(const std::map<std::string, std::pair<std::vector<int>, int>>& solved_tasks) {
    std::map<int, int> tasks;
    for (auto it : solved_tasks) {
        for (auto it2 : it.second.first) {
            tasks[it2]++;
        }
    }
    std::vector<std::pair<int, int>> tasks_copy;
    for (auto it : tasks) {
        tasks_copy.push_back({it.second, it.first});
    }
    std::sort(tasks_copy.begin(), tasks_copy.end());
    for (auto it : tasks_copy) {
        std::cout << it.second + 1 << " " << it.first << "\n";
    }
}

void get_data(std::vector<int>& points) {
    for (int i = 0; i < points.size(); i++) {
        std::cin >> points[i];
    }
}

void parse_command(const std::string& curr_command, const std::vector<int>& points, std::map<std::string, std::pair<std::vector<int>, int>>& solved_tasks, bool& exit_flag) {
    if (curr_command == "SOLVED") {
        std::string name;
        int task;
        std::cin >> name >> task;
        if (--task >= points.size() || task < 0) {
            std::cout << "Error: there are only " << points.size() << " tasks.\n";
        } else {
            add_student(points, solved_tasks, name, task);
        }
    } else if (curr_command == "STUD_STAT") {
        std::string name;
        std::cin >> name;
        print_students_info(solved_tasks, name);
    } else if (curr_command == "STUDS_BY_TASKS") {
        studs_by_tasks(solved_tasks);
    } else if (curr_command == "STUDS_BY_BALLS") {
        studs_by_balls(solved_tasks);
    } else if (curr_command == "STUDS_MORE_TASKS") {
        int bound;
        std::cin >> bound;
        studs_more_tasks(solved_tasks, bound);
    } else if (curr_command == "STUDS_MORE_BALLS") {
        int bound;
        std::cin >> bound;
        studs_more_balls(solved_tasks, bound);
    } else if (curr_command == "TASKS_BY_SOLUTIONS") {
        tasks_by_solutions(solved_tasks);
    } else if (curr_command == "EXIT") {
        exit_flag = true;
    } else {
        std::cout << "Error: there's no such command.\n";
    }
}

int main() {
    int num_of_tasks;
    std::cin >> num_of_tasks;
    std::vector<int> points(num_of_tasks);
    get_data(points);

    std::map<std::string, std::pair<std::vector<int>, int>> solved_tasks; //name of student and information about his solved tasks -- their indexes and quantity

    bool exit_flag = false;
    std::string curr_command;
    while(!exit_flag) {
        std::cin >> curr_command;
        parse_command(curr_command, points, solved_tasks, exit_flag);
    }
    return 0;
}
