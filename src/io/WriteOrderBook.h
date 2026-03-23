#ifndef WRITEORDERBOOK_H
#define WRITEORDERBOOK_H

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "InputOrder.h"
#include "GenerateCSV.h"

class WriteOrderBook
{
public:
    static void write(std::vector<InputOrder> buyOrders, std::vector<InputOrder> sellOrders, const std::string& instrument)
    {
        GenerateCSV csv("output/order_books/order_book_" + instrument + ".csv");

        std::vector<std::string> headers = {"Seq", "OrderId", "Qty", "Price", "Price", "Qty", "OrderId", "Seq"};
        csv.setHeaders(headers);

        std::sort(buyOrders.begin(), buyOrders.end(), [](const InputOrder& a, const InputOrder& b) {
            if (a.getPrice() != b.getPrice()) return a.getPrice() > b.getPrice();
            return a.getPrioritySequence() < b.getPrioritySequence();
        });

        std::sort(sellOrders.begin(), sellOrders.end(), [](const InputOrder& a, const InputOrder& b) {
            if (a.getPrice() != b.getPrice()) return a.getPrice() < b.getPrice();
            return a.getPrioritySequence() < b.getPrioritySequence();
        });

        int maxRows = std::max(buyOrders.size(), sellOrders.size());

        for (int i = 0; i < maxRows; i++)
        {
            std::vector<std::string> row(8, "");

            if (i < (int)buyOrders.size())
            {
                row[0] = std::to_string(buyOrders[i].getPrioritySequence());
                row[1] = buyOrders[i].getClientOrderId();
                row[2] = std::to_string(buyOrders[i].getQuantity());
                row[3] = formatPrice(buyOrders[i].getPrice());
            }

            if (i < (int)sellOrders.size())
            {
                row[4] = formatPrice(sellOrders[i].getPrice());
                row[5] = std::to_string(sellOrders[i].getQuantity());
                row[6] = sellOrders[i].getClientOrderId();
                row[7] = std::to_string(sellOrders[i].getPrioritySequence());
            }

            csv.addRow(row);
        }

        csv.writeCSV();
    }

private:
    static std::string formatPrice(double price)
    {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << price;
        return oss.str();
    }
};

#endif