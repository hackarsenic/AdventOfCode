#pragma once

#include <vector>
#include <map>
#include <fstream>

using std::string;

int part_one(std::ifstream &ifs) {
    string line;
    std::vector<string> scheme;
    int sum = 0;

    const std::vector<std::pair<int, int>> check_cell = {{-1,0}, {1,0}, {0,-1}, {0,1},
                                                         {-1,-1}, {-1,1}, {1,-1}, {1,1}};

    while (std::getline(ifs, line)) {
        scheme.push_back(line);
    }

    bool reading_num = false;
    std::vector<string> all_s_nums;
    for (size_t v_i = 0; v_i < scheme.size(); ++v_i) {
        bool is_valid = false;
        string s_num;
        for (size_t s_i = 0; s_i < scheme[v_i].size(); ++s_i) {
            if ((static_cast<int>(scheme[v_i][s_i]) > 47 && static_cast<int>(scheme[v_i][s_i]) < 58)) {
                if (!reading_num) {
                    reading_num = true;
                }

                for (const auto &p : check_cell) {
                    int check_x = v_i + p.first;
                    int check_y = s_i + p.second;

                    if (check_x >= 0 && check_x < scheme.size() && check_y >= 0 && check_y < scheme[v_i].size()) {
                        if ((static_cast<int>(scheme[check_x][check_y]) < 48 || static_cast<int>(scheme[check_x][check_y]) > 57) && scheme[check_x][check_y] != '.') {
                            is_valid = true;
                        }
                    }
                }

                s_num.push_back(scheme[v_i][s_i]);
            } else if (reading_num) {
                if (is_valid)
                    all_s_nums.push_back(s_num);

                reading_num = false;
                s_num.clear();
                is_valid = false;
            }

            if (s_i == scheme[v_i].size()-1 && !s_num.empty() && is_valid) {
                all_s_nums.push_back(s_num);
                reading_num = false;
                s_num.clear();
                is_valid = false;
            }
        }
    }

    for (const auto &s : all_s_nums) {
        sum += stoi(s);
    }

    return sum;
}


int part_two(std::ifstream &ifs) {
    string line;
    std::vector<string> scheme;
    int sum = 0;

    const std::vector<std::pair<int, int>> check_cell = {{-1,0}, {1,0}, {0,-1}, {0,1},
                                                         {-1,-1}, {-1,1}, {1,-1}, {1,1}};

    while (std::getline(ifs, line)) {
        scheme.push_back(line);
    }

    bool reading_num = false;
    std::map<std::pair<int,int>, std::vector<string>> nums_coord;
    for (size_t v_i = 0; v_i < scheme.size(); ++v_i) {
        bool is_valid = false;
        std::pair<int,int> coord;

        string s_num;
        for (size_t s_i = 0; s_i < scheme[v_i].size(); ++s_i) {
            if ((static_cast<int>(scheme[v_i][s_i]) > 47 && static_cast<int>(scheme[v_i][s_i]) < 58)) {
                if (!reading_num) {
                    reading_num = true;
                }

                for (const auto &p : check_cell) {
                    int check_x = v_i + p.first;
                    int check_y = s_i + p.second;

                    if (check_x >= 0 && check_x < scheme.size() && check_y >= 0 && check_y < scheme[v_i].size()) {
                        if (scheme[check_x][check_y] == '*') {
                            is_valid = true;
                            coord.first = check_x;
                            coord.second = check_y;
                        }
                    }
                }

                s_num.push_back(scheme[v_i][s_i]);
            } else if (reading_num) {
                if (is_valid)
                    nums_coord[coord].push_back(s_num);

                reading_num = false;
                s_num.clear();
                is_valid = false;
            }

            if (s_i == scheme[v_i].size()-1 && !s_num.empty() && is_valid) {
                nums_coord[coord].push_back(s_num);
                reading_num = false;
                s_num.clear();
                is_valid = false;
            }
        }
    }

    for (const auto &p : nums_coord) {
        if (p.second.size() > 1)
            sum += stoi(p.second[0]) * stoi(p.second[1]);
    }

    return sum;
}