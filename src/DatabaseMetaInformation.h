//
// Created by felix on 26.02.23.
//

#ifndef FXCSVPARSER_DATABASEMETAINFORMATION_H
#define FXCSVPARSER_DATABASEMETAINFORMATION_H

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <map>
#include "TableMetaInformation.h"

class DatabaseMetaInformation {
public:
    DatabaseMetaInformation() {}

    void addTableMetaInformation(const std::string& table_name, TableMetaInformation table_meta_info) {
        table_meta_info_map_.insert(std::make_pair(table_name, std::move(table_meta_info)));
    }

    const TableMetaInformation* getTableMetaInformation(const std::string& table_name) const {
        auto it = table_meta_info_map_.find(table_name);
        if (it == table_meta_info_map_.end()) {
            return nullptr;
        } else {
            return &it->second;
        }
    }

    const std::map<std::string, TableMetaInformation>& getTableMetaInformationMap() const {
        return table_meta_info_map_;
    }

    void saveToJson(const std::string& filename) const;

    void loadFromJson(const std::string& filename);

private:
    std::map<std::string, TableMetaInformation> table_meta_info_map_;
};


#endif //FXCSVPARSER_DATABASEMETAINFORMATION_H
