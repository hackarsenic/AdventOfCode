#pragma once

#include <fstream>
#include <cstdio>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using std::string;

int part_one(std::ifstream &ifs) {
    string line;
    int sum = 0;

    while (std::getline(ifs, line)) {
        const size_t w_num_idx = line.find(':');
        const size_t c_num_idx = line.find('|');
        const string s_win_nums(line.substr(w_num_idx + 2, (c_num_idx - 2) - w_num_idx));
        const string s_cur_nums(line.substr(c_num_idx + 2));

        std::istringstream iss(s_win_nums);
        int temp_num;
        std::vector<int> win_nums;
        std::set<int> cur_nums;

        while (iss >> temp_num) {
            win_nums.push_back(temp_num);
        }

        iss.clear();
        iss.str(s_cur_nums);

        while (iss >> temp_num) {
            cur_nums.insert(temp_num);
        }

        int cur_points = 0;
        for (const auto &i : win_nums) {
            if (cur_nums.find(i) != cur_nums.end()) {
                if (!cur_points)
                    cur_points = 1;
                else
                    cur_points *= 2;
            }
        }

        sum += cur_points;
    }

    return sum;
}

int part_two(std::ifstream &ifs) {
    string line;
    int sum = 0;
    std::map<int, int> cards_num;

    while (std::getline(ifs, line)) {
        const size_t w_num_idx = line.find(':');
        const size_t c_num_idx = line.find('|');

        const int id = std::stoi(line.substr(4, w_num_idx - 4));
        cards_num[id] += 1;

        const string s_win_nums(line.substr(w_num_idx + 2, (c_num_idx - 2) - w_num_idx));
        const string s_cur_nums(line.substr(c_num_idx + 2));

        std::istringstream iss(s_win_nums);
        int temp_num;
        std::vector<int> win_nums;
        std::set<int> cur_nums;

        while (iss >> temp_num) {
            win_nums.push_back(temp_num);
        }

        iss.clear();
        iss.str(s_cur_nums);

        while (iss >> temp_num) {
            cur_nums.insert(temp_num);
        }

        int won_tickets = 0;
        for (const auto &i : win_nums) {
            if (cur_nums.find(i) != cur_nums.end()) {
                if (!won_tickets)
                    won_tickets = 1;
                else
                    won_tickets += 1;
            }
        }

        for (int i = 1; i <= won_tickets; ++i) {
            cards_num[id+i] += cards_num[id];
        }

        sum += cards_num[id];
    }

    return sum;
}