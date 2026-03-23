#ifndef CSVREPORTWRITER_H
#define CSVREPORTWRITER_H

#include "IReportWriter.h"
#include "WriteExecutionReport.h"
#include "WriteRejectedReport.h"

class CsvReportWriter : public IReportWriter
{
public:
    void write(const std::vector<ExecutionReport>& reports,
               const std::string& filename) const override
    {
        WriteExecutionReport::write(reports, filename);
    }
};

// Rejected variant
class CsvRejectedReportWriter : public IReportWriter
{
public:
    void write(const std::vector<ExecutionReport>& reports,
               const std::string& filename) const override
    {
        WriteRejectedReport::write(reports, filename);
    }
};

#endif