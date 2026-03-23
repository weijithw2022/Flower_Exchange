#ifndef INPUTORDER_H
#define INPUTORDER_H

#include <string>
#include <tuple>
#include "Side.h"
#include "ExecStatus.h"

class InputOrder
{
private:
    std::string clientOrderId;
    std::string instrument;
    Side side;
    // int side;
    double price;
    int quantity;
    std::string orderId;
    int prioritySequence;

public:
    InputOrder(std::string clientOrderId, std::string instrument, int side, double price, int quantity)
    {
        this->clientOrderId = clientOrderId;
        this->instrument = instrument;
        this->side = static_cast<Side>(side);
        this->quantity = quantity;
        this->price = price;
    }

    // tuple<bool, string> validate_order() const;
    std::string getClientOrderId() const { return clientOrderId; }
    std::string getInstrument() const { return instrument; }
    Side getSide() const { return side; }
    int getQuantity() const { return quantity; }
    void setQuantity(int newQuantity) { quantity = newQuantity; }
    double getPrice() const { return price; }
    void setOrderId(std::string id) { orderId = id; }
    std::string getOrderId() const { return orderId; }
    void setPrioritySequence(int seq) { prioritySequence = seq; }
    int getPrioritySequence() const { return prioritySequence; }
};

#endif
