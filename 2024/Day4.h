#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <algorithm>

using std::string;
using std::vector;

int lookupXmas(const vector<string> &data, int x, int y) {
    string word = "XMAS";
    int found = 0;
    bool horis_plus = true;
    bool horis_minus = true;
    bool vert_plus = true;
    bool vert_minus = true;
    bool diag_lt_plus = true;
    bool diag_lt_minus = true;
    bool diag_rt_plus = true;
    bool diag_rt_minus = true;

    for (int i = 0; i < word.size(); ++i) {
        if (!(x + i < data[y].size() && data[y][x + i] == word[i])) {
            horis_plus = false;
        }
        if (!(x - i >= 0 && data[y][x - i] == word[i])) {
            horis_minus = false;
        }
        if (!(y + i < data.size() && data[y + i][x] == word[i])) {
            vert_plus = false;
        }
        if (!(y - i >= 0 && data[y - i][x] == word[i])) {
            vert_minus = false;
        }
        if (!(x + i < data[y].size() && y + i < data.size() && data[y + i][x + i] == word[i])) {
            diag_lt_plus = false;
        }
        if (!(x - i >= 0 && y - i >= 0 && data[y - i][x - i] == word[i])) {
            diag_lt_minus = false;
        }
        if (!(x + i < data[y].size() && y - i >= 0 && data[y - i][x + i] == word[i])) {
            diag_rt_plus = false;
        }
        if (!(x - i >= 0 && y + i < data.size() && data[y + i][x - i] == word[i])) {
            diag_rt_minus = false;
        }
    }

    found = horis_minus + horis_plus + vert_plus + vert_minus + diag_lt_plus + diag_lt_minus + diag_rt_plus + diag_rt_minus;

    return found;
}


int part_one(std::ifstream &ifs) {
    string line;
    vector<string> data;
    while (std::getline(ifs, line)) {
        data.push_back(line);
    }

    int res = 0;
    for (int i = 0; i < data.size(); ++i) {
        size_t x_itx = data[i].find('X');
        while (x_itx != string::npos) {
            res += lookupXmas(data, x_itx, i);
            x_itx = data[i].find('X', x_itx + 1);
        }
    }

    return res;
}

bool compare_data_pattern(const vector<string> &data, const vector<std::array<char, 3>> &pattern, int x, int y) {
    if (data[y-1][x-1] == pattern[0][0] && data[y-1][x+1] == pattern[0][2] && data[y+1][x-1] == pattern[2][0] &&
        data[y+1][x+1] == pattern[2][2])
        return true;
}

bool lookupCrossMAS(const vector<string> &data, int x, int y) {
    if (x < 1 || y < 1 || x >= data[0].size() || y > data.size())
        return false;

    vector<std::array<char, 3>> pattern = {
        {'M', '.', 'M'},
        {'.', 'A', ','},
        {'S', '.', 'S'}
    };

    if (compare_data_pattern(data, pattern, x, y))
        return true;

    std::swap(pattern[0][0], pattern[2][2]);
    if (compare_data_pattern(data, pattern, x, y))
        return true;

    std::swap(pattern[0][2], pattern[2][0]);
    if (compare_data_pattern(data, pattern, x, y))
        return true;

    std::swap(pattern[2][2], pattern[0][0]);
    return compare_data_pattern(data, pattern, x, y);
}

int part_two(std::ifstream &ifs) {
    string line;
    vector<string> data;
    while (std::getline(ifs, line)) {
        data.push_back(line);
    }

    int res = 0;
    for (int i = 1; i < data.size() - 1; ++i) {
        size_t x_itx = data[i].find('A', 1);
        while (x_itx != string::npos) {
            res += lookupCrossMAS(data, x_itx, i);
            x_itx = data[i].find('A', x_itx + 1);
        }
    }

    return res;
}