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

#ifndef FXCSVPARSER_STRINGUTILS_H
#define FXCSVPARSER_STRINGUTILS_H

#include <iostream>
#include <regex>
#include <boost/lexical_cast.hpp>
//#include <boost/date_time.hpp>


std::string to_lower(const std::string &str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

enum StringType {
    Boolean,
    Uuid,
    Int,
    Double,
    String,
//    Date
};

StringType classifyString(const std::string& input) {
    // Check if the input is a boolean
    std::string lower = to_lower(input);
    if (lower == "true" || lower == "false") {
        return Boolean;
    }

    // Check if the input is a UUID
    std::regex uuidRegex(R"(^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}$)");
    if (std::regex_match(input, uuidRegex)) {
        return Uuid;
    }

    // Check if the input is a double
    try {
        boost::lexical_cast<double>(input);
        return Double;
    } catch (boost::bad_lexical_cast&) {
        // not a double, continue
    }

    // Check if the input is an integer
    try {
        boost::lexical_cast<int>(input);
        return Int;
    } catch (boost::bad_lexical_cast&) {
        // not an integer, continue
    }

    // Check if the input is a date
//    try {
//        std::locale loc(std::locale::classic(), new boost::gregorian::date_facet("%Y-%m-%d"));
//        boost::gregorian::date result = boost::lexical_cast<boost::gregorian::date>(input, loc);
//        return Date;
//    } catch (boost::bad_lexical_cast&) {
//        // not a date, continue
//    }

    // If none of the above conditions are met, classify the input as a string
    return String;
}

#endif //FXCSVPARSER_STRINGUTILS_H
