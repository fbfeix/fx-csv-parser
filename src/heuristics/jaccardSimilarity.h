//
// Created by felix on 20.02.23.
//

#ifndef FXCSVPARSER_JACCARDSIMILARITY_H
#define FXCSVPARSER_JACCARDSIMILARITY_H


#include <string>
#include <sstream>
#include <set>
#include <algorithm>
#include "../CSVHeader.h"

// Returns a set of all the unique words in a given string, after removing common stopwords
std::set<std::string> tokenize(const std::string &s);

/*
 *  Calculates the Jaccard similarity coefficient between two sets of strings
 */
float calculateJaccardSimilarity(const std::set<std::string> &s1, const std::set<std::string> &s2);

// Returns a vector of pairs of column names and their similarity scores, sorted by the scores in descending order
std::vector<std::pair<std::string, float>> getSimilarityScores(const CSVHeader &header1, const CSVHeader &header2);

#endif //FXCSVPARSER_JACCARDSIMILARITY_H
