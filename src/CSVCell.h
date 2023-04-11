//
// Created by felix on 20.02.23.
//

#ifndef FXCSVPARSER_CSVCELL_H
#define FXCSVPARSER_CSVCELL_H


#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace fs = std::filesystem;

class CSVCell {
public:

    explicit CSVCell(std::string value) : value(std::move(value)) {

    }

    [[nodiscard]] std::string getValue() const {
        return value;
    }
private:
    std::string value;
};


#endif //FXCSVPARSER_CSVCELL_H
