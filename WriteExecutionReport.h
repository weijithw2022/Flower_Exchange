#ifndef WRITEEXECUTIONREPORT_H
#define WRITEEXECUTIONREPORT_H

#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include "ExecutionReport.h"
#include "GenerateCSV.h"
using namespace std;

class WriteExecutionReport
{
public:
    static void write(const vector<ExecutionReport> &reports, const string &filename = "execution_rep.csv")
    {
        GenerateCSV csv(filename);

        vector<string> headers = {"Order ID", "Client Order ID", "Instrument", "Side", "Exec Status", "Quantity", "Price", "Reason", "Transaction Time" };
        csv.setHeaders(headers);

        for (const auto &r : reports)
        {
            vector<string> row = {
                r.getOrderId(),
                r.getClientOrderId(),
                r.getInstrument(),
                to_string(r.getSide()),
                statusToString(r.getStatus()),
                to_string(r.getQuantity()),
                formatPrice(r.getPrice()),
                r.getReason(),
                r.getTransactionTime()
            };
            csv.addRow(row);
        }

        csv.writeCSV();
    }

private:
    static string statusToString(int status)
    {
        switch (status)
        {
        case 0:
            return "New";
        case 1:
            return "Rejected";
        case 2:
            return "Fill";
        case 3:
            return "Pfill";
        default:
            return "Unknown";
        }
    }

    static string formatPrice(double price)
    {
        ostringstream oss;
        oss << fixed << setprecision(2) << price;
        return oss.str();
    }
};

#endif