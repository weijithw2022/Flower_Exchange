#ifndef REPORTSERVICE_H
#define REPORTSERVICE_H

#include <map>
#include <vector>
#include <string>
#include "ExecutionReport.h"
#include "IReportWriter.h"

class ReportService
{
private:
    IReportWriter& reportWriter;
    IReportWriter& rejectedWriter;

public:
    ReportService(IReportWriter& reportWriter, IReportWriter& rejectedWriter)
        : reportWriter(reportWriter), rejectedWriter(rejectedWriter) {}

    void writeValid(const std::map<std::string, std::vector<ExecutionReport>>& reports)
    {
        for (const auto& [inst, reps] : reports)
            reportWriter.write(reps, "output/execution_reps/execution_rep_" + inst + ".csv");
    }

    void writeRejected(const std::vector<ExecutionReport>& reports)
    {
        if (!reports.empty())
            rejectedWriter.write(reports, "output/rejected_execution_reps/rejected_execution_rep.csv");
    }
};

#endif