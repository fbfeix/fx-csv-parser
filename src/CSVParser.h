//
// Created by felix on 20.02.23.
//

#ifndef FXCSVPARSER_CSVPARSER_H
#define FXCSVPARSER_CSVPARSER_H


#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "CSVCell.h"

namespace fs = std::filesystem;


class CSVParser
{
public:
    CSVParser(const fs::path& filepath, char delimiter)
            : filepath_(filepath), delimiter_(delimiter)
    {}

    std::vector<CSVCell> parse()
    {
        if (!fs::exists(filepath_))
        {
            throw std::runtime_error("File does not exist: " + filepath_.string());
        }

        if (!fs::is_regular_file(filepath_))
        {
            throw std::runtime_error("File is not a regular file: " + filepath_.string());
        }

        std::ifstream file(filepath_);

        if (!file)
        {
            throw std::runtime_error("Failed to open file: " + filepath_.string());
        }

        std::vector<std::string> column_names = read_column_names(file);
        std::vector<CSVCell> cells = read_cells(file, column_names);

        return cells;
    }

protected:
    fs::path filepath_;
    char delimiter_;

    std::vector<std::string> read_column_names(std::ifstream& file)
    {
        std::string line;

        if (std::getline(file, line))
        {
            std::stringstream ss(line);
            std::string column_name;
            std::vector<std::string> column_names;

            while (std::getline(ss, column_name, delimiter_))
            {
                column_names.push_back(column_name);
            }

            return column_names;
        }
        else
        {
            throw std::runtime_error("Failed to read column names");
        }
    }

    std::vector<CSVCell> read_cells(std::ifstream& file, const std::vector<std::string>& column_names)
    {
        std::vector<CSVCell> cells;
        std::string line;
        size_t row_number = 1;

        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            std::string cell_value;
            size_t column_number = 0;

            while (std::getline(ss, cell_value, delimiter_))
            {
                if (cell_value.size() > 0 && cell_value[0] == '"')
                {
                    std::string quoted_value = read_quoted_value(ss, cell_value);

                    cells.push_back(CSVCell(column_names[column_number], quoted_value, row_number));
                }
                else
                {
                    cells.push_back(CSVCell(column_names[column_number], cell_value, row_number));
                }

                column_number++;
            }

            row_number++;
        }

        return cells;
    }

    std::string read_quoted_value(std::stringstream& ss, std::string cell_value)
    {
        std::string quoted_value = cell_value.substr(1);
        bool found_closing_quote = false;

        while (std::getline(ss, cell_value, delimiter_))
        {
            quoted_value += delimiter_ + cell_value;

            if (cell_value.size() > 0 && cell_value.back() == '"')
            {
                quoted_value.pop_back();
                std::string::size_type pos = 0;

                while ((pos = quoted_value.find("\"\"", pos)) != std::string::npos)
                {
                    quoted_value.erase(pos, 1);
                }

                found_closing_quote = true;
                break;
            }
        }

        if (!found_closing_quote)
        {
            throw std::runtime_error("Missing closing quote in value: " + quoted_value);
        }

        return quoted_value;
    }
};

#endif //FXCSVPARSER_CSVPARSER_H
