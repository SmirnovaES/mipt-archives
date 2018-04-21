#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>

class Voter{
public:
    Voter(std::string new_telephone = 0): votes_left(1), status(false), telephone(new_telephone) {}


    std::string get_telephone() const{
        return telephone;
    }

    bool get_status() const {
        return status;
    }

    bool set_vip() {
        if (!status) {
            votes_left += 2;
            status = true;
            return true;
        } else return false;
    }

    bool voted() {
        if (votes_left - 1 >= 0) {
            votes_left--;
            return true;
        } else return false;
    }

private:
    std::string telephone;
    int votes_left;
    bool status;
};

void add_participant(std::map<std::string, int>& participants, const std::string& name) {
    if (participants.find(name) == participants.end()) {
        participants[name] = 0;
        std::cout << "OK\n";
    } else std::cout << "ALREADY REGISTED\n";
}

int get_voters_index(const std::vector<std::shared_ptr<Voter>>& voted, const std::string& telephone) {
    for (int i = 0; i < voted.size(); i++) {
        if ((*voted[i]).get_telephone() == telephone) return i;
    }
    return -1;
}

void set_vip(std::vector<std::shared_ptr<Voter>>& voted, const std::string& telephone) {
    int curr_person = get_voters_index(voted, telephone);
    if (curr_person != -1) {
        if ((*voted[curr_person]).get_status()) {
            std::cout << "ALREADY VIP\n";
        } else {
            (*voted[curr_person]).set_vip();
            std::cout << "OK\n";
        }
    } else {
        std::shared_ptr<Voter> new_voter = std::make_shared<Voter>(telephone);
        new_voter->set_vip();
        voted.push_back(new_voter);
        std::cout << "OK\n";
    }
}

void add_vote(std::map<std::string, int>& participants, std::vector<std::shared_ptr<Voter>>& voted, const std::string& name, const std::string& telephone) {
    if (participants.find(name) == participants.end()) {
        std::cout << "NOT REGISTERED\n";
        return;
    }
    int curr_person = get_voters_index(voted, telephone);
    if (curr_person == -1) {
        std::shared_ptr<Voter> new_voter = std::make_shared<Voter>(telephone);
        new_voter->voted();
        voted.push_back(new_voter);
        participants[name]++;
        std::cout << "VOTES FOR " << name << ": " << participants[name] << "\n";
        return;
    }
    if (voted[curr_person]->voted()) {
        participants[name]++;
        std::cout << participants[name] << "\n";
    } else std::cout << "NO MORE VOTES\n";
}

void delete_participant(std::map<std::string, int>& participants, const std::string& name) {
    auto curr_participant = participants.find(name);
    if (curr_participant == participants.end()) {
        std::cout << "NOT REGISTERED\n";
        return;
    }
    participants.erase(curr_participant);
    std::cout << "OK\n";
}

void get_the_best_ones(const std::map<std::string, int>& participants, int amount) {
    std::map<int, std::vector<std::string>> participants_by_points;
    for (auto it : participants) {
        participants_by_points[it.second].push_back(it.first);
    }
    for (auto it : participants_by_points) {
        std::sort(it.second.begin(), it.second.end());
    }
    for (auto it = participants_by_points.end(); it != participants_by_points.begin();) {
        it--;
        for (auto it2 : it->second) {
            if (amount > 0) {
                std::cout << it2 << " " << it->first << "\n";
                amount--;
            } else break;
        }
    }
}

void parse_command(const std::string& curr_command, std::map<std::string, int>& participants, std::vector<std::shared_ptr<Voter>>& voted, bool& exit_flag) {
    if (curr_command == "REGISTER") {
        std::string name;
        std::cin >> name;
        add_participant(participants, name);
    } else if (curr_command == "VIP") {
        std::string telephone;
        std::cin >> telephone;
        set_vip(voted, telephone);
    } else if (curr_command == "VOTE") {
        std::string name, telephone;
        std::cin >> name >> telephone;
        add_vote(participants, voted, name, telephone);
    } else if (curr_command == "KICK") {
        std::string name;
        std::cin >> name;
        delete_participant(participants, name);
    } else if (curr_command == "TOP") {
        int number;
        std::cin >> number;
        get_the_best_ones(participants, number);
    } else if (curr_command == "EXIT") {
        exit_flag = true;
    } else std::cout << "THERE IS NO SUCH COMMAND.\n";
}

int main() {
    std::map<std::string, int> participants;
    std::vector<std::shared_ptr<Voter>> voted;
    bool exit_flag = false;
    std::string curr_command;
    while (!exit_flag) {
        std::cin >> curr_command;
        parse_command(curr_command, participants, voted, exit_flag);
    }
    return 0;
}
