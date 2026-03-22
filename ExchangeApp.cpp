#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <filesystem>
#include "OrderBook.h"
#include "InputOrder.h"
#include "OrderIDGenerator.h"
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
            if ((filename.find("execution_rep") == 0 || filename.find("order_book_") == 0 || filename.find("rejected_execution_rep") == 0) &&
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
    cleanUpOldCSVFiles();
    vector<InputOrder> orders = ReadInputOrder::readCSV("order.csv");
    map<string, OrderBook> orderBooks;
    map<string, vector<ExecutionReport>> executionReports;
    vector<ExecutionReport> rejectedReports;   

    for (const auto &order : orders)
    {
        string generatedOrderId = OrderIDGenerator::generateOrderID();
        auto [valid, errorMsg] = order.validate_order();
        if (!valid)
        {
            ExecutionReport rep(
                generatedOrderId,
                order.getClientOrderId(),
                order.getInstrument(),
                order.getSide(),
                //1,
                ExecStatus::Rejected,
                order.getQuantity(),
                order.getPrice(),
                errorMsg);
            
            rejectedReports.push_back(rep);
            continue;
        }
        const string &instrument = order.getInstrument();

        if (orderBooks.find(instrument) == orderBooks.end())
        {
            orderBooks.emplace(instrument, OrderBook(instrument));
        }
        vector<ExecutionReport> reports = orderBooks.at(instrument).addOrder(order, generatedOrderId);
        for (const auto &report : reports)
        {
            executionReports[instrument].push_back(report);
        }
    }

    if (!rejectedReports.empty())
        WriteExecutionReport::write(rejectedReports, "rejected_execution_rep.csv", true);
    
    for (auto &[inst, reports] : executionReports)
    {
        WriteExecutionReport::write(reports, "execution_rep_" + inst + ".csv", false);
    }

    for (auto &[inst, book] : orderBooks)
    {
        book.displayOrderBook();
    }

    return 0;
}