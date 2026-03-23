#ifndef IORDERREADER_H
#define IORDERREADER_H

#include <vector>
#include "InputOrder.h"

class IOrderReader
{
public:
    virtual std::vector<InputOrder> read(const std::string& filename) const = 0;
    virtual ~IOrderReader() = default;
};

#endif