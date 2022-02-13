//
// Created by galqiwi on 13.02.2022.
//

#ifndef NONOGRAM_SOLVER_FIELD_H
#define NONOGRAM_SOLVER_FIELD_H

#include <vector>
#include <iostream>

#include "Rule.h"

enum CellState {
    EMPTY = 0,
    FULL = 1,
    UNKNOWN = -1
};

class Field {
public:
    Field() = default;

    Field(int w, int h, std::vector<Rule> horizontal_rules, std::vector<Rule> vertical_rules);

    [[nodiscard]] const auto& GetCells() const;

    [[nodiscard]] std::pair<int, int> GetSize() const;

    void Solve();
private:
    enum SampleDirection {
        Row,
        Column
    };
    std::vector<CellState> Sample(SampleDirection direction, int index);
    static std::vector<std::pair<int, CellState>> BruteforceRow(std::vector<CellState> row, const Rule& rule);
    static bool ValidateRow(const std::vector<CellState>& row, const Rule& rule);
    int w_{0}, h_{0};
    std::vector<Rule> horizontal_rules_;
    std::vector<Rule> vertical_rules_;
    std::vector<std::vector<CellState>> cells_;
};

std::istream& operator>>(std::istream& in, Field& field);
std::ostream& operator<<(std::ostream& out, const Field& field);
std::ostream& operator<<(std::ostream& out, const std::vector<CellState>& row);

#endif //NONOGRAM_SOLVER_FIELD_H
