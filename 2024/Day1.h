#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <functional>

using std::string;
using std::vector;

long part_one(std::ifstream &ifs) {
    string line;
    std::function<bool (int, int)> min_heap = [] (const int a, const int b) { return a > b; };
    std::priority_queue<int, vector<int>, decltype(min_heap)> col1(min_heap), col2(min_heap);

    while (std::getline(ifs, line)) {
        std::istringstream iss(line);
        int tmp;
        iss >> tmp;
        col1.emplace(tmp);
        iss >> tmp;
        col2.emplace(tmp);
    }

    int res = 0;

    while (!col1.empty()) {
        const int l = col1.top();
        const int r = col2.top();
        col1.pop();
        col2.pop();

        res += std::abs(l - r);
    }

    return res;
}

long part_two(std::ifstream &ifs) {
    string line;
    vector<int> col1;
    std::unordered_map<int, int> col2;

    while (std::getline(ifs, line)) {
        std::istringstream iss(line);
        int tmp;
        iss >> tmp;
        col1.emplace_back(tmp);
        iss >> tmp;
        col2[tmp] += 1;
    }

    int res = 0;

    for (const auto i : col1) {
        auto it = col2.find(i);
        if (it != col2.end()) {
            res += i * it->second;
        }
    }

    return res;

}