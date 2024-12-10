#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>


using std::string;
using std::vector;

struct pair_hash {
    size_t operator()(const std::pair<int, int>& p) const {
        return std::hash<int>{}(p.first) ^ std::hash<int>{}(p.second);
    }
};

int part_one(std::ifstream &ifs) {
    string line;
    std::unordered_set<std::pair<int,int>, pair_hash> page_order;
    vector<vector<int>> updates;

    while (std::getline(ifs, line) && !line.empty()) {
        size_t sep_idx = line.find('|');
        int a = std::atoi(line.substr(0, sep_idx).c_str());
        int b = std::atoi(line.substr(sep_idx + 1, line.size() - (sep_idx + 1)).c_str());

        page_order.emplace(a, b);
    }

    while (std::getline(ifs, line)) {
        vector<int> tmp;

        size_t cur_comma_idx = line.find(',');
        tmp.emplace_back(std::atoi(line.substr(0, cur_comma_idx).c_str()));
        while (cur_comma_idx != string::npos) {
            size_t next_comma_idx = line.find(',', cur_comma_idx + 1);
            string num = line.substr(cur_comma_idx + 1, next_comma_idx - (cur_comma_idx + 1));
            tmp.emplace_back(std::atoi(num.c_str()));
            cur_comma_idx = next_comma_idx;
        }
        updates.emplace_back(std::move(tmp));
    }

    int res = 0;
    for (const auto &v : updates) {
        bool is_odered = true;
        for (int i = 1; i < v.size(); ++i) {
            if (page_order.find({v[i - 1], v[i]}) == page_order.end()) {
                is_odered = false;
                break;
            }
        }

        if (is_odered) {
            res += v[v.size() / 2];
        }
    }

    return res;
}


int part_two(std::ifstream &ifs) {
    string line;
    std::unordered_set<std::pair<int,int>, pair_hash> page_order;
    vector<vector<int>> updates;

    while (std::getline(ifs, line) && !line.empty()) {
        size_t sep_idx = line.find('|');
        int a = std::atoi(line.substr(0, sep_idx).c_str());
        int b = std::atoi(line.substr(sep_idx + 1, line.size() - (sep_idx + 1)).c_str());

        page_order.emplace(a, b);
    }

    while (std::getline(ifs, line)) {
        vector<int> tmp;

        size_t cur_comma_idx = line.find(',');
        tmp.emplace_back(std::atoi(line.substr(0, cur_comma_idx).c_str()));
        while (cur_comma_idx != string::npos) {
            size_t next_comma_idx = line.find(',', cur_comma_idx + 1);
            string num = line.substr(cur_comma_idx + 1, next_comma_idx - (cur_comma_idx + 1));
            tmp.emplace_back(std::atoi(num.c_str()));
            cur_comma_idx = next_comma_idx;
        }
        updates.emplace_back(std::move(tmp));
    }

    int res = 0;
    for (auto &v : updates) {
        bool is_odered = true;
        for (int i = 1; i < v.size(); ++i) {
            if (page_order.find({v[i - 1], v[i]}) == page_order.end()) {
                is_odered = false;
                break;
            }
        }

        if (!is_odered) {
            std::sort(v.begin(), v.end(), [&page_order](int a, int b) {
                return page_order.find({a, b}) != page_order.end();
            });

            res += v[v.size() / 2];
        }
    }

    return res;
}