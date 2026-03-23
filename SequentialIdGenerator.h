#ifndef SEQUENTIALIDGENERATOR_H
#define SEQUENTIALIDGENERATOR_H

#include "IIdGenerator.h"
#include "OrderIDGenerator.h"

class SequentialIdGenerator : public IIdGenerator
{
public:
    std::string generate() override
    {
        return OrderIDGenerator::generateOrderID();
    }
};

#endif