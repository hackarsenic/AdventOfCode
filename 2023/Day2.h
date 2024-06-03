#pragma once

#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <cstdio>

using std::string;

void separator(const string &st_arg, char delim, std::vector<string> &items) {
    size_t sets_beg = 0;
    string set;
    for (size_t next_set = st_arg.find(delim, sets_beg); next_set != string::npos; next_set = st_arg.find(delim, next_set + 1)) {
        set = st_arg.substr(sets_beg, next_set - (sets_beg));
        sets_beg = next_set + 2;
        items.push_back(set);
    }

    set = st_arg.substr(sets_beg, st_arg.size());
    items.push_back(set);
}

int part_one(std::ifstream &ifs) {
    string line;
    int res = 0;

    while (std::getline(ifs, line)) {
        bool is_valid_set = true;
        std::map<string, int> col_nums = {{"red", 12}, {"green", 13}, {"blue", 14}};
        std::vector<string> sets;

        size_t sets_start_idx = line.find(':') + 2;
        int id;
        std::sscanf(line.substr(0, sets_start_idx).c_str(), "Game %d:", &id);
        string game_sets = line.substr(sets_start_idx, line.size() - 1);

        separator(game_sets, ';', sets);

        for (const auto &s : sets) {
            std::vector<string> items;

            separator(s, ',', items);
            for (const auto &i : items) {
                char color[5];
                int num;

                std::sscanf(i.c_str(), "%d %s", &num, color);

                if (col_nums[string(color)] < num) {
                    is_valid_set = false;
                    break;
                }
            }

        }
        if (is_valid_set)
            res += id;
    }

    return res;
}

int part_two(std::ifstream &ifs) {
    string line;
    int res = 0;

    while (std::getline(ifs, line)) {
        std::map<string, int> min_col_nums = {{"red", 0}, {"green", 0}, {"blue", 0}};
        std::vector<string> sets;

        size_t sets_start_idx = line.find(':') + 2;
        int id;
        std::sscanf(line.substr(0, sets_start_idx).c_str(), "Game %d:", &id);
        string game_sets = line.substr(sets_start_idx, line.size() - 1);

        separator(game_sets, ';', sets);

        for (const auto &s : sets) {
            std::vector<string> items;

            separator(s, ',', items);
            for (const auto &i : items) {
                char color[5];
                int num;

                std::sscanf(i.c_str(), "%d %s", &num, &color);

                if (min_col_nums[string(color)] < num) {
                    min_col_nums[string(color)] = num;
                }
            }
        }

        int pw_cols = 1;
        for (const auto &i : min_col_nums) {
            pw_cols *= i.second;
        }

        res += pw_cols;
    }

    return res;
}