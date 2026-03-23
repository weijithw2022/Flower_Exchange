#include "OrderBook.h"
#include "OrderIDGenerator.h"
#include "WriteOrderBook.h"
#include "ExecutionReportFactory.h"
#include <iostream>
#include "GenerateCSV.h"

bool OrderBook::canMatch(const InputOrder &order)
{
    if (order.getSide() == Side::Buy)
    {
        return !sellOrders.empty() && order.getPrice() >= sellOrders.front().getPrice();
    }
    else
    {
        return !buyOrders.empty() && order.getPrice() <= buyOrders.front().getPrice();
    }
}

void OrderBook::insertIntoBuyBook(InputOrder &order, const std::string &orderId)
{
    order.setOrderId(orderId);
    buySeqCounter[order.getPrice()]++;
    order.setPrioritySequence(buySeqCounter[order.getPrice()]);

    buyOrders.push_back(order);
    std::sort(buyOrders.begin(), buyOrders.end(), [](const InputOrder &a, const InputOrder &b)
              {
        if (a.getPrice() != b.getPrice())
            return a.getPrice() > b.getPrice();       
        return a.getPrioritySequence() < b.getPrioritySequence(); });
}

void OrderBook::insertIntoSellBook(InputOrder &order, const std::string &orderId)
{
    order.setOrderId(orderId);
    sellSeqCounter[order.getPrice()]++;
    order.setPrioritySequence(sellSeqCounter[order.getPrice()]);

    sellOrders.push_back(order);
    std::sort(sellOrders.begin(), sellOrders.end(), [](const InputOrder &a, const InputOrder &b)
              {
        if (a.getPrice() != b.getPrice())
            return a.getPrice() < b.getPrice();       
        return a.getPrioritySequence() < b.getPrioritySequence(); });
}

void OrderBook::insertIntoBook(InputOrder &order, const std::string &orderId)
{
    if (order.getSide() == Side::Buy)
        insertIntoBuyBook(order, orderId);
    else
        insertIntoSellBook(order, orderId);
}

void OrderBook::removePassive(Side aggressiveSide)
{
    if (aggressiveSide == Side::Buy)
        sellOrders.erase(sellOrders.begin());
    else
        buyOrders.erase(buyOrders.begin());
}

std::vector<ExecutionReport> OrderBook::addOrder(InputOrder order, const std::string &generatedOrderId)
{
    // string generatedOrderId = OrderIDGenerator::generateOrderID();

    std::vector<ExecutionReport> reports;
    int remainingQuantity = order.getQuantity();

    while (remainingQuantity > 0 && canMatch(order))
    {
        InputOrder &passive = (order.getSide() == Side::Buy) ? sellOrders.front() : buyOrders.front();
        double fillPrice = passive.getPrice();
        int passiveQuantity = passive.getQuantity();
        int fillQuantity = std::min(remainingQuantity, passiveQuantity);

        // Full fill
        if (remainingQuantity == passiveQuantity)
        {
            reports.push_back(ExecutionReportFactory::fill(
                generatedOrderId,
                order,
                fillQuantity,
                fillPrice));

            reports.push_back(ExecutionReportFactory::fill(
                passive.getOrderId(),
                passive,
                fillQuantity,
                fillPrice));

            if (order.getSide() == Side::Buy)
            {
                removePassive(Side::Buy);
            }
            else
            {
                removePassive(Side::Sell);
            }

            remainingQuantity = 0;
            // remainingQuantity -= fillQuantity;
        }

        // Partial fill -> aggressive order has remaining quantity
        else if (remainingQuantity > passiveQuantity)
        {

            reports.push_back(ExecutionReportFactory::pfill(
                generatedOrderId,
                order,
                fillQuantity,
                fillPrice));

            reports.push_back(ExecutionReportFactory::fill(
                passive.getOrderId(),
                passive,
                fillQuantity,
                fillPrice));

            if (order.getSide() == Side::Buy)
            {
                removePassive(Side::Buy);
            }
            else
            {
                removePassive(Side::Sell);
            }

            remainingQuantity -= fillQuantity;
            // order.setOrderId(generatedOrderId);
            order.setQuantity(remainingQuantity);
        }

        else
        {

            reports.push_back(ExecutionReportFactory::fill(
                generatedOrderId,
                order,
                fillQuantity,
                fillPrice));

            reports.push_back(ExecutionReportFactory::pfill(
                passive.getOrderId(),
                passive,
                fillQuantity,
                fillPrice));

            passive.setQuantity(passiveQuantity - fillQuantity);
            remainingQuantity = 0;
        }
    }

    if (remainingQuantity > 0)
    {
        order.setQuantity(remainingQuantity);
        insertIntoBook(order, generatedOrderId);
    }

    if (reports.empty())
    {
        reports.push_back(ExecutionReportFactory::newOrder(
            generatedOrderId,
            order));
    }
    return reports;
}

void OrderBook::displayOrderBook()
{
    WriteOrderBook::write(buyOrders, sellOrders, instrument);
}
