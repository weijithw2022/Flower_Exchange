#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "OrderBook.h"
#include "InputOrder.h"
#include "ReadInputOrderCSV.h"
#include "WriteExecutionReport.h"

using namespace std;

int main()
{
    vector<InputOrder> orders = ReadInputOrder::readCSV("order.csv");
    map <string, OrderBook> orderBooks;
    map<string, vector<ExecutionReport>> executionReports;

    for (const auto& order : orders)
    {
        const string& instrument = order.getInstrument();

        if (orderBooks.find(instrument) == orderBooks.end())
        {
            orderBooks.emplace(instrument, OrderBook(instrument));
        }
        vector<ExecutionReport> reports = orderBooks.at(instrument).addOrder(order);
        for (const auto& report : reports)
        {
            executionReports[instrument].push_back(report);
        }
    }

    for (auto& [inst, book] : orderBooks)
    {
        WriteExecutionReport::write(executionReports[inst], "execution_rep_" + inst + ".csv");
        book.displayOrderBook(); 
    }

    return 0;
}