//
// Created by felix on 20.02.23.
//

#ifndef FXCSVPARSER_CSVFOLDERPARSER_H
#define FXCSVPARSER_CSVFOLDERPARSER_H


#include <string>
#include <map>
#include <iostream>
#include "CSVFile.h"
#include "CSVParser.h"

/**
 * Entry class for handling CSV files.
 */
class CSVFolderParser {
public:


    explicit CSVFolderParser(char delimiter) : delimiter(delimiter) {

    }


    /**
     * Looks into a folder and parses all its CSV files.
     *
     * @param folderPath
     * @return
     */
    [[nodiscard]] std::map<std::string, CSVFile> parse(const std::string &folderPath) const;

private:
    char delimiter;
    /**
     * The option if exceptions are allowed to happen during parsing a folder of files (If it should continue parsing).
     */
    bool allowFailedParsing = false;
};

#endif //FXCSVPARSER_CSVFOLDERPARSER_H
