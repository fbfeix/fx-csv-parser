// MIT License
//
// Copyright (c) 2023 Felix Astner
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


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
