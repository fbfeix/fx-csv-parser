//
// Created by felix on 20.02.23.
//

#ifndef FXCSVPARSER_CSVROW_H
#define FXCSVPARSER_CSVROW_H


#include "CSVCell.h"

class CSVRow {

public:
    void addCell(CSVCell cell);

private:
    std::vector<CSVCell> cells;
};


#endif //FXCSVPARSER_CSVROW_H
