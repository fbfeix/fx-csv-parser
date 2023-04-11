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


        /**
         * Serialize the class as a boost property tree.
         * @return
         */
        [[nodiscard]] boost::property_tree::ptree toPropertyTree() const {
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
        /**
         * Represents the similarity of the source column name to the referenced column name.
         */
        float similarity;

        /**
         * Serialize the class as a boost property tree.
         * @return
         */
        [[nodiscard]] boost::property_tree::ptree toPropertyTree() const {
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


    [[nodiscard]] const std::vector<ColumnInfo> &getColumnInformation() const;

    [[nodiscard]] const std::vector<ReferenceInfo>& getForeignKeys() const;

    void addForeignKey(const ReferenceInfo& foreign_key);

    static TableMetaInformation calculateColumnNameSimilarities(const CSVHeader &header, const std::string &filename);


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


    [[nodiscard]] boost::property_tree::ptree toPropertyTree() const;


    static TableMetaInformation fromPropertyTree(const boost::property_tree::ptree &pt);


    TableMetaInformation();

private:

    std::vector<ColumnInfo> column_info_;
    std::vector<ReferenceInfo> foreign_keys_;

    std::string file_name_;

};


#endif //FXCSVPARSER_TABLEMETAINFORMATION_H
