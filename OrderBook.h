#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "InputOrder.h"
#include "ExecutionReport.h"

class OrderBook
{
private:
    std::string instrument;
    std::vector<InputOrder> buyOrders;
    std::vector<InputOrder> sellOrders;
    std::map<double, int> buySeqCounter;
    std::map<double, int> sellSeqCounter;

public:
    OrderBook(std::string instrumentName) : instrument(instrumentName) {}

    bool canMatch(const InputOrder &order);

    std::vector<ExecutionReport> addOrder(InputOrder order, const std::string &generatedOrderId);

    void displayOrderBook();

    std::string getInstrument() const { return instrument; }
    int getBuyOrderCount() const { return buyOrders.size(); }
    int getSellOrderCount() const { return sellOrders.size(); }

private:
    void insertIntoBuyBook(InputOrder &order, const std::string &orderId);
    void insertIntoSellBook(InputOrder &order, const std::string &orderId);
    void insertIntoBook(InputOrder &order, const std::string &orderId);
    void removePassive(Side aggressiveSide);
};
