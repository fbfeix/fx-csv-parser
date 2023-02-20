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

    CSVCell(std::string value) : value_(std::move(value)) {

    }

private:
    std::string value_;
};


#endif //FXCSVPARSER_CSVCELL_H
