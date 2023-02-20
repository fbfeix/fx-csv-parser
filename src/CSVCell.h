//
// Created by felix on 20.02.23.
//

#ifndef FXCSVPARSER_CSVCELL_H
#define FXCSVPARSER_CSVCELL_H


#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

class CSVCell
{
public:
    CSVCell(const std::string& column_name, const std::string& value, size_t row_number)
            : column_name_(column_name), value_(value), row_number_(row_number)
    {}

    const std::string& get_column_name() const { return column_name_; }
    const std::string& get_value() const { return value_; }
    size_t get_row_number() const { return row_number_; }

private:
    std::string column_name_;
    std::string value_;
    size_t row_number_;
};


#endif //FXCSVPARSER_CSVCELL_H
