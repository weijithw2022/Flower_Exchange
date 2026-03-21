#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <filesystem>
#include "OrderBook.h"
#include "InputOrder.h"
#include "ReadInputOrderCSV.h"
#include "WriteExecutionReport.h"

using namespace std;

void cleanUpOldCSVFiles()
{
    try
    {
        for (const auto &entry : filesystem::directory_iterator("."))
        {
            string filename = entry.path().filename().string();
            if ((filename.find("execution_rep_") == 0 || filename.find("order_book_") == 0) &&
                filename.rfind(".csv") == filename.length() - 4)
            {
                filesystem::remove(entry.path());
                cout << "Deleted: " << filename << endl;
            }
        }
    }
    catch (const exception &e)
    {
        cerr << "Error during cleanup: " << e.what() << endl;
    }
}

int main()
{
    // cleanUpOldCSVFiles();
    vector<InputOrder> orders = ReadInputOrder::readCSV("order.csv");
    map<string, OrderBook> orderBooks;
    map<string, vector<ExecutionReport>> executionReports;

    for (const auto &order : orders)
    {
        const string &instrument = order.getInstrument();

        if (orderBooks.find(instrument) == orderBooks.end())
        {
            orderBooks.emplace(instrument, OrderBook(instrument));
        }
        vector<ExecutionReport> reports = orderBooks.at(instrument).addOrder(order);
        for (const auto &report : reports)
        {
            executionReports[instrument].push_back(report);
        }
    }

    for (auto &[inst, book] : orderBooks)
    {
        WriteExecutionReport::write(executionReports[inst], "execution_rep_" + inst + ".csv");
        book.displayOrderBook();
    }

    return 0;
}