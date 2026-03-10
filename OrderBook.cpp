#include "OrderBook.h"
#include "OrderIDGenerator.h"
#include <iostream>
#include "GenerateCSV.h"

ExecutionReport OrderBook::addOrder(InputOrder order)
{
    string generatedOrderId = OrderIDGenerator::generateOrderID();

    if (order.getSide() == 1)
    {
        buyOrders.push_back(order);
        sort(buyOrders.begin(), buyOrders.end(), [](const InputOrder &a, const InputOrder &b) {
            return a.getPrice() > b.getPrice();
        });
    }
    else
    {
        sellOrders.push_back(order);
        sort(sellOrders.begin(), sellOrders.end(), [](const InputOrder &a, const InputOrder &b) {
            return a.getPrice() < b.getPrice();
        });
    }
    return ExecutionReport(
        generatedOrderId,
        order.getClientOrderId(),
        order.getInstrument(),
        order.getSide(),
        0,
        order.getQuantity(),
        order.getPrice());
} 


void OrderBook::displayOrderBook()
{
    GenerateCSV orderBookCSV("order_book_" + instrument + ".csv");
    vector<string> headers = {"OrderId", "Qty", "Price", "Price", "Qty", "OrderId"};
    orderBookCSV.setHeaders(headers);

    vector<InputOrder> sortedBuyOrders = buyOrders;
    sort(sortedBuyOrders.begin(), sortedBuyOrders.end(), [](const InputOrder &a, const InputOrder &b) {
        return a.getPrice() > b.getPrice();
    });

    vector<InputOrder> sortedSellOrders = sellOrders;
    sort(sortedSellOrders.begin(), sortedSellOrders.end(), [](const InputOrder &a, const InputOrder &b) {
        return a.getPrice() < b.getPrice();
    });

    int maxRows = max(sortedBuyOrders.size(), sortedSellOrders.size());

    for (int i = 0; i < maxRows; i++)
    {
        vector<string> row(6, ""); 

        // Left side: Buy orders 
        if (i < (int)sortedBuyOrders.size())
        {
            row[0] = sortedBuyOrders[i].getClientOrderId();   // Buy Order ID (left)
            row[1] = to_string(sortedBuyOrders[i].getQuantity()); // Buy Quantity
            row[2] = to_string(sortedBuyOrders[i].getPrice());  // Buy Price
        }
        
        if (i < (int)sortedSellOrders.size())
        {
            row[3] = to_string(sortedSellOrders[i].getPrice());  // Sell Price
            row[4] = to_string(sortedSellOrders[i].getQuantity()); // Sell Quantity
            row[5] = sortedSellOrders[i].getClientOrderId();   // Sell Order ID (right)
        }

        orderBookCSV.addRow(row);
    }
    orderBookCSV.writeCSV();
}