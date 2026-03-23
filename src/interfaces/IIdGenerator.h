#ifndef IIDGENERATOR_H
#define IIDGENERATOR_H

#include <string>

class IIdGenerator
{
public:
    virtual std::string generate() = 0;
    virtual ~IIdGenerator() = default;
};

#endif