#ifndef WRITEEXECUTIONREPORT_H
#define WRITEEXECUTIONREPORT_H

#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include "ExecutionReport.h"
#include "GenerateCSV.h"
#include "Side.h"
#include "ExecStatus.h"
using namespace std;

class WriteExecutionReport
{
public:
    static void write(const vector<ExecutionReport> &reports, const string &filename = "execution_rep.csv", bool includeReason = false)
    {
        GenerateCSV csv(filename);

        vector<string> headers = {"Order ID", "Client Order ID", "Instrument", "Side", "Exec Status", "Quantity", "Price" , "Transaction Time" };
        if (includeReason)
        {
            headers.insert(headers.end() - 1, "Reason");
        }
        csv.setHeaders(headers);

        for (const auto &r : reports)
        {
            vector<string> row = {
                r.getOrderId(),
                r.getClientOrderId(),
                r.getInstrument(),
                sideToString(r.getSide()),
                statusToString(r.getStatus()),
                to_string(r.getQuantity()),
                formatPrice(r.getPrice()),
                r.getTransactionTime()
            };

            if (includeReason)
            {
                row.insert(row.end() - 1, r.getReason());
            }
            csv.addRow(row);
        }

        csv.writeCSV();
    }

private:
    static string statusToString(ExecStatus status)
    {
        switch (status)
        {
        case ExecStatus::New:
            return "New";
        case ExecStatus::Rejected:
            return "Rejected";
        case ExecStatus::Fill:
            return "Fill";
        case ExecStatus::PFill:
            return "Pfill";
        default:
            return "Unknown";
        }
    }

    static string sideToString(Side side)
    {
        switch (side)
        {
        case Side::Buy:
            return "1";
        case Side::Sell:
            return "2";
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