//
// Created by felix on 20.02.23.
//

#include "CSVHeader.h"

void CSVHeader::addCell(CSVCell cell) {
    this->cells.push_back(cell);
}

int CSVHeader::getNumCells() const {
    return this->cells.size();
}

CSVCell CSVHeader::getCell(int i) const{
    return this->cells.at(i);
}
