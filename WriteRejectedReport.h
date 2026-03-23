#ifndef WRITEREJECTEDREPORT_H
#define WRITEREJECTEDREPORT_H

#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include "ExecutionReport.h"
#include "GenerateCSV.h"

class WriteRejectedReport
{
public:
    static void write(const std::vector<ExecutionReport> &reports, const std::string &filename = "rejected_execution_rep.csv")
    {
        GenerateCSV csv(filename);

        csv.setHeaders({"Order ID", "Client Order ID", "Instrument",
                        "Side", "Exec Status", "Quantity", "Price",
                        "Reason",
                        "Transaction Time"});

        for (const auto &r : reports)
        {
            csv.addRow({r.getOrderId(),
                        r.getClientOrderId(),
                        r.getInstrument(),
                        sideToString(r.getSide()),
                        statusToString(r.getStatus()),
                        std::to_string(r.getQuantity()),
                        formatPrice(r.getPrice()),
                        r.getReason(),
                        r.getTransactionTime()});
        }

        csv.writeCSV();
    }

private:
    static std::string sideToString(Side side)
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

    static std::string statusToString(ExecStatus status)
    {
        switch (status)
        {
        case ExecStatus::Rejected:
            return "Rejected";
        default:
            return "Unknown";
        }
    }

    static std::string formatPrice(double price)
    {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << price;
        return oss.str();
    }
};

#endif
