#ifndef EXECUTIONREPORTFACTORY_H
#define EXECUTIONREPORTFACTORY_H

#include "ExecutionReport.h"
#include "InputOrder.h"

class ExecutionReportFactory
{
public:
    static ExecutionReport fill(const string& orderId, const InputOrder& order, int qty, double price)
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

    static ExecutionReport pfill(const string& orderId, const InputOrder& order, int qty, double price)
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

    static ExecutionReport newOrder(const string& orderId, const InputOrder& order)
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

    static ExecutionReport rejected(const string& orderId, const InputOrder& order, const string& reason)
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