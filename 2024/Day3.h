#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;

long get_mul_res(const string &s, size_t &pos) {
    size_t mul_idx = s.find("mul(", pos);
    if (mul_idx == string::npos) {
        pos = string::npos;
        return 0;

    }

    size_t f_num_idx = mul_idx + 4;
    size_t comma_idx = s.find(',', f_num_idx);
    string f_s = s.substr(f_num_idx, comma_idx - f_num_idx);
    size_t s_num_idx = comma_idx + 1;
    string s_s = s.substr(s_num_idx, s.find(')', s_num_idx) - s_num_idx);
    pos = f_num_idx;

    if (std::all_of(f_s.begin(), f_s.end(), [](const int i) { return std::isdigit(i); }) &&
        std::all_of(s_s.begin(), s_s.end(), [](const int i) { return std::isdigit(i); }))
        return std::atoi(f_s.c_str()) * std::atoi(s_s.c_str());

    return 0;
}

long part_one(std::ifstream &ifs) {
    string line;

    long res = 0;
    while (std::getline(ifs, line)) {
        size_t pos = 0;
        while (pos != string::npos) {
            res += get_mul_res(line, pos);
        }
    }

    return res;
}

void find_dont(string &s, vector<std::pair<size_t, size_t>> &dont_vec) {
    size_t beg_idx = 0;
    size_t end_idx = 0;
    while (beg_idx != string::npos) {
        beg_idx = s.find("don't()", beg_idx);
        end_idx = s.find("do()", beg_idx);
        if (beg_idx != string::npos) {
            dont_vec.emplace_back(beg_idx, end_idx);
            beg_idx = end_idx;
        }
    }
}

long part_two(std::ifstream &ifs) {
    string line;

    long res = 0;
    string data;
    while (std::getline(ifs, line)) {
        data += line;
    }

    vector<std::pair<size_t, size_t>> dont_vec;
    find_dont(data, dont_vec);
    int i = 0;
    int cur_lim_l = dont_vec[0].first;
    int cur_lim_r = dont_vec[0].second;
    size_t pos = 0;
    while (pos != string::npos) {
        long val = get_mul_res(data, pos);

        if (i < dont_vec.size()) {
            cur_lim_l = dont_vec[i].first;
            cur_lim_r = dont_vec[i].second;
        } else {
            cur_lim_l = dont_vec[dont_vec.size() - 1].first;
            cur_lim_r = dont_vec[dont_vec.size() - 1].second;
        }

        if (pos > cur_lim_r) {
            ++i;
        }
        if (!(pos > cur_lim_l && pos < cur_lim_r)) {
            res += val;
        }
    }

    return res;
}