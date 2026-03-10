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

public:
    OrderBook(string instrumentName) : instrument(instrumentName) {}

    bool canMatch(const InputOrder& order);

    vector<ExecutionReport> addOrder(InputOrder order);

    void displayOrderBook();

    string getInstrument() const { return instrument; }
    int getBuyOrderCount() const { return buyOrders.size(); }
    int getSellOrderCount() const { return sellOrders.size(); }
};