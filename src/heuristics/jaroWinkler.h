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
