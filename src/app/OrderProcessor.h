#ifndef ORDERPROCESSOR_H
#define ORDERPROCESSOR_H

#include <map>
#include <vector>
#include <string>
#include "InputOrder.h"
#include "OrderBook.h"
#include "ExecutionReport.h"
#include "ExecutionReportFactory.h"
#include "OrderValidator.h"
#include "IIdGenerator.h"

class OrderProcessor
{
private:
    IIdGenerator& idGenerator;

    std::map<std::string, OrderBook>                    orderBooks;
    std::map<std::string, std::vector<ExecutionReport>> executionReports;
    std::vector<ExecutionReport>                        rejectedReports;

public:
    OrderProcessor(IIdGenerator& idGenerator)
        : idGenerator(idGenerator) {}

    void process(const std::vector<InputOrder>& orders)
    {
        for (const auto& order : orders)
        {
            std::string      orderId = idGenerator.generate();
            ValidationResult result  = OrderValidator::validate(order);

            if (!result.valid)
            {
                rejectedReports.push_back(
                    ExecutionReportFactory::rejected(orderId, order, result.message));
                continue;
            }

            const std::string& inst = order.getInstrument();
            if (orderBooks.find(inst) == orderBooks.end())
                orderBooks.emplace(inst, OrderBook(inst));

            auto reports = orderBooks.at(inst).addOrder(order, orderId);
            for (const auto& r : reports)
                executionReports[inst].push_back(r);
        }
    }

    void displayOrderBooks()
    {
        for (auto& [inst, book] : orderBooks)
            book.displayOrderBook();
    }

    const std::map<std::string, std::vector<ExecutionReport>>& getExecutionReports() const
    { return executionReports; }

    const std::vector<ExecutionReport>& getRejectedReports() const
    { return rejectedReports; }
};

#endif