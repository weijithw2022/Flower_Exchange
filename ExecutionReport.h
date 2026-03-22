#ifndef EXECUTIONREPORT_H
#define EXECUTIONREPORT_H

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "ExecStatus.h"
#include "Side.h"
using namespace std;

class ExecutionReport
{

private:
    string orderId;
    string clientOrderId;
    string instrument;
    //int side;
    Side side;
    // int status;
    ExecStatus status;
    int quantity;
    double price;
    string reason;
    string transactionTime;

public:
    ExecutionReport(string id, string clientOrderId, string instrument, Side side, ExecStatus status, int quantity, double price)
        : orderId(id), clientOrderId(clientOrderId), instrument(instrument), side(side), status(status), quantity(quantity), price(price), reason(""), transactionTime(generateTimestamp()) {}

    ExecutionReport(string id, string clientOrderId, string instrument, Side side, ExecStatus status, int quantity, double price, string r)
        : orderId(id), clientOrderId(clientOrderId), instrument(instrument), side(side), status(status), quantity(quantity), price(price), reason(r), transactionTime(generateTimestamp()) {}

    string getOrderId() const { return orderId; }
    string getClientOrderId() const { return clientOrderId; }
    string getInstrument() const { return instrument; }
    Side getSide() const { return side; }
    ExecStatus getStatus() const { return status; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }
    void setReason(string r) { reason = r; }
    string getReason() const { return reason; }
    string getTransactionTime() const { return transactionTime; }

private:
    static string generateTimestamp()
    {
        auto now = chrono::system_clock::now();
        auto ms = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()) % 1000;
        time_t t = chrono::system_clock::to_time_t(now);
        tm tm = *gmtime(&t);
        ostringstream oss;
        oss << put_time(&tm, "%Y%m%d-%H%M%S")
            << "." << setfill('0') << setw(3) << ms.count();
        return oss.str();
    }
};

#endif