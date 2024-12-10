#pragma once

#include <fstream>
#include <sstream>
#include <vector>

using std::string;
using std::vector;

long part_one(std::ifstream &ifs) {
    string line;

    int res = 0;
    while (std::getline(ifs, line)) {
        vector<int> data;
        std::istringstream iss(line);
        int tmp;
        while (iss >> tmp) {
            data.emplace_back(tmp);
        }

        int i = 1;
        while (i < data.size() && (data[i - 1] < data[i] && std::abs(data[i - 1] - data[i]) < 4)) {
            ++i;
        }

        if (i == data.size())
            ++res;

        i = 1;
        while (i < data.size() && (data[i - 1] > data[i] && std::abs(data[i - 1] - data[i]) < 4)) {
            ++i;
        }

        if (i == data.size())
            ++res;
    }

    return res;
}

std::pair<int,int> isOk(const vector<int> &data) {
    bool is_ok = false;

    int i = 0;

    for (; i < data.size() - 1; ++i) {
        if (!(data[i] < data[i + 1] && std::abs(data[i] - data[i + 1]) < 4)) {
            break;
        }
    }

    int asc_fail_idx = -1;
    int dsc_fail_idx = -1;

    if (i == data.size() - 1)
        is_ok = true;
    else {
        asc_fail_idx = i;
        i = 0;

        for (; i < data.size() - 1; ++i) {
            if (!(data[i] > data[i + 1] && std::abs(data[i] - data[i + 1]) < 4)) {
                break;
            }
        }

        if (i == data.size() - 1)
            is_ok = true;
        else
            dsc_fail_idx = i;
    }

    if (is_ok)
        return {-1, -1};
    else
        return {asc_fail_idx, dsc_fail_idx};
}

long part_two(std::ifstream &ifs) {
    string line;

    int res = 0;
    while (std::getline(ifs, line)) {
        vector<int> data;
        std::istringstream iss(line);
        int tmp;
        while (iss >> tmp) {
            data.emplace_back(tmp);
        }

        auto p = isOk(data);
        if (p.first == -1 && p.second == -1)
            ++res;
        else {
            vector<int> rm_idxs = {p.first, p.first + 1, p.second, p.second + 1};
            for (const auto i : rm_idxs) {
                vector<int> tmp_vec = data;
                tmp_vec.erase(tmp_vec.begin() + i);
                p = isOk(tmp_vec);
                if (p.first == -1 && p.second == -1) {
                    ++res;
                    break;
                }
            }
        }
    }

    return res;
}