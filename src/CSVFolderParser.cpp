//
// Created by felix on 20.02.23.
//

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
