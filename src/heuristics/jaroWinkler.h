//
// Created by felix on 20.02.23.
//

#ifndef FXCSVPARSER_JAROWINKLER_H
#define FXCSVPARSER_JAROWINKLER_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

/**
 * The Jaro-Winkler distance is a string similarity metric that measures the similarity between two strings based on the
 * number of matching characters and the number of transpositions of those characters.
 * The Jaro-Winkler distance is a modification of the Jaro distance that gives more weight to matching prefixes of the
 * two strings. The prefix bonus is calculated based on the number of characters at the start of the strings that match.
 * The resulting Jaro-Winkler distance ranges from 0 (no similarity) to 1 (exact match), with higher values indicating
 * greater similarity.
 *
 * @param s1
 * @param s2
 * @param caseSensitive
 * @return
 */
float jaroWinklerDistance(std::string s1, std::string s2, bool caseSensitive = true);

#endif //FXCSVPARSER_JAROWINKLER_H
