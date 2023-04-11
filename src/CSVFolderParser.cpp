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


#include "CSVFolderParser.h"

std::map<std::string, CSVFile> CSVFolderParser::parse(const std::string &folderPath) const {
    std::map<std::string, CSVFile> files;
    CSVParser parser(delimiter);

    try {
        // Open the folder and loop over its contents
        for (auto &entry: std::filesystem::directory_iterator(folderPath)) {
            // Check if the file is a CSV file
            if (entry.is_regular_file() && entry.path().extension() == ".csv") {
                try {
                    // Parse the CSV file and add it to the map of files with the filename as the key
                    CSVFile file = parser.parse(entry.path().string());
                    files.insert(std::make_pair(file.getName(), file));
                } catch (std::exception &e) {
                    // If parsing the file fails, print an error message and continue to the next file
                    std::cerr << "Failed to parse " << entry.path().string() << ": " << e.what() << std::endl;

                    if(!this->allowFailedParsing) {
                        throw e;
                    }
                }
            }
        }
    } catch (std::exception &e) {
        // If parsing the folder fails, print an error message
        std::cerr << "Failed to parse " << folderPath << ": " << e.what() << std::endl;
    }

    return files;
}
