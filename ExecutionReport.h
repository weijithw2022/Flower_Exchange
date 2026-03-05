#include <iostream>
#include <string>
using namespace std;

class ExecutionReport
{

private:
    string orderId;
    string clientOrderId;
    string instrument;
    int side; 
    int status; 
    int quantity;
    double price;
public: 
    ExecutionReport(string id, string clientOrderId, string instrument, int side, int status, int quantity, double price)
        : orderId(id), clientOrderId(clientOrderId), instrument(instrument), side(side), status(status), quantity(quantity), price(price) {}

    string getOrderId() const { return orderId; }
    string getClientOrderId() const { return clientOrderId; }
    string getInstrument() const { return instrument; }
    int getSide() const { return side; }
    int getStatus() const { return status; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }

    // string getSideString() const {
    //     return (side == 1) ? "BUY" : "SELL";
    // }
    
    // string getStatusString() const {
    //     switch(status) {
    //         case 1: return "NEW";
    //         case 2: return "FILLED"; 
    //         case 3: return "PARTIAL_FILL";
    //         case 4: return "REJECTED";
    //         default: return "UNKNOWN";
    //     }
    // }
};