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
#include "CSVHeader.h"
#include "CSVRow.h"
#include "CSVFile.h"

namespace fs = std::filesystem;


class CSVParser
{
public:
    CSVParser(char delimiter)
            :  delimiter_(delimiter)
    {}

    CSVFile parse(const fs::path& filepath)
    {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file");
        }

        CSVFile csvFile(filepath);
        CSVHeader header;
        CSVRow row;
        bool isHeader = true;
        std::string line;

        while (std::getline(file, line)) {
            // Create a stringstream from the line to tokenize it
            std::stringstream ss(line);
            std::string::const_iterator it = line.begin();

            // Loop over the cells in the line
            while (it != line.end()) {
                CSVCell cell = findNextCell(it, line.end());
                if (isHeader) {
                    header.addCell(cell);
                } else {
                    row.addCell(cell);
                }
            }

            if (isHeader) {
                isHeader = false;
            } else {
                // Add the current row to the CSVFile object and create a new row object
                csvFile.addRow(row);
                row = CSVRow();
            }
        }

        csvFile.setHeader(header);

        return csvFile;
    }

protected:
    char delimiter_;

private:
    CSVCell findNextCell(std::string::const_iterator& it, const std::string::const_iterator& end) const {
        std::string cellValue;
        bool inQuotes = false;
        int quoteCount = 0;

        while (it != end) {
            char c = *it;
            ++it;

            if (c == '"') {
                if (!inQuotes) {
                    // If we encounter a quote outside of quotes, we've started a quoted field
                    inQuotes = true;
                } else {
                    // If we encounter a quote inside quotes, check if it's a triple quote
                    quoteCount++;
                    if (quoteCount == 3) {
                        cellValue += '"';
                        quoteCount = 0;
                    }
                }
            } else {
                // If we're inside quotes, add the character to the cell value
                if (inQuotes) {
                    cellValue += c;
                } else if (c == delimiter_) {
                    // If we encounter the separator outside of quotes, we've found the next cell
                    return CSVCell(cellValue);
                } else {
                    // If we encounter any other character outside of quotes, add it to the cell value
                    cellValue += c;
                }
                quoteCount = 0;
            }
        }

        // If we reach the end of the string, the last cell doesn't have a separator after it
        return CSVCell(cellValue);
    }
};

#endif //FXCSVPARSER_CSVPARSER_H
