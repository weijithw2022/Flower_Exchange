#ifndef CSVORDERREADER_H
#define CSVORDERREADER_H

#include "IOrderReader.h"
#include "ReadInputOrderCSV.h"

class CsvOrderReader : public IOrderReader
{
public:
    std::vector<InputOrder> read(const std::string& filename) const override
    {
        return ReadInputOrder::readCSV(filename);
    }
};

#endif