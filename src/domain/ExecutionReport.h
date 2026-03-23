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

class ExecutionReport
{

private:
    std::string orderId;
    std::string clientOrderId;
    std::string instrument;
    // int side;
    Side side;
    // int status;
    ExecStatus status;
    int quantity;
    double price;
    std::string reason;
    std::string transactionTime;

public:
    ExecutionReport(std::string id, std::string clientOrderId, std::string instrument, Side side, ExecStatus status, int quantity, double price)
        : orderId(id), clientOrderId(clientOrderId), instrument(instrument), side(side), status(status), quantity(quantity), price(price), reason(""), transactionTime(generateTimestamp()) {}

    ExecutionReport(std::string id, std::string clientOrderId, std::string instrument, Side side, ExecStatus status, int quantity, double price, std::string r)
        : orderId(id), clientOrderId(clientOrderId), instrument(instrument), side(side), status(status), quantity(quantity), price(price), reason(r), transactionTime(generateTimestamp()) {}

    std::string getOrderId() const { return orderId; }
    std::string getClientOrderId() const { return clientOrderId; }
    std::string getInstrument() const { return instrument; }
    Side getSide() const { return side; }
    ExecStatus getStatus() const { return status; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }
    void setReason(std::string r) { reason = r; }
    std::string getReason() const { return reason; }
    std::string getTransactionTime() const { return transactionTime; }

private:
    static std::string generateTimestamp()
    {
        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::gmtime(&t);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y%m%d-%H%M%S")
            << "." << std::setfill('0') << std::setw(3) << ms.count();
        return oss.str();
    }
};

#endif