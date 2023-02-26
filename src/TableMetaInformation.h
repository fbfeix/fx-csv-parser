//
// Created by felix on 26.02.23.
//

#ifndef FXCSVPARSER_TABLEMETAINFORMATION_H
#define FXCSVPARSER_TABLEMETAINFORMATION_H


#include <string>
#include <vector>
#include <set>
#include <ostream>
#include "CSVHeader.h"
#include "heuristics/jaroWinkler.h"
#include "heuristics/jaccardSimilarity.h"

class DatabaseMetaInformation;

class TableMetaInformation {
public:


    struct ColumnInfo {
        std::string name;
        float similarity;
    };

    TableMetaInformation(std::vector<ColumnInfo> column_info, std::string file_name);
    TableMetaInformation(std::vector<ColumnInfo> column_info, std::vector<ColumnInfo> foreign_keys,
                         std::string filename);


    const std::vector<ColumnInfo> &getColumnInformation() const;

    const std::vector<ColumnInfo>& getForeignKeys() const;

    void addForeignKey(const ColumnInfo& foreign_key);

    static TableMetaInformation calculateColumnNameSimilarities(const CSVHeader &header, const std::string &filename);

    void calculateForeignKeys(TableMetaInformation& table_meta_info, const DatabaseMetaInformation& db_info);


    friend std::ostream &operator<<(std::ostream &os, const TableMetaInformation &information);

private:
    std::vector<ColumnInfo> column_info_;
    std::vector<ColumnInfo> foreign_keys_;

    std::string file_name_;

};


#endif //FXCSVPARSER_TABLEMETAINFORMATION_H
