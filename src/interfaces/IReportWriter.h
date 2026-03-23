#ifndef IREPORTWRITER_H
#define IREPORTWRITER_H

#include <vector>
#include <string>
#include "ExecutionReport.h"

class IReportWriter
{
public:
    virtual void write(const std::vector<ExecutionReport>& reports,
                       const std::string& filename) const = 0;
    virtual ~IReportWriter() = default;
};

#endif