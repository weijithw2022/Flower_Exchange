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
        // sort(buyOrders.begin(), buyOrders.end(), [](const InputOrder &a, const InputOrder &b) {
        //     return a.getPrice() > b.getPrice();
        // });
    }
    else
    {
        sellOrders.push_back(order);
        // sort(sellOrders.begin(), sellOrders.end(), [](const InputOrder &a, const InputOrder &b) {
        //     return a.getPrice() < b.getPrice();
        // });
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
    // sort(sortedBuyOrders.begin(), sortedBuyOrders.end(), [](const InputOrder &a, const InputOrder &b)
    //      { return a.getPrice() > b.getPrice(); });

    vector<InputOrder> sortedSellOrders = sellOrders;
    // sort(sortedSellOrders.begin(), sortedSellOrders.end(), [](const InputOrder &a, const InputOrder &b)
    //      { return a.getPrice() < b.getPrice(); });

    int maxRows = max(sortedBuyOrders.size(), sortedSellOrders.size());

    for (int i = 0; i < maxRows; i++)
    {
        map<string, string> row;

        // Left side: Buy orders 
        if (i < sortedBuyOrders.size())
        {
            row["OrderId"] = sortedBuyOrders[i].getClientOrderId();   // Buy Order ID (left)
            row["Qty"] = to_string(sortedBuyOrders[i].getQuantity()); // Buy Quantity
            row["Price"] = to_string(sortedBuyOrders[i].getPrice());  // Buy Price
        }
        else
        {
            row["OrderId"] = ""; // Empty if no more buy orders
            row["Qty"] = "";
            row["Price"] = "";
        }
        
        if (i < sortedSellOrders.size())
        {
            // We need to map to the right-side headers
            // The headers are: {"OrderId", "Qty", "Price", "Price", "Qty", "OrderId"}
            // So indices 3, 4, 5 are for sell side
            row["Price"] = to_string(sortedSellOrders[i].getPrice());  // Sell Price
            row["Qty"] = to_string(sortedSellOrders[i].getQuantity()); // Sell Quantity
            row["OrderId"] = sortedSellOrders[i].getClientOrderId();   // Sell Order ID (right)
        }
        else
        {
            // Empty if no more sell orders
            row["Price"] = "";
            row["Qty"] = "";
            row["OrderId"] = "";
        }

        orderBookCSV.addRow(row);
    }

}