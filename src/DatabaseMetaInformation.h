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
    DatabaseMetaInformation() = default;

    void addTableMetaInformation(const std::string &table_name, TableMetaInformation table_meta_info) {
        table_meta_info_map_.insert(std::make_pair(table_name, std::move(table_meta_info)));
    }

    [[nodiscard]] const TableMetaInformation *getTableMetaInformation(const std::string &table_name) const {
        auto it = table_meta_info_map_.find(table_name);
        if (it == table_meta_info_map_.end()) {
            return nullptr;
        } else {
            return &it->second;
        }
    }

    [[nodiscard]] const std::map<std::string, TableMetaInformation> &getTableMetaInformationMap() const {
        return table_meta_info_map_;
    }

    void saveToJson(const std::string &filename) const;

    void loadFromJson(const std::string &filename);

    void createRelationGraph(const std::string &filename);

    void calculateForeignKeys();



private:
    std::map<std::string, TableMetaInformation> table_meta_info_map_;

    std::string
    findRequiredReferenceColumn(const TableMetaInformation &tableMeta,
                                const TableMetaInformation::ColumnInfo &originColInfo) const;
};


#endif //FXCSVPARSER_DATABASEMETAINFORMATION_H
