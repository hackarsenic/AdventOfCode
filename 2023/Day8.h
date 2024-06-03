#pragma once

#include <fstream>
#include <unordered_map>
#include <vector>

using std::string;

int part_one(std::ifstream &ifs) {
    int res = 0;
    string instr;
    std::getline(ifs, instr);

    string line;
    std::unordered_map<string, std::pair<string, string>> netw;

    // skip empty line
    std::getline(ifs, line);

    while (std::getline(ifs, line)) {
        const string key = line.substr(0, 3);
        const string left = line.substr(line.find('(') + 1, 3);
        const string right = line.substr(line.find(',') + 2, 3);

        netw.insert({key, std::pair<string, string> (left, right)});
    }

    string dest = netw.begin()->first;
    for (int i = 0; i <= instr.size(); ++i) {
        if (dest == "ZZZ")
            break;

        if (i == instr.size())
            i = 0;

        switch (instr[i]) {
            // L
            case 76 :
                dest = netw[dest].first;
                break;
            // R
            case 82 :
                dest = netw[dest].second;
                break;
        }

        ++res;
    }

    return res;
}

long long  gcd(const long long &a, const long long &b) {
    long long  res = (a > b) ? a : b;
    long long  num = (a > b) ? b : a;

    while (num != 0) {
        long long  rem = res % num;
        res = num;
        num = rem;
    }

    return res;
}

long long lcm(long long a, long long  b) {
    return (long long)(a * b) / gcd(a, b);
}

long long part_two(std::ifstream &ifs) {
    string instr;
    std::getline(ifs, instr);

    string line;
    std::unordered_map<string, std::pair<string, string>> netw;

    // skip empty line
    std::getline(ifs, line);

    std::vector<string> start_points;

    while (std::getline(ifs, line)) {
        const string key = line.substr(0, 3);
        const string left = line.substr(line.find('(') + 1, 3);
        const string right = line.substr(line.find(',') + 2, 3);

        if (key[2] == 'A')
            start_points.push_back(key);

        netw.insert({key, std::pair<string, string> (left, right)});
    }

    std::vector<int> all_cycles;

    for (auto &node : start_points) {
        int cycles = 0;

        for (int i = 0; i <= instr.size(); ++i) {
            if (node[2] == 'Z')
                break;
            if (i == instr.size())
                i = 0;

            switch (instr[i]) {
                // L
                case 76 :
                    node = netw[node].first;
                    break;
                // R
                case 82 :
                    node = netw[node].second;
                    break;
            }

            ++cycles;
        }

        all_cycles.push_back(cycles);
    }

    long long res = lcm(all_cycles[0], all_cycles[1]);

    if (all_cycles.size() > 2) {
        for (int i = 2; i < all_cycles.size(); ++i)
            res = lcm(res, all_cycles[i]);
    }

    return res;
}