#ifndef EXECUTIONREPORTFACTORY_H
#define EXECUTIONREPORTFACTORY_H

#include "ExecutionReport.h"
#include "InputOrder.h"

class ExecutionReportFactory
{
public:
    static ExecutionReport fill(const std::string &orderId, const InputOrder &order, int qty, double price)
    {
        return ExecutionReport(
            orderId,
            order.getClientOrderId(),
            order.getInstrument(),
            order.getSide(),
            ExecStatus::Fill,
            qty,
            price);
    }

    static ExecutionReport pfill(const std::string &orderId, const InputOrder &order, int qty, double price)
    {
        return ExecutionReport(
            orderId,
            order.getClientOrderId(),
            order.getInstrument(),
            order.getSide(),
            ExecStatus::PFill,
            qty,
            price);
    }

    static ExecutionReport newOrder(const std::string &orderId, const InputOrder &order)
    {
        return ExecutionReport(
            orderId,
            order.getClientOrderId(),
            order.getInstrument(),
            order.getSide(),
            ExecStatus::New,
            order.getQuantity(),
            order.getPrice());
    }

    static ExecutionReport rejected(const std::string &orderId, const InputOrder &order, const std::string &reason)
    {
        ExecutionReport rep(
            orderId,
            order.getClientOrderId(),
            order.getInstrument(),
            order.getSide(),
            ExecStatus::Rejected,
            order.getQuantity(),
            order.getPrice());
        rep.setReason(reason);
        return rep;
    }
};

#endif