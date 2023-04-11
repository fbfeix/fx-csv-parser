//
// Created by felix on 26.02.23.
//

#include "TableMetaInformation.h"

#include <utility>
#include "DatabaseMetaInformation.h"


void TableMetaInformation::calculateForeignKeys(TableMetaInformation &table_meta_info,
                                                const DatabaseMetaInformation &db_info) {
    for (const auto &column_info: table_meta_info.getColumnInformation()) {
        // Check if the column name indicates a foreign key
        if (column_info.name.length() > 3 && column_info.name.substr(column_info.name.length() - 3) == "_id") {
            // Extract the name of the referenced column
            std::string referenced_column_name = column_info.name.substr(0, column_info.name.length() - 3);

            // Find the best match for the referenced column name in other tables
            float max_similarity = 0.0f;
            std::string best_match;
            for (const auto &[table_name, other_table_meta_info]: db_info.getTableMetaInformationMap()) {
                if (table_name != table_meta_info.file_name_) {
                    for (const auto &other_column_info: other_table_meta_info.getColumnInformation()) {
                        float similarity = jaroWinklerDistance(referenced_column_name, other_column_info.name);
                        if (similarity > max_similarity) {
                            max_similarity = similarity;
                            best_match = other_column_info.name;
                        }
                    }
                }
            }

            // Add the foreign key information to the table metadata
//            table_meta_info.addForeignKey(TableMetaInformation::ReferenceInfo{best_match, max_similarity});
        }
    }
}

std::ostream &operator<<(std::ostream &os, const TableMetaInformation &information) {
    os << "\n\n+ " << information.file_name_ << "\n";
    os << "+----------+----------+" << "\n";
    os << "|  Column  |  Value   |" << "\n";
    os << "+----------+----------+" << "\n";

    // Iterate over the map and print each row
    for (const TableMetaInformation::ColumnInfo &inf: information.column_info_) {

        std::cout << "| " << std::setw(9) << std::left << inf.name << " |";
        std::cout << " " << inf.similarity << std::endl;
    }
}

TableMetaInformation
TableMetaInformation::calculateColumnNameSimilarities(const CSVHeader &header, const std::string &filename) {
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

void TableMetaInformation::addForeignKey(const TableMetaInformation::ReferenceInfo &foreign_key) {
    foreign_keys_.push_back(foreign_key);
}

const std::vector<TableMetaInformation::ReferenceInfo> &TableMetaInformation::getForeignKeys() const {
    return foreign_keys_;
}

const std::vector<TableMetaInformation::ColumnInfo> &TableMetaInformation::getColumnInformation() const {
    return column_info_;
}

TableMetaInformation::TableMetaInformation(std::vector<ColumnInfo> column_info, std::string file_name) : column_info_(
        std::move(column_info)), file_name_(std::move(file_name)) {}

TableMetaInformation::TableMetaInformation(std::vector<ColumnInfo> column_info, std::vector<ReferenceInfo> foreign_keys,
                                           std::string filename)
        : column_info_(std::move(column_info)), foreign_keys_(std::move(foreign_keys)),
          file_name_(std::move(filename)) {

}

