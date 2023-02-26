//
// Created by felix on 20.02.23.
//

#ifndef FXCSVPARSER_CSVHEADER_H
#define FXCSVPARSER_CSVHEADER_H


#include <map>
#include "CSVCell.h"

class CSVHeader {

public:
    void addCell(CSVCell cell);

    int getNumCells() const;

    CSVCell getCell(int i) const;

private:
    std::vector<CSVCell> cells;
};





#endif //FXCSVPARSER_CSVHEADER_H
