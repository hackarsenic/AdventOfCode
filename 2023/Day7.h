#pragma once

#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <functional>
#include <algorithm>

using std::string;

// pair = 1;
// two pair = 2
// three = 3
// three + two = 4
// four = 5
// five = 6

void hand_grade_helper (int &hand_grade, const int &count) {
    switch (count) {
        case 2:
            hand_grade += 1;
            break;
        case 3:
            hand_grade += 3;
            break;
        case 4:
            hand_grade += 5;
            break;
        case 5:
            hand_grade += 6;
            break;
        default:
            break;
    }
}

int get_hand_grade_p1 (string hand) {
    std::sort(hand.begin(), hand.end());

    int hand_grade = 0;
    int count = 1;

    for (int i = 0; i < hand.size() - 1; ++i) {
        if (hand[i] == hand[i+1]) {
            ++count;
        } else {
            hand_grade_helper(hand_grade, count);
            count = 1;
        }
    }

    if (count > 1) {
        hand_grade_helper(hand_grade, count);
    }

    return hand_grade;
}

int part_one(std::ifstream &ifs) {
    string line;
    int res = 0;
    const std::unordered_map<char, int> card_values = { {'2', 1}, {'3', 2}, {'4', 3}, {'5', 4},
                                                        {'6', 5}, {'7', 6}, {'8', 7}, {'9', 8},
                                                        {'T', 9}, {'J', 10}, {'Q', 11}, {'K', 12},
                                                        {'A', 13} };

    std::function<bool (std::pair<string, int> &, std::pair<string, int> &)> comp_hands =
        [ &card_values ] (const std::pair<string, int> &h1, const std::pair<string, int> &h2) -> bool {
        int hand1_grade = get_hand_grade_p1(h1.first);
        int hand2_grade = get_hand_grade_p1(h2.first);

        if (hand1_grade > hand2_grade) {
            return true;
        } else if (hand1_grade < hand2_grade) {
            return false;
        } else {
            for (int i = 0; i < h1.first.size(); ++i) {
                if (card_values.at(h1.first[i]) > card_values.at(h2.first[i]))
                    return true;
                else if (card_values.at(h1.first[i]) < card_values.at(h2.first[i]))
                    return false;
            }
            return true;
        }
    };

    std::priority_queue<std::pair<string, int>, std::vector<std::pair<string, int>>, decltype(comp_hands)> rank_queue (comp_hands);

    while (std::getline(ifs, line)) {
        string hand;
        int bet;
        std::istringstream iss(line);

        iss >> hand;
        iss >> bet;

        rank_queue.emplace(std::pair<string, int>(hand, bet));
    }

    int rank = 1;
    while (!rank_queue.empty()) {
        res += rank_queue.top().second * rank;
        rank_queue.pop();
        ++rank;
    }

    return res;
}

// single = 0   ---- 1(J), 3(JJ), 5(JJJ), 6(JJJJ)
// pair = 1     ---- 3(J), 5(JJ), 6(JJJ)
// two pair = 2 ---- 4(J)
// three = 3    ---- 5(J), 6(JJ)
// three + two = 4
// four = 5     ---- 6(J)
// five = 6


void hand_upgrade_w_J (int &hand_grade, const int &j_count) {
    int new_hand_grade = 0;
    switch (hand_grade) {
        case 0:
            hand_grade_helper(new_hand_grade, j_count+1);
            break;
        case 1:
            hand_grade_helper(new_hand_grade, j_count+2);
            break;
        case 2:
            new_hand_grade = 4;
            break;
        case 3:
            hand_grade_helper(new_hand_grade, j_count+3);
            break;
        case 5:
            new_hand_grade = 6;
            break;
        default:
            break;
    }

    hand_grade = new_hand_grade;
}

int get_hand_grade_p2(string hand) {
    std::sort(hand.begin(), hand.end());

    int hand_grade = 0;
    int count = 1;
    int j_count = 0;

    for (int i = 0; i < hand.size() - 1; ++i) {
        if (hand[i] == 'J') {
            ++j_count;
            continue;
        }

        if (hand[i] == hand[i+1]) {
            ++count;
        } else {
            hand_grade_helper(hand_grade, count);
            count = 1;
        }
    }

    if (hand[hand.size() - 1] == 'J')
        ++j_count;

    if (count > 1)
        hand_grade_helper(hand_grade, count);


    if (j_count > 0) {
        if (j_count == 5)
            return 6;

        hand_upgrade_w_J(hand_grade, j_count);
    }

    return hand_grade;
}

int part_two(std::ifstream &ifs) {
    string line;
    int res = 0;
    const std::unordered_map<char, int> card_values = { {'J', 0}, {'2', 1}, {'3', 2}, {'4', 3},
                                                        {'5', 4}, {'6', 5}, {'7', 6}, {'8', 7},
                                                        {'9', 8}, {'T', 9},  {'Q', 11}, {'K', 12},
                                                        {'A', 13} };

    std::function<bool (std::pair<string, int> &, std::pair<string, int> &)> comp_hands =
        [ &card_values ] (const std::pair<string, int> &h1, const std::pair<string, int> &h2) -> bool {
            int hand1_grade = get_hand_grade_p2(h1.first);
            int hand2_grade = get_hand_grade_p2(h2.first);

            if (hand1_grade > hand2_grade) {
                return true;
            } else if (hand1_grade < hand2_grade) {
                return false;
            } else {
                for (int i = 0; i < h1.first.size(); ++i) {
                    if (card_values.at(h1.first[i]) > card_values.at(h2.first[i]))
                        return true;
                    else if (card_values.at(h1.first[i]) < card_values.at(h2.first[i]))
                        return false;
                }
                return true;
            }
        };

    std::priority_queue<std::pair<string, int>, std::vector<std::pair<string, int>>, decltype(comp_hands)> rank_queue (comp_hands);

    while (std::getline(ifs, line)) {
        string hand;
        int bet;
        std::istringstream iss(line);

        iss >> hand;
        iss >> bet;

        rank_queue.emplace(std::pair<string, int>(hand, bet));
    }

    int rank = 1;
    while (!rank_queue.empty()) {
        res += rank_queue.top().second * rank;
        rank_queue.pop();
        ++rank;
    }

    return res;
}