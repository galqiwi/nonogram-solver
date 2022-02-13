//
// Created by galqiwi on 13.02.2022.
//

#ifndef NONOGRAM_SOLVER_RULE_H
#define NONOGRAM_SOLVER_RULE_H

#include <vector>
#include <iostream>

struct Rule {
    std::vector<int> lengths;
};

std::istream& operator>>(std::istream& in, Rule& rule);
std::ostream& operator<<(std::ostream& out, const Rule& rule);

#endif //NONOGRAM_SOLVER_RULE_H
