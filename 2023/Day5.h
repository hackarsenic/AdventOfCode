#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <cctype>
#include <climits>

using std::string;
using std::vector;

typedef vector<vector<vector<long>>> data_vector;

inline void skip_lines(std::ifstream &ifs, size_t skip_n) {
    string line;
    for (auto i = 0; i < skip_n; ++i) {
        std::getline(ifs, line);
    }
}

void process_source_to_dest(long &seed, const vector<vector<long>> &v_filter) {
    for(const auto &v : v_filter) {
        auto source = v[1];
        auto dest = v[0];
        auto range = v[2];
        auto shift = dest - source;

        if (seed >= source && seed <= source + range){
            seed += shift;
            break;
        }
    }
}

long part_one(std::ifstream &ifs) {
    string line;
    data_vector data(7);
    vector<long> seeds;
    std::getline(ifs, line);
    line = line.substr(line.find(':') + 1, line.size());
    std::istringstream iss(line);

    long tmp;
    while (iss >> tmp) {
        seeds.push_back(tmp);
    }

    skip_lines(ifs, 2);

    vector<vector<long>> v_stage;
    int state = 0;

    while (std::getline(ifs, line)) {
        vector<long> v_nums;
        iss.clear();
        if (!isdigit(line[0])) {
            data[state] = v_stage;
            v_stage.clear();
            ++state;
            skip_lines(ifs, 1);
            continue;
        }

        iss.str(line);
        while (iss >> tmp) {
            v_nums.push_back(tmp);
        }

        v_stage.push_back(v_nums);
    }
    data[state] = v_stage;

    long res = LONG_MAX;
    for (auto s : seeds) {
        for (const auto &stage : data) {
            process_source_to_dest(s, stage);
        }
        if (s < res)
            res = s;
    }

    return res;
}

void process_seed_range(std::set<std::pair<long, long>> &new_seed_range, const std::pair<long, long> &seed_range, const vector<vector<long>> &v_filter) {
    std::list<std::pair<long, long>> tmp (1, seed_range);
    auto it = tmp.begin();

    while (it != tmp.end()) {
        bool is_filtered = false;
        for (const auto &v : v_filter) {
            auto source = v[1];
            auto dest = v[0];
            auto range = v[2];
            auto shift = dest - source;
            auto filter_beg = source;
            auto filter_end = source + range - 1;

            if (std::max(it->first, filter_beg) <= std::min(it->second, filter_end)) {
                auto seed_beg = it->first;
                auto seed_end = it->second;

                auto shifted_seed_beg = std::max(seed_beg, filter_beg) + shift;
                auto shifted_seed_end = std::min(seed_end, filter_end) + shift;

                if (seed_beg >= filter_beg && seed_end > filter_end) {
                    new_seed_range.emplace(shifted_seed_beg, shifted_seed_end);
                    tmp.emplace_back(filter_end + 1, seed_end);
                } else if (seed_beg < filter_beg && seed_end <= filter_end) {
                    new_seed_range.emplace(shifted_seed_beg, shifted_seed_end);
                    tmp.emplace_back(seed_beg, filter_beg - 1);
                } else if (seed_beg < filter_beg && seed_end > filter_end) {
                    new_seed_range.emplace(shifted_seed_beg, shifted_seed_end);
                    tmp.emplace_back(seed_beg, filter_beg);
                    tmp.emplace_back(filter_end + 1, seed_end);
                } else if (seed_beg >= filter_beg && seed_end <= filter_end) {
                    new_seed_range.emplace(shifted_seed_beg, shifted_seed_end);
                }

                it = tmp.erase(it);
                is_filtered = true;
                break;
            }
        }
        if (!is_filtered)
            it++;
    }

    for (auto &p : tmp)
        new_seed_range.emplace(p);
}

long part_two(std::ifstream &ifs) {
    string line;
    data_vector data(7);
    std::set<std::pair<long, long>> seed_range;
    std::getline(ifs, line);
    line = line.substr(line.find(':') + 1, line.size());
    std::istringstream iss(line);

    long tmp;
    while (iss >> tmp) {
        std::pair<long, long> range;
        range.first = tmp;
        iss >> tmp;
        range.second = range.first + tmp - 1;
        seed_range.emplace(range);
    }

    skip_lines(ifs, 2);

    vector<vector<long>> v_stage;
    int state = 0;

    while (std::getline(ifs, line)) {
        vector<long> v_nums;
        iss.clear();
        if (!isdigit(line[0])) {
            data[state] = v_stage;
            v_stage.clear();
            ++state;
            skip_lines(ifs, 1);
            continue;
        }

        iss.str(line);
        while (iss >> tmp) {
            v_nums.push_back(tmp);
        }

        v_stage.push_back(v_nums);
    }

    data[state] = v_stage;

    for (const auto &stage : data) {
        std::set<std::pair<long, long>> tmp_ranges;

        for (auto &range : seed_range) {
            process_seed_range(tmp_ranges, range, stage);
        }
        seed_range = tmp_ranges;
    }

    return seed_range.begin()->first;
}