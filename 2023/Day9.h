#pragma once

#include <fstream>
#include <sstream>
#include <vector>

using std::string;

long part_one(std::ifstream &ifs) {
    string line;
    std::vector<std::vector<int>> data;

    while (std::getline(ifs, line)) {
        std::istringstream iss(line);
        std::vector<int> v_line;

        int tmp;
        while (iss >> tmp) {
            v_line.push_back(tmp);
        }

        data.push_back(v_line);
    }

    long res = 0;
    for (const auto &v : data) {
        std::vector<int> last_num;
        std::vector<int> current_v = v;
        bool all_zero = false;
        while (!all_zero) {
            bool tmp_all_zero = true;
            std::vector<int> new_v;
            last_num.push_back(current_v[current_v.size() - 1]);
            for (auto i = 0; i < current_v.size() - 1; ++i) {
                int diff = current_v[i + 1] - current_v[i];
                new_v.push_back(diff);
                if (diff != 0)
                    tmp_all_zero = false;
            }

            current_v = new_v;

            if (tmp_all_zero)
                all_zero = true;
        }

        int last_num_i = 0;
        for (int i = last_num.size() - 1; i >= 0; --i) {
            last_num_i += last_num[i];
        }

        res += last_num_i;
    }

    return res;
}

long part_two(std::ifstream &ifs) {
    string line;
    std::vector<std::vector<int>> data;

    while (std::getline(ifs, line)) {
        std::istringstream iss(line);
        std::vector<int> v_line;

        int tmp;
        while (iss >> tmp) {
            v_line.push_back(tmp);
        }

        data.push_back(v_line);
    }


    long res = 0;
    for (const auto &v : data) {
        std::vector<int> first_num;
        std::vector<int> current_v = v;
        bool all_zero = false;
        while (!all_zero) {
            bool tmp_all_zero = true;
            std::vector<int> new_v;
            first_num.push_back(current_v[0]);
            for (auto i = 0; i < current_v.size() - 1; ++i) {
                int diff = current_v[i + 1] - current_v[i];
                new_v.push_back(diff);
                if (diff != 0)
                    tmp_all_zero = false;
            }

            current_v = new_v;

            if (tmp_all_zero)
                all_zero = true;
        }

        int first_num_i = 0;
        for (int i = first_num.size() - 1; i >= 0; --i) {
            first_num_i = first_num[i] - first_num_i;
        }

        res += first_num_i;
    }

    return res;
}