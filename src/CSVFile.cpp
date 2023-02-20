//
// Created by felix on 20.02.23.
//

#include "CSVFile.h"

void CSVFile::addRow(CSVRow row) {
    this->rows.push_back(row);

}

void CSVFile::setHeader(CSVHeader header) {
    this->header = header;
}

CSVFile::CSVFile(const std::filesystem::path &filename) : filename(filename) {}

std::string CSVFile::getName() const {
    return filename.stem().string();
}

const CSVHeader &CSVFile::getHeader() const {
    return header;
}
