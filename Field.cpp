//
// Created by galqiwi on 13.02.2022.
//

#include <algorithm>
#include <unordered_map>
#include <cassert>

#include "Field.h"

Field::Field(int w, int h, std::vector<Rule> horizontal_rules, std::vector<Rule> vertical_rules):
        w_(w), h_(h), horizontal_rules_(std::move(horizontal_rules)), vertical_rules_(std::move(vertical_rules)),
        cells_(w, std::vector<CellState>(h, CellState::UNKNOWN)){
}

const auto &Field::GetCells() const {
    return cells_;
}

std::pair<int, int> Field::GetSize() const {
    return {w_, h_};
}

void Field::Solve() {
    bool done = false;

    while (!done) {
        done = true;

        for (int y = 0; y < h_; ++y) {
            auto row = Sample(Row, y);
            auto bruteforce_result = BruteforceRow(std::move(row), horizontal_rules_[y]);
            for (auto& [x, value]: bruteforce_result) {
                cells_[x][y] = value;
                done = false;
            }
        }

        for (int x = 0; x < w_; ++x) {
            auto row = Sample(Column, x);
            auto bruteforce_result = BruteforceRow(std::move(row), vertical_rules_[x]);
            for (auto& [y, value]: bruteforce_result) {
                cells_[x][y] = value;
                done = false;
            }
        }

    }
}

std::vector<CellState> Field::Sample(Field::SampleDirection direction, int index) {
    std::vector<CellState> output(direction == Column ? h_:w_);

    if (direction == Column) {
        output = cells_[index];
    } else {
        for (int x = 0; x < w_; ++x) {
            output[x] = cells_[x][index];
        }
    }

    return std::move(output);
}

std::vector<std::pair<int, CellState>> Field::BruteforceRow(std::vector<CellState> row, const Rule& rule) {
    int row_length = static_cast<int>(row.size());

    std::vector<int> unknown_indexes;
    int n_full_known_cells = 0;
    for (int i = 0; i < row_length; ++i) {
        if (row[i] == UNKNOWN) {
            unknown_indexes.push_back(i);
        }
        if (row[i] == FULL) {
            ++n_full_known_cells;
        }
    }

    int n_full_cells = 0;
    for (auto rule_length: rule.lengths) {
        n_full_cells += rule_length;
    }

    int n_cells_to_fill = n_full_cells - n_full_known_cells;
    int n_unknown_cells = static_cast<int>(unknown_indexes.size());

    std::vector<bool> permutation(n_unknown_cells, false);
    for (int i = n_unknown_cells - 1; i > n_unknown_cells - 1 - n_cells_to_fill; --i) {
        permutation[i] = true;
    }

    std::vector<bool> is_surely_full(n_unknown_cells, true);
    std::vector<bool> is_surely_empty(n_unknown_cells, true);

    do {
        for (int i = 0; i < n_unknown_cells; ++i) {
            row[unknown_indexes[i]] = permutation[i] ? FULL:EMPTY;
        }

        if (!ValidateRow(row, rule)) {
            continue;
        }

        for (int i = 0; i < n_unknown_cells; ++i) {
            is_surely_full[i] = is_surely_full[i] && permutation[i];
            is_surely_empty[i] = is_surely_empty[i] && (!permutation[i]);
        }
    } while (std::next_permutation(permutation.begin(), permutation.end()));

    std::vector<std::pair<int, CellState>> output;

    for (int i = 0; i < n_unknown_cells; ++i) {
        assert(!(is_surely_full[i] && is_surely_empty[i]));

        if (is_surely_full[i]) {
            output.emplace_back(unknown_indexes[i], FULL);
        }
        if (is_surely_empty[i]) {
            output.emplace_back(unknown_indexes[i], EMPTY);
        }
    }
    return std::move(output);
}

bool Field::ValidateRow(const std::vector<CellState> &row, const Rule &rule) {
    std::vector<int> lengths = {0};

    for (auto& cell: row) {
        assert(cell != UNKNOWN);
        if (cell == FULL) {
            ++lengths.back();
        } else {
            if (lengths.back() > 0) {
                lengths.push_back(0);
            }
        }
    }
    if (lengths.back() == 0) {
        lengths.pop_back();
    }

    return lengths == rule.lengths;
}


std::istream& operator>>(std::istream& in, Field& field) {
    int w, h;
    std::cin >> w >> h;

    std::vector<Rule> horizontal_rules(w);
    std::vector<Rule> vertical_rules(h);

    for (auto& rule: vertical_rules) {
        std::cin >> rule;
    }

    for (auto& rule: horizontal_rules) {
        std::cin >> rule;
    }

    field = Field(w, h, std::move(horizontal_rules), std::move(vertical_rules));

    return in;
}

char GetCharByCell(CellState cell) {
    const std::unordered_map<CellState, char> cell_chars ({
        {FULL, 'x'},
        {EMPTY, '.'},
        {UNKNOWN, '?'}
    });

    return cell_chars.at(cell);
}

std::ostream& operator<<(std::ostream& out, const Field& field) {
    auto& cells = field.GetCells();
    auto [w, h] = field.GetSize();



    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            std::cout << GetCharByCell(cells[x][y]);
        }
        if (y < h - 1) {
            std::cout << std::endl;
        }
    }

    return out;
}


std::ostream& operator<<(std::ostream& out, const std::vector<CellState>& row) {
    for (auto& cell: row) {
        std::cout << GetCharByCell(cell);
    }

    return out;
}