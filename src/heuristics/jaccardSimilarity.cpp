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


#ifndef FXCSVPARSER_JACCARDSIMILARITY_H
#define FXCSVPARSER_JACCARDSIMILARITY_H


#include <string>
#include <sstream>
#include <set>
#include <algorithm>
#include "../CSVHeader.h"

// Returns a set of all the unique words in a given string, after removing common stopwords
std::set<std::string> tokenize(const std::string& s) {
    std::set<std::string> tokens;
    std::string token;
    std::istringstream ss(s);
    const std::set<std::string> stopwords = {"id", "name", "type", "value", "date", "time", "number", "quantity"};

    while (ss >> token) {
        // Remove common stopwords and punctuation from the token
        token.erase(std::remove_if(token.begin(), token.end(), ispunct), token.end());
        std::transform(token.begin(), token.end(), token.begin(), ::tolower);
        if (stopwords.find(token) == stopwords.end()) {
            tokens.insert(token);
        }
    }

    return tokens;
}

/*
 *  Calculates the Jaccard similarity coefficient between two sets of strings
 */
float calculateJaccardSimilarity(const std::set<std::string>& s1, const std::set<std::string>& s2) {
    std::set<std::string> intersection;
    std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), std::inserter(intersection, intersection.begin()));
    std::set<std::string> unionSet;
    std::set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), std::inserter(unionSet, unionSet.begin()));
    float similarity = (float) intersection.size() / (float) unionSet.size();
    return similarity;
}

// Returns a vector of pairs of column names and their similarity scores, sorted by the scores in descending order
std::vector<std::pair<std::string, float>> getSimilarityScores(const CSVHeader& header1, const CSVHeader& header2) {
    std::vector<std::pair<std::string, float>> scores;

    // Calculate the similarity score between each pair of column names in the two headers
    for (int i = 0; i < header1.getNumCells(); i++) {
        std::string name1 = header1.getCell(i).getValue();
        std::set<std::string> tokens1 = tokenize(name1);

        for (int j = 0; j < header2.getNumCells(); j++) {
            std::string name2 = header2.getCell(j).getValue();
            std::set<std::string> tokens2 = tokenize(name2);

            float score = calculateJaccardSimilarity(tokens1, tokens2);
            scores.emplace_back(name2, score);
        }
    }

    // Sort the scores in descending order
    std::sort(scores.begin(), scores.end(), [](const std::pair<std::string, float>& a, const std::pair<std::string, float>& b) {
        return a.second > b.second;
    });

    return scores;
}

#endif //FXCSVPARSER_JACCARDSIMILARITY_H
