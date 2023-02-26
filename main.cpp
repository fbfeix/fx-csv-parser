#include <iostream>
#include <map>
#include <string>
#include <cmath>
#include <algorithm>
#include "src/CSVParser.h"
#include "src/CSVFolderParser.h"
#include "src/heuristics/jaccardSimilarity.h"
#include "src/heuristics/jaroWinkler.h"
#include "src/TableMetaInformation.h"
#include "src/DatabaseMetaInformation.h"

//std::map<std::string, float> calculateColumnNameSimilarities(const CSVHeader &header, const std::string &filename) {
//    std::map<std::string, float> columnScores;
//    float maxScore = 0.0f;
//
//    // Tokenize the filename
//    std::set<std::string> filenameTokens = tokenize(filename);
//
//    // Calculate the similarity score between each column name and the filename
//    for (int i = 0; i < header.getNumCells(); i++) {
//        std::string columnName = header.getCell(i).getValue();
//        std::set<std::string> columnTokens = tokenize(columnName);
//        float score;
//
//        if (columnName == "id") {
//            score = 0.99;
//        } else {
//            score = jaroWinklerDistance(filename, columnName);
//        }
//        columnScores.insert(std::make_pair(columnName, score));
//    }
//
//
//    return columnScores;
//}


std::map<std::string, std::set<std::string>>
buildGraph(std::map<std::string, std::map<std::string, float>> &file_Scores) {
    // Create a map to store the graph nodes and edges
    std::map<std::string, std::set<std::string>> graph;

    // Loop over each file and column name
    for (const auto &outgoingTable: file_Scores) {
        const std::string &filename = outgoingTable.first;
        const std::map<std::string, float> &outgoingTableScores = outgoingTable.second;

        // Loop over each column name and similarity score
        for (const auto &outgoingColumnPair: outgoingTableScores) {
            const std::string &outgoingColumnName = outgoingColumnPair.first;
            const float outgoingScore = outgoingColumnPair.second;


            for (const auto &incomingTable: file_Scores) {
                const std::string &incomingFilename = incomingTable.first;
                const std::map<std::string, float> &incomingTableScores = incomingTable.second;

                if (incomingFilename == filename) {
                    continue;
                }

                for (const auto &incomingColumnPair: incomingTableScores) {
                    const std::string &incomingColumnName = incomingColumnPair.first;
                    const float incomingScore = incomingColumnPair.second;

                    if (incomingFilename == "id") {
                        auto score = jaroWinklerDistance(incomingFilename, outgoingColumnName);

                        std::cout << "mau";

                    } else if (outgoingColumnName != incomingColumnName) {
                        continue;
                    }


                    if (incomingScore > 0.75) {
                        // add edge
                        graph[filename].insert(incomingFilename);
                    }
                }
            }
        }
    }

    // Print the graph for debugging
    for (const auto &node: graph) {
        std::cout << node.first << " -> ";
        for (const auto &edge: node.second) {
            std::cout << edge << " ";
        }
        std::cout << std::endl;
    }

    return graph;
}


int main() {
    std::filesystem::path path = "/home/felix/CLionProjects/FxCSVParser/examples/data/";
    path = absolute(path);
    CSVFolderParser parser(',');
    auto files = parser.parse(path);

    std::map<std::string, CSVHeader> map;
    std::map<std::string, std::map<std::string, float>> graphPrep;

    DatabaseMetaInformation dbInfo;

    for (const auto &item: files) {
        auto info = TableMetaInformation::calculateColumnNameSimilarities(item.second.getHeader(),
                                                                            item.second.getName());

        dbInfo.addTableMetaInformation(item.second.getName(), info);

        std::cout << info;


//        graphPrep.insert(std::make_pair(item.second.getName(), data));
    }


    dbInfo.saveToJson(path / ".fx-rel.json");
    dbInfo.createRelationGraph(path / "graph.dot");


    buildGraph(graphPrep);

    return 0;

}
