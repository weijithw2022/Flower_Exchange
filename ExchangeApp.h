#ifndef EXCHANGEAPP_H
#define EXCHANGEAPP_H

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include <exception>
#include "IOrderReader.h"
#include "IIdGenerator.h"
#include "IReportWriter.h"
#include "OrderBook.h"
#include "ExecutionReport.h"
#include "OrderValidator.h"
#include "ValidationResult.h"
#include "ExecutionReportFactory.h"

class ExchangeApp
{
private:
    IOrderReader &reader;
    IIdGenerator &idGenerator;
    IReportWriter &reportWriter;
    IReportWriter &rejectedWriter;

    std::map<std::string, OrderBook> orderBooks;
    std::map<std::string, std::vector<ExecutionReport>> executionReports;
    std::vector<ExecutionReport> rejectedReports;

public:
    ExchangeApp(IOrderReader &reader,
                IIdGenerator &idGenerator,
                IReportWriter &reportWriter,
                IReportWriter &rejectedWriter)
        : reader(reader), idGenerator(idGenerator),
          reportWriter(reportWriter), rejectedWriter(rejectedWriter) {}

    void run(const std::string &inputFile)
    {
        cleanUpOldCSVFiles();
        auto orders = reader.read(inputFile);

        for (const auto &order : orders)
        {
            std::string orderId = idGenerator.generate();
            ValidationResult result = OrderValidator::validate(order);

            if (!result.valid)
            {
                rejectedReports.push_back(
                    ExecutionReportFactory::rejected(orderId, order, result.message));
                continue;
            }

            const std::string &inst = order.getInstrument();
            if (orderBooks.find(inst) == orderBooks.end())
                orderBooks.emplace(inst, OrderBook(inst));

            auto reports = orderBooks.at(inst).addOrder(order, orderId);
            for (const auto &r : reports)
                executionReports[inst].push_back(r);
        }

        writeReports();
        writeOrderBooks();
    }

private:
    void writeReports()
    {
        if (!rejectedReports.empty())
            rejectedWriter.write(rejectedReports, "rejected_execution_rep.csv");

        for (auto &[inst, reports] : executionReports)
            reportWriter.write(reports, "execution_rep_" + inst + ".csv");
    }

    void writeOrderBooks()
    {
        for (auto &[inst, book] : orderBooks)
            book.displayOrderBook();
    }

    void cleanUpOldCSVFiles()
    {
        try
        {
            for (const auto &entry : std::filesystem::directory_iterator("."))
            {
                std::string filename = entry.path().filename().string();
                if ((filename.find("execution_rep") == 0 ||
                     filename.find("order_book_") == 0 ||
                     filename.find("rejected_execution_rep") == 0) &&
                    filename.rfind(".csv") == filename.length() - 4)
                {
                    std::filesystem::remove(entry.path());
                }
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Cleanup error: " << e.what() << std::endl;
        }
    }
};

#endif