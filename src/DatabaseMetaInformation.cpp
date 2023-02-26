//
// Created by felix on 26.02.23.
//

#include "DatabaseMetaInformation.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>


void DatabaseMetaInformation::saveToJson(const std::string &filename) const {
    using boost::property_tree::ptree;
    ptree pt;
    for (const auto &[table_name, table_meta_info]: table_meta_info_map_) {
        ptree table_pt;
        for (const auto &column_info: table_meta_info.getColumnInformation()) {
            ptree column_pt;
            column_pt.put("name", column_info.name);
            column_pt.put("similarity", column_info.similarity);
            table_pt.push_back(std::make_pair("", column_pt));
        }
        for (const auto &foreign_key: table_meta_info.getForeignKeys()) {
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
    for (const auto &[table_name, table_pt]: pt) {
        std::vector<TableMetaInformation::ColumnInfo> column_info;
        std::vector<TableMetaInformation::ColumnInfo> fkeys;
        for (const auto &[key, column_pt]: table_pt) {
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
                        if (other_column_info.name == foreign_key.name) {
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
