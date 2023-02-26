//
// Created by felix on 21.02.23.
//

#ifndef FXCSVPARSER_FOREIGNKEYHEURISTICS_H
#define FXCSVPARSER_FOREIGNKEYHEURISTICS_H


#include <map>
#include <string>

class ForeignKeyHeuristics {

private:
    std::map<std::string, std::map<std::string, float>> foreignKeyProbabilities;

};


#endif //FXCSVPARSER_FOREIGNKEYHEURISTICS_H
