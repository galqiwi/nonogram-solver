#include <iostream>
#include <vector>
#include <unordered_map>
#include "Field.h"


int main() {
    Field field;
    std::cin >> field;
    field.Solve();
    std::cout << field << std::endl;
}