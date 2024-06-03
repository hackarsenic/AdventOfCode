#pragma once

#include <fstream>
#include <sstream>
#include <vector>

using std::string;

typedef std::pair<std::pair<int,int>, std::pair<int,int>> coord_pair;

coord_pair get_pipe_adj(char pipe) {
    switch (pipe) {
        // connecting north and south
        case '|' :
            return coord_pair {{0, -1}, {0, 1}};
        // connecting east and west
        case '-' :
            return coord_pair {{1, 0}, {-1 , 0}};
        // connecting north and east
        case 'L' :
            return coord_pair {{0, -1}, {1 , 0}};
        // connecting north and west
        case 'J' :
            return coord_pair {{0, -1}, {-1, 0}};
        // connecting south and west
        case '7' :
            return coord_pair {{0, 1}, {-1, 0}};
        // connecting south and east
        case 'F' :
            return coord_pair {{1, 0}, {0,1}};
        case '.' :
            return coord_pair {{0, 0}, {0,0}};
    }
}

std::pair<int,int> get_start_next(int s_x, int s_y, const std::vector<std::vector<char>> &data) {
    const std::vector<std::pair<int,int>> check_coords = { {-1,0}, {0,-1}, {1,0}, {0, 1}};
    for (const auto &p : check_coords) {
        int chk_x = s_x + p.first;
        int chk_y = s_y + p.second;
        if (chk_x >= 0 && chk_x < data[0].size() && chk_y >= 0 && chk_y < data.size()) {
            coord_pair chk_pipe = get_pipe_adj(data[chk_y][chk_x]);
            if ((chk_x + chk_pipe.first.first == s_x && chk_y + chk_pipe.first.second == s_y) ||
                (chk_x + chk_pipe.second.first == s_x && chk_y + chk_pipe.second.second == s_y))
                return {chk_x, chk_y};
        }
    }
}

void get_pipe_coords(std::pair<int, int> &cur_coord, std::pair<int, int> &next_coord, std::vector<std::pair<int,int>> &loop_coords, const std::vector<std::vector<char>> &data) {
    if (data[next_coord.second][next_coord.first] == 'S') {
        loop_coords.emplace_back(next_coord);
        return;
    }

    coord_pair next_pipe_p = get_pipe_adj(data[next_coord.second][next_coord.first]);
    if (next_pipe_p.first.first + next_coord.first == cur_coord.first &&
        next_pipe_p.first.second + next_coord.second == cur_coord.second) {
        cur_coord = next_coord;
        next_coord.first += next_pipe_p.second.first;
        next_coord.second += next_pipe_p.second.second;
        loop_coords.emplace_back(cur_coord);
    } else {
        cur_coord = next_coord;
        next_coord.first += next_pipe_p.first.first;
        next_coord.second += next_pipe_p.first.second;
        loop_coords.emplace_back(cur_coord);
    }

    get_pipe_coords(cur_coord, next_coord, loop_coords, data);
}

// shoelace formula
int get_area(const std::vector<std::pair<int,int>> &coords) {
    int area =coords[0].second * coords[coords.size() - 1].first - coords[0].first * coords[coords.size()-1].second;
    for (int i = 0; i < coords.size() - 1; ++i) {
        int a = coords[i].first * coords[i+1].second;
        int b = coords[i].second * coords[i+1].first;
        area += (a - b);
    }

    return std::abs(area/2);
}

// Pick's theorem
int get_inner_points_num(int area, int outer_points_num) {
    return area - outer_points_num/2 + 1;
}

int part_one(std::ifstream &ifs) {
    string line;
    std::vector<std::vector<char>> data;

    size_t find_S_x = 0, find_S_y = 0;
    std::pair<int, int> S_coords;
    while (std::getline(ifs, line)) {
        find_S_x = 0;
        std::istringstream iss(line);
        std::vector<char> v_line;

        char tmp;
        while (iss >> tmp) {
            v_line.push_back(tmp);
            if (tmp == 'S')
                S_coords = {find_S_x, find_S_y};
            ++find_S_x;
        }

        data.push_back(v_line);
        ++find_S_y;
    }

    std::pair<int, int> start_coord = get_start_next(S_coords.first, S_coords.second, data);
    std::vector<std::pair<int,int>> pipe_coords;
    get_pipe_coords(S_coords, start_coord, pipe_coords, data);


    return pipe_coords.size() / 2;
}

int part_two(std::ifstream &ifs) {
    string line;
    std::vector<std::vector<char>> data;

    size_t find_S_x = 0, find_S_y = 0;
    std::pair<int, int> S_coords;
    while (std::getline(ifs, line)) {
        find_S_x = 0;
        std::istringstream iss(line);
        std::vector<char> v_line;

        char tmp;
        while (iss >> tmp) {
            v_line.push_back(tmp);
            if (tmp == 'S')
                S_coords = {find_S_x, find_S_y};
            ++find_S_x;
        }

        data.push_back(v_line);
        ++find_S_y;
    }

    std::pair<int, int> start_coord = get_start_next(S_coords.first, S_coords.second, data);
    std::vector<std::pair<int,int>> pipe_coords;
    get_pipe_coords(S_coords, start_coord, pipe_coords, data);

    int area = get_area(pipe_coords);
    int res = get_inner_points_num(area, pipe_coords.size());

    return res;
}