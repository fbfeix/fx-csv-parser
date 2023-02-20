//
// Created by felix on 20.02.23.
//

#ifndef FXCSVPARSER_CSVFILE_H
#define FXCSVPARSER_CSVFILE_H


#include "CSVRow.h"
#include "CSVHeader.h"

class CSVFile {

public:
    void addRow(CSVRow row);

    void setHeader(CSVHeader header);

private:
    std::vector<CSVRow> rows;
    CSVHeader header;
};


#endif //FXCSVPARSER_CSVFILE_H
