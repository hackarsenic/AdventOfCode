#pragma once

#include <fstream>
#include <sstream>
#include <vector>

using std::string;
using std::vector;

int part_one(std::ifstream &ifs) {
    string line;
    vector<int> vec_time;
    vector<int> vec_distance;

    std::getline(ifs, line);
    line = line.substr(line.find(':') + 1);

    int tmp;
    std::istringstream iss(line);

    while (iss >> tmp)
        vec_time.push_back(tmp);

    std::getline(ifs, line);
    line = line.substr(line.find(':') + 1);

    iss.clear();
    iss.str(line);

    while (iss >> tmp)
        vec_distance.push_back(tmp);

    int res = 1;

    for (int i = 0; i < vec_time.size(); ++i) {
        int possible_races = 0;
        int hold_time = vec_time[i]/2;

        while ((vec_time[i] - hold_time) * hold_time > vec_distance[i]) {
            --hold_time;
            ++possible_races;
        }

        possible_races *= 2;
        if (vec_time[i]%2 == 0)
            possible_races -= 1;

        res *= possible_races;
    }

    return res;
}


int part_two(std::ifstream &ifs) {
    string line;
    string s_time;
    string s_distance;

    std::getline(ifs, line);
    line = line.substr(line.find(':') + 1);

    std::istringstream iss(line);

    string tmp;
    while (iss >> tmp)
        s_time.append(tmp);

    const long time = std::stol(s_time);

    std::getline(ifs, line);
    line = line.substr(line.find(':') + 1);

    iss.clear();
    iss.str(line);

    while (iss >> tmp)
        s_distance.append(tmp);

    const long distance = std::stol(s_distance);

    int possible_races = 0;
    int hold_time = time/2;

    while ((time - hold_time) * hold_time > distance) {
        --hold_time;
        ++possible_races;
    }

    possible_races *= 2;
    if (time%2 == 0)
        possible_races -= 1;

    return possible_races;
}