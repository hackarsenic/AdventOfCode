#pragma onece

#include <map>
#include <string>
#include <vector>
#include <fstream>

using std::string;

int part_one(std::ifstream &ifs) {
    string line;
    int sum = 0;

    while (std::getline(ifs, line)) {
        auto it_s = line.cbegin();
        auto it_e = line.crbegin();
        while ((static_cast<int>(*it_s) < 47 || static_cast<int>(*it_s) > 57) && it_s != line.end()) {
            ++it_s;
        }

        while ((static_cast<int>(*it_e) < 47 || static_cast<int>(*it_e) > 57) && it_e != line.rend()) {
            ++it_e;
        }

        char f = *it_s, s = *it_e;

        string num = {f, s};
        sum += stoi(num);
    }

    return sum;
}

int part_two(std::ifstream &ifs) {
    string line;
    int sum = 0;

    std::map<string, char> strtonums = {{"one", '1'}, {"two", '2'}, {"three", '3'}, {"four", '4'}, {"five", '5'},
                                   {"six", '6'}, {"seven", '7'}, {"eight", '8'}, {"nine",'9'}};


    while (std::getline(ifs, line)) {
        char c_f = '\0', c_s = '\0';
        size_t c_pos_s = 0, c_pos_e = line.size() - 1;
        auto it_s = line.cbegin();
        auto it_e = line.crbegin();
        while ((static_cast<int>(*it_s) < 47 || static_cast<int>(*it_s) > 58) && it_s != line.end()) {
            ++c_pos_s;
            ++it_s;
        }

        while ((static_cast<int>(*it_e) < 47 || static_cast<int>(*it_e) > 58) && it_e != line.rend()) {
            --c_pos_e;
            ++it_e;
        }

        size_t s_pos_s = line.size() - 1, s_pos_e = 0;
        char s_f = '\0', s_s = '\0';

        for (const auto &p : strtonums) {
            auto pos = line.find(p.first);
            auto r_pos = line.rfind(p.first);
            if (pos != string::npos) {
                if (pos < s_pos_s) {
                    s_pos_s = pos;
                    s_f = p.second;
                }
            }

            if (r_pos != string::npos) {
                if (r_pos > s_pos_e) {
                    s_pos_e = r_pos;
                    s_s = p.second;
                }
            }
        }

        if (it_s != line.end())
            c_f = *it_s;
        if (it_e != line.rend())
            c_s = *it_e;

        char f, s;
        if (c_f != '\0' && c_pos_s <= s_pos_s)
            f = c_f;
        else
            f = s_f;

        if (c_s != '\0' && c_pos_e >= s_pos_e)
            s = c_s;
        else
            s = s_s;


        string num = {f, s};
        sum += stoi(num);
    }

    return sum;
}
