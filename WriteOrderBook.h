#ifndef WRITEORDERBOOK_H
#define WRITEORDERBOOK_H

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "InputOrder.h"
#include "GenerateCSV.h"
using namespace std;

class WriteOrderBook
{
public:
    static void write(vector<InputOrder> buyOrders, vector<InputOrder> sellOrders, const string& instrument)
    {
        GenerateCSV csv("order_book_" + instrument + ".csv");

        vector<string> headers = {"Seq", "OrderId", "Qty", "Price", "Price", "Qty", "OrderId", "Seq"};
        csv.setHeaders(headers);

        sort(buyOrders.begin(), buyOrders.end(), [](const InputOrder& a, const InputOrder& b) {
            if (a.getPrice() != b.getPrice()) return a.getPrice() > b.getPrice();
            return a.getPrioritySequence() < b.getPrioritySequence();
        });

        sort(sellOrders.begin(), sellOrders.end(), [](const InputOrder& a, const InputOrder& b) {
            if (a.getPrice() != b.getPrice()) return a.getPrice() < b.getPrice();
            return a.getPrioritySequence() < b.getPrioritySequence();
        });

        int maxRows = max(buyOrders.size(), sellOrders.size());

        for (int i = 0; i < maxRows; i++)
        {
            vector<string> row(8, "");

            if (i < (int)buyOrders.size())
            {
                row[0] = to_string(buyOrders[i].getPrioritySequence());
                row[1] = buyOrders[i].getClientOrderId();
                row[2] = to_string(buyOrders[i].getQuantity());
                row[3] = formatPrice(buyOrders[i].getPrice());
            }

            if (i < (int)sellOrders.size())
            {
                row[4] = formatPrice(sellOrders[i].getPrice());
                row[5] = to_string(sellOrders[i].getQuantity());
                row[6] = sellOrders[i].getClientOrderId();
                row[7] = to_string(sellOrders[i].getPrioritySequence());
            }

            csv.addRow(row);
        }

        csv.writeCSV();
    }

private:
    static string formatPrice(double price)
    {
        ostringstream oss;
        oss << fixed << setprecision(2) << price;
        return oss.str();
    }
};

#endif