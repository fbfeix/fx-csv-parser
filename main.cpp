#include <iostream>
#include "src/CSVParser.h"

int main() {
    std::filesystem::path path = "/home/felix/CLionProjects/FxCSVParser/examples/data/index.csv";
    path = absolute(path);
    CSVParser parser(path, ',');
    auto file = parser.parse();

    return 0;

}
