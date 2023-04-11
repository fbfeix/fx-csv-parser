//
// Created by felix on 11.04.23.
//

#ifndef FXCSVPARSER_DATABASE_H
#define FXCSVPARSER_DATABASE_H

#include <filesystem>
#include <set>
#include "DatabaseMetaInformation.h"

namespace fs = std::filesystem;

/**
 * Represents a file or folder of CSV files.
 */
class Database {

public:
    void add(const fs::path &fileOrFolder);
    void remove(const fs::path &fileOrFolder);
    void clear();
    bool contains(const fs::path &fileOrFolder) const;

    static Database loadDatabase(const fs::path &fxRelFile);

    // @todo add an "execute(command)" function
protected:


    void generateDatabaseMetaInformation();

private:
    std::set<fs::path> files;
    DatabaseMetaInformation meta;
};


#endif //FXCSVPARSER_DATABASE_H
