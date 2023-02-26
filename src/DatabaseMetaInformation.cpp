//
// Created by felix on 26.02.23.
//

#include "DatabaseMetaInformation.h"

void DatabaseMetaInformation::saveToJson(const std::string &filename) const {
    using boost::property_tree::ptree;
    ptree pt;
    for (const auto& [table_name, table_meta_info] : table_meta_info_map_) {
        ptree table_pt;
        for (const auto& column_info : table_meta_info.getColumnInformation()) {
            ptree column_pt;
            column_pt.put("name", column_info.name);
            column_pt.put("similarity", column_info.similarity);
            table_pt.push_back(std::make_pair("", column_pt));
        }
        for (const auto& foreign_key : table_meta_info.getForeignKeys()) {
            ptree foreign_key_pt;
            foreign_key_pt.put("name", foreign_key.name);
            foreign_key_pt.put("similarity", foreign_key.similarity);
            table_pt.push_back(std::make_pair("foreign_key", foreign_key_pt));
        }
        pt.push_back(std::make_pair(table_name, table_pt));
    }
    boost::property_tree::write_json(filename, pt);
}

void DatabaseMetaInformation::loadFromJson(const std::string &filename) {
    using boost::property_tree::ptree;
    ptree pt;
    boost::property_tree::read_json(filename, pt);
    for (const auto& [table_name, table_pt] : pt) {
        std::vector<TableMetaInformation::ColumnInfo> column_info;
        std::vector<TableMetaInformation::ColumnInfo> fkeys;
        for (const auto& [key, column_pt] : table_pt) {
            if (key == "") {
                std::string column_name = column_pt.get<std::string>("name");
                float similarity = column_pt.get<float>("similarity");
                column_info.emplace_back(TableMetaInformation::ColumnInfo{column_name, similarity});
            } else if (key == "foreign_key") {
                std::string referenced_column_name = column_pt.get<std::string>("name");
                float similarity = column_pt.get<float>("similarity");
                fkeys.emplace_back(TableMetaInformation::ColumnInfo{referenced_column_name, similarity});
            }
        }
        TableMetaInformation table_meta_info(column_info, fkeys, table_name);

        addTableMetaInformation(table_name, std::move(table_meta_info));
    }
}
