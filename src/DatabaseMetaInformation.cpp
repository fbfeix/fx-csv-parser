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



#include "DatabaseMetaInformation.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>


void DatabaseMetaInformation::saveToJson(const std::string &filename) const {
    using boost::property_tree::ptree;

    ptree pt;
    for (const auto &[table_name, table_meta_info]: table_meta_info_map_) {
        pt.push_back(std::make_pair(table_name, table_meta_info.toPropertyTree()));
    }
    boost::property_tree::write_json(filename, pt);
}

void DatabaseMetaInformation::loadFromJson(const std::string &filename) {
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(filename, pt);

    for (const auto &table_entry: pt) {
        TableMetaInformation table_meta = TableMetaInformation::fromPropertyTree(table_entry.second);
        table_meta_info_map_[table_entry.first] = table_meta;
    }
}

void DatabaseMetaInformation::createRelationGraph(const std::string &filename) {

    struct Vertex {
        std::string name;
    };
    struct Edge {
        float similarity;
    };


    using TableGraph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, Vertex, Edge>;

    TableGraph relation_graph;

    // Add the tables as vertices in the graph
    std::map<std::string, TableGraph::vertex_descriptor> vertex_map;
    for (const auto &[table_name, table_meta_info]: this->getTableMetaInformationMap()) {
        vertex_map[table_name] = boost::add_vertex({table_name}, relation_graph);
    }


    // Add the foreign keys as edges in the graph
    for (const auto &[table_name, table_meta_info]: this->getTableMetaInformationMap()) {
        for (const auto &foreign_key: table_meta_info.getForeignKeys()) {
            for (const auto &[other_table_name, other_table_meta_info]: this->getTableMetaInformationMap()) {
                if (other_table_name != table_name) {
                    for (const auto &other_column_info: other_table_meta_info.getColumnInformation()) {
                        if (other_column_info.name == foreign_key.targetColumn) {
                            TableGraph::vertex_descriptor source = vertex_map[table_name];
                            TableGraph::vertex_descriptor target = vertex_map[other_table_name];
                            float weight = foreign_key.similarity;
                            boost::add_edge(source, target, {weight}, relation_graph);
                        }
                    }
                }
            }
        }
    }

    // Write the graph to a Graphviz DOT file
    std::ofstream ofs(filename);
    boost::write_graphviz(ofs, relation_graph, [&](auto &out, auto v) {
                              out << "[label=\"" << relation_graph[v].name << "\"]";
                          },
                          [&](auto &out, auto e) {
                              out << "[label=\"" << relation_graph[e].similarity << "\"]";
                          });
}

void DatabaseMetaInformation::calculateForeignKeys() {
    for (auto &[originTableName, originTableInfo]: this->table_meta_info_map_) {

        // go through all the columns of this table and try to find foreign keys
        for (const auto& originColInfo: originTableInfo.getColumnInformation()) {
            for (const auto &[targetTableName, targetTableInfo]: this->table_meta_info_map_) {
                std::cout << "mau";


                float distance = jaroWinklerDistance(originColInfo.name, targetTableName);
                if (distance > 0.85) {
                    //currently not supported; @todo add check for primary key or something like that
                    if (originTableName == targetTableName) {
                        continue;
                    }

                    // we got a matching between the origin and target tables
                    // create a new foreign key
                    TableMetaInformation::ReferenceInfo foreignKey;
                    foreignKey.targetColumn = this->findRequiredReferenceColumn(targetTableInfo, originColInfo);
                    foreignKey.targetTableName = targetTableName;
                    foreignKey.sourceColumn = originColInfo.name;
                    foreignKey.similarity = distance;

                    originTableInfo.addForeignKey(foreignKey);


                }

            }
        }
    }
}

std::string DatabaseMetaInformation::findRequiredReferenceColumn(const TableMetaInformation &tableMeta,
                                                                 const TableMetaInformation::ColumnInfo &originColInfo) const {


    for (const auto &info: tableMeta.getColumnInformation()) {
        if (info.name == "id") {
            return info.name;
        }


        if (info.name == originColInfo.name) {
            return info.name;
        }
    }


    throw std::runtime_error("Could not find required reference column");
}



