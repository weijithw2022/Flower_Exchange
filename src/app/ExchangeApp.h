#ifndef EXCHANGEAPP_H
#define EXCHANGEAPP_H

#include "IOrderReader.h"
#include "IIdGenerator.h"
#include "IReportWriter.h"
#include "FileCleanupService.h"
#include "OrderProcessor.h"
#include "ReportService.h"

class ExchangeApp
{
private:
    IOrderReader&       reader;
    OrderProcessor      processor;
    ReportService       reportService;
    FileCleanupService  cleanupService;

public:
    ExchangeApp(IOrderReader&  reader,
                IIdGenerator&  idGenerator,
                IReportWriter& reportWriter,
                IReportWriter& rejectedWriter)
        : reader(reader),
          processor(idGenerator),
          reportService(reportWriter, rejectedWriter) {}

    void run(const std::string& inputFile)
    {
        cleanupService.cleanup("output");

        auto orders = reader.read(inputFile);
        processor.process(orders);

        reportService.writeRejected(processor.getRejectedReports());
        reportService.writeValid(processor.getExecutionReports());
        processor.displayOrderBooks();
    }
};

#endif