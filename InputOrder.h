#ifndef INPUTORDER_H
#define INPUTORDER_H

#include <string>
#include <tuple>
using namespace std;

class InputOrder
{
private:
    string clientOrderId;
    string instrument;
    int side;
    double price;
    int quantity;
    string orderId;
    int prioritySequence;

public:
    InputOrder(string clientOrderId, string instrument, int side, double price, int quantity)
    {
        this->clientOrderId = clientOrderId;
        this->instrument = instrument;
        this->side = side;
        this->quantity = quantity;
        this->price = price;
    }

    tuple<bool, string> validate_order() const;
    string getClientOrderId() const { return clientOrderId; }
    string getInstrument() const { return instrument; }
    int getSide() const { return side; }
    int getQuantity() const { return quantity; }
    void setQuantity(int newQuantity) { quantity = newQuantity; }
    double getPrice() const { return price; }
    void setOrderId(string id) { orderId = id; }
    string getOrderId() const { return orderId; }
    void setPrioritySequence(int seq) { prioritySequence = seq; }
    int getPrioritySequence() const { return prioritySequence; }

};

#endif
