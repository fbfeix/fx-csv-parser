#include <iostream>
#include "src/CSVParser.h"
#include "src/CSVFolderParser.h"

int main() {
    std::filesystem::path path = "/home/felix/CLionProjects/FxCSVParser/examples/data/";
    path = absolute(path);
    CSVFolderParser parser(',');
    auto files = parser.parse(path);

    return 0;

}
