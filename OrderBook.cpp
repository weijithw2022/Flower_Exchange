#include "OrderBook.h"
#include "OrderIDGenerator.h"
#include "WriteOrderBook.h"
#include "ExecutionReportFactory.h"
#include <iostream>
#include "GenerateCSV.h"

bool OrderBook::canMatch(const InputOrder &order)
{
    if (order.getSide() ==  Side::Buy)
    {
        return !sellOrders.empty() && order.getPrice() >= sellOrders.front().getPrice();
    }
    else
    {
        return !buyOrders.empty() && order.getPrice() <= buyOrders.front().getPrice();
    }
}

void OrderBook::insertIntoBuyBook(InputOrder& order, const string& orderId)
{
    order.setOrderId(orderId);
    buySeqCounter[order.getPrice()]++;
    order.setPrioritySequence(buySeqCounter[order.getPrice()]);

    buyOrders.push_back(order);
    sort(buyOrders.begin(), buyOrders.end(), [](const InputOrder& a, const InputOrder& b) {
        if (a.getPrice() != b.getPrice())
            return a.getPrice() > b.getPrice();       
        return a.getPrioritySequence() < b.getPrioritySequence();
    });
}

void OrderBook::insertIntoSellBook(InputOrder& order, const string& orderId)
{
    order.setOrderId(orderId);
    sellSeqCounter[order.getPrice()]++;
    order.setPrioritySequence(sellSeqCounter[order.getPrice()]);

    sellOrders.push_back(order);
    sort(sellOrders.begin(), sellOrders.end(), [](const InputOrder& a, const InputOrder& b) {
        if (a.getPrice() != b.getPrice())
            return a.getPrice() < b.getPrice();       
        return a.getPrioritySequence() < b.getPrioritySequence();
    });
}

void OrderBook::insertIntoBook(InputOrder& order, const string& orderId)
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

vector<ExecutionReport> OrderBook::addOrder(InputOrder order, const string& generatedOrderId)
{
    // string generatedOrderId = OrderIDGenerator::generateOrderID();

    vector<ExecutionReport> reports;
    int remainingQuantity = order.getQuantity();

    while (remainingQuantity > 0 && canMatch(order))
    {
        InputOrder &passive = (order.getSide() == Side::Buy) ? sellOrders.front() : buyOrders.front();
        double fillPrice = passive.getPrice();
        int passiveQuantity = passive.getQuantity();
        int fillQuantity = min(remainingQuantity, passiveQuantity);

        // Full fill
        if (remainingQuantity == passiveQuantity)
        {
            // reports.push_back(ExecutionReport(
            //     generatedOrderId,
            //     order.getClientOrderId(),
            //     order.getInstrument(),
            //     order.getSide(),
            //     ExecStatus::Fill,
            //     //order.getQuantity(), 
            //     fillQuantity,
            //     fillPrice));

            reports.push_back(ExecutionReportFactory::fill(
                generatedOrderId,
                order,
                fillQuantity,
                fillPrice
            ));

            // reports.push_back(ExecutionReport(
            //     passive.getOrderId(),
            //     passive.getClientOrderId(),
            //     passive.getInstrument(),
            //     passive.getSide(),
            //     ExecStatus::Fill,
            //     // passive.getQuantity(),
            //     fillQuantity,
            //     fillPrice));

            reports.push_back(ExecutionReportFactory::fill(
                passive.getOrderId(),
                passive,
                fillQuantity,
                fillPrice
            ));

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
        else if(remainingQuantity > passiveQuantity){
            // reports.push_back(ExecutionReport(
            //     generatedOrderId,
            //     order.getClientOrderId(),
            //     order.getInstrument(),
            //     order.getSide(),
            //     ExecStatus::PFill,
            //     fillQuantity,
            //     fillPrice));

            reports.push_back(ExecutionReportFactory::pfill(
                generatedOrderId,
                order,
                fillQuantity,
                fillPrice
            ));
            
            // reports.push_back(ExecutionReport(
            //     passive.getOrderId(),
            //     passive.getClientOrderId(),
            //     passive.getInstrument(),
            //     passive.getSide(),
            //     //2,
            //     ExecStatus::Fill,
            //     fillQuantity,
            //     fillPrice));

            reports.push_back(ExecutionReportFactory::fill(
                passive.getOrderId(),
                passive,
                fillQuantity,
                fillPrice
            ));
            
            if (order.getSide() == Side::Buy){
                removePassive(Side::Buy);
            }
            else{
                removePassive(Side::Sell);
            }

            remainingQuantity  -= fillQuantity;
            // order.setOrderId(generatedOrderId);
            order.setQuantity(remainingQuantity);

        }

        else{
            // reports.push_back(ExecutionReport(
            //     generatedOrderId,
            //     order.getClientOrderId(),
            //     order.getInstrument(),
            //     order.getSide(),
            //     // 2,
            //     ExecStatus::Fill,
            //     fillQuantity,
            //     fillPrice));

            reports.push_back(ExecutionReportFactory::fill(
                generatedOrderId,
                order,
                fillQuantity,
                fillPrice
            ));
            
            // reports.push_back(ExecutionReport(
            //     passive.getOrderId(),
            //     passive.getClientOrderId(),
            //     passive.getInstrument(),
            //     passive.getSide(),
            //     // 3,
            //     ExecStatus::PFill,
            //     fillQuantity,
            //     fillPrice));

            reports.push_back(ExecutionReportFactory::pfill(
                passive.getOrderId(),
                passive,
                fillQuantity,
                fillPrice
            ));
            
            passive.setQuantity(passiveQuantity - fillQuantity);\
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
        // reports.push_back(ExecutionReport(
        //     generatedOrderId,
        //     order.getClientOrderId(),
        //     order.getInstrument(),
        //     order.getSide(),
        //     //0,
        //     ExecStatus::New,
        //     order.getQuantity(),
        //     order.getPrice()));
        reports.push_back(ExecutionReportFactory::newOrder(
            generatedOrderId,
            order
        ));
    }
    return reports;
}

void OrderBook::displayOrderBook()
{
    WriteOrderBook::write(buyOrders, sellOrders, instrument);
}
// void OrderBook::displayOrderBook()
// {
//     GenerateCSV orderBookCSV("order_book_" + instrument + ".csv");
//     vector<string> headers = {"Seq", "OrderId", "Qty", "Price", "Price", "Qty", "OrderId", "Seq"};
//     orderBookCSV.setHeaders(headers);

//     vector<InputOrder> sortedBuyOrders = buyOrders;
//     sort(sortedBuyOrders.begin(), sortedBuyOrders.end(), [](const InputOrder &a, const InputOrder &b)
//          { return a.getPrice() > b.getPrice(); });

//     vector<InputOrder> sortedSellOrders = sellOrders;
//     sort(sortedSellOrders.begin(), sortedSellOrders.end(), [](const InputOrder &a, const InputOrder &b)
//          { return a.getPrice() < b.getPrice(); });

//     int maxRows = max(sortedBuyOrders.size(), sortedSellOrders.size());

//     for (int i = 0; i < maxRows; i++)
//     {
//         vector<string> row(8, "");

//         // Left side: Buy orders
//         if (i < (int)sortedBuyOrders.size())
//         {
//             row[0] = to_string(sortedBuyOrders[i].getPrioritySequence()); // Buy Order Priority Sequence
//             row[1] = sortedBuyOrders[i].getClientOrderId();               // Buy Order ID (left)
//             row[2] = to_string(sortedBuyOrders[i].getQuantity());         // Buy Quantity
//             row[3] = to_string(sortedBuyOrders[i].getPrice());            // Buy Price
//         }

//         if (i < (int)sortedSellOrders.size())
//         {
//             row[4] = to_string(sortedSellOrders[i].getPrice());            // Sell Price
//             row[5] = to_string(sortedSellOrders[i].getQuantity());         // Sell Quantity
//             row[6] = sortedSellOrders[i].getClientOrderId();               // Sell Order ID (right)
//             row[7] = to_string(sortedSellOrders[i].getPrioritySequence()); // Sell Order Priority Sequence
//         }

//         orderBookCSV.addRow(row);
//     }
//     orderBookCSV.writeCSV();
// }