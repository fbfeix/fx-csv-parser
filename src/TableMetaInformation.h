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
#include <boost/property_tree/ptree.hpp>


class DatabaseMetaInformation;

class TableMetaInformation {
public:




    struct ColumnInfo {
        std::string name;
        /**
         * Represents the similarity of the column with the given table name.
         * ID is an exception to this rule and is always 0.99
         */
        float similarity = 0.0f;


        boost::property_tree::ptree toPropertyTree() const {
            boost::property_tree::ptree pt;
            pt.put("name", name);
            pt.put("similarity", similarity);
            return pt;
        }
    };

    struct ReferenceInfo {
        std::string targetTableName;
        std::string targetColumn;
        std::string sourceColumn;
        float similarity;

        boost::property_tree::ptree toPropertyTree() const {
            boost::property_tree::ptree pt;
            pt.put("targetTableName", targetTableName);
            pt.put("targetColumn", targetColumn);
            pt.put("sourceColumn", sourceColumn);
            pt.put("similarity", similarity);
            return pt;
        }
    };

    TableMetaInformation(std::vector<ColumnInfo> column_info, std::string file_name);
    TableMetaInformation(std::vector<ColumnInfo> column_info, std::vector<ReferenceInfo> foreign_keys,
                         std::string filename);


    const std::vector<ColumnInfo> &getColumnInformation() const;

    const std::vector<ReferenceInfo>& getForeignKeys() const;

    void addForeignKey(const ReferenceInfo& foreign_key);

    static TableMetaInformation calculateColumnNameSimilarities(const CSVHeader &header, const std::string &filename);

    void calculateForeignKeys(TableMetaInformation& table_meta_info, const DatabaseMetaInformation& db_info);


    friend std::ostream &operator<<(std::ostream &os, const TableMetaInformation &information);


    void addColumnInfo(const ColumnInfo &column_info) {
        column_info_.push_back(column_info);
    }

    void addReferenceInfo(const ReferenceInfo &reference_info) {
        foreign_keys_.push_back(reference_info);
    }

    void setFileName(const std::string &file_name) {
        file_name_ = file_name;
    }


    boost::property_tree::ptree toPropertyTree() const {
        boost::property_tree::ptree pt;

        boost::property_tree::ptree column_info_pt;
        for (const auto &column : column_info_) {
            column_info_pt.push_back(std::make_pair("", column.toPropertyTree()));
        }
        pt.add_child("column_info", column_info_pt);

        boost::property_tree::ptree foreign_keys_pt;
        for (const auto &reference : foreign_keys_) {
            foreign_keys_pt.push_back(std::make_pair("", reference.toPropertyTree()));
        }
        pt.add_child("foreign_keys", foreign_keys_pt);

        pt.put("file_name", file_name_);
        return pt;
    }


    static TableMetaInformation fromPropertyTree(const boost::property_tree::ptree &pt) {
        TableMetaInformation table_meta;

        for (const auto &column_entry : pt.get_child("column_info")) {
            ColumnInfo column_info;
            column_info.name = column_entry.second.get<std::string>("name");
            column_info.similarity = column_entry.second.get<float>("similarity");
            table_meta.addColumnInfo(column_info);
        }

        for (const auto &reference_entry : pt.get_child("foreign_keys")) {
            ReferenceInfo reference_info;
            reference_info.targetTableName = reference_entry.second.get<std::string>("targetTableName");
            reference_info.targetColumn = reference_entry.second.get<std::string>("targetColumn");
            reference_info.sourceColumn = reference_entry.second.get<std::string>("sourceColumn");
            reference_info.similarity = reference_entry.second.get<float>("similarity");
            table_meta.addReferenceInfo(reference_info);
        }

        table_meta.setFileName(pt.get<std::string>("file_name"));

        return table_meta;
    }


    TableMetaInformation();

private:

    std::vector<ColumnInfo> column_info_;
    std::vector<ReferenceInfo> foreign_keys_;

    std::string file_name_;

};


#endif //FXCSVPARSER_TABLEMETAINFORMATION_H
