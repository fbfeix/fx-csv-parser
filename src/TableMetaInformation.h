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

class TableMetaInformation {
public:
    struct ColumnInfo {
        std::string name;
        float similarity;
    };

    TableMetaInformation(std::vector<ColumnInfo> column_info, std::string file_name) : column_info_(
            std::move(column_info)), file_name_(file_name) {}

    const std::vector<ColumnInfo> &getColumnInformation() const {
        return column_info_;
    }

    static TableMetaInformation calculateColumnNameSimilarities(const CSVHeader &header, const std::string &filename) {
        std::vector<TableMetaInformation::ColumnInfo> column_info;

        // Calculate the similarity score between each column name and the filename
        for (int i = 0; i < header.getNumCells(); i++) {
            std::string column_name = header.getCell(i).getValue();
            std::set<std::string> column_tokens = tokenize(column_name);
            float score;

            if (column_name == "id") {
                score = 0.99;
            } else {
                score = jaroWinklerDistance(filename, column_name);
            }
            column_info.emplace_back(TableMetaInformation::ColumnInfo{column_name, score});
        }


        return TableMetaInformation(column_info, filename);
    }

    friend std::ostream &operator<<(std::ostream &os, const TableMetaInformation &information) {
        os << "\n\n+ " << information.file_name_ << "\n";
        os << "+----------+----------+" << "\n";
        os << "|  Column  |  Value   |" << "\n";
        os << "+----------+----------+" << "\n";

        // Iterate over the map and print each row
        for (const ColumnInfo &inf: information.column_info_) {

            std::cout << "| " << std::setw(9) << std::left << inf.name << " |";
            std::cout << " " << inf.similarity << std::endl;
        }
    }

private:
    std::vector<ColumnInfo> column_info_;
    std::string file_name_;
};


#endif //FXCSVPARSER_TABLEMETAINFORMATION_H
