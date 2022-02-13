//
// Created by galqiwi on 13.02.2022.
//

#include "Rule.h"

std::istream& operator>>(std::istream& in, Rule& rule) {
    char sep = ' ';
    rule.lengths.clear();
    while (sep == ' ') {
        int new_length;
        in >> new_length;
        rule.lengths.push_back(new_length);

        in >> std::noskipws;
        in >> sep;
        in >> std::skipws;
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const Rule& rule) {
    out << "RULE: ";
    for (auto length: rule.lengths) {
        out << length << " ";
    }
    return out;
}