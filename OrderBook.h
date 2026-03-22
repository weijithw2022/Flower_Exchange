#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "InputOrder.h"
#include "ExecutionReport.h"

using namespace std;

class OrderBook
{
private:
    string instrument;
    vector<InputOrder> buyOrders;  
    vector<InputOrder> sellOrders; 
    map<double, int> buySeqCounter;
    map<double, int> sellSeqCounter;

public:
    OrderBook(string instrumentName) : instrument(instrumentName) {}

    bool canMatch(const InputOrder& order);

    vector<ExecutionReport> addOrder(InputOrder order, const string& generatedOrderId);

    void displayOrderBook();

    string getInstrument() const { return instrument; }
    int getBuyOrderCount() const { return buyOrders.size(); }
    int getSellOrderCount() const { return sellOrders.size(); }

private:
    void insertIntoBuyBook (InputOrder& order, const string& orderId);
    void insertIntoSellBook(InputOrder& order, const string& orderId);
    void insertIntoBook(InputOrder& order, const string& orderId);
    void removePassive(Side aggressiveSide);
};


