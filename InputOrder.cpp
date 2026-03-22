#include "InputOrder.h"
#include "Side.h"
#include <vector>
#include <algorithm>
using namespace std;


tuple<bool, string> InputOrder::validate_order() const
{
    if (clientOrderId.empty())
        return {false, "Missing Client Order ID"};
    
    if (instrument.empty())
        return {false, "Missing Instrument"};
    
    static const vector<string> validInstruments = {"Rose", "Lavender", "Lotus", "Tulip", "Orchid"};
    if (find(validInstruments.begin(), validInstruments.end(), instrument) == validInstruments.end())
        return {false, "Invalid Instrument"};
    
    if (side != Side::Buy && side != Side::Sell)
        return {false, "Invalid Side"};

    if (price <= 0)
        return {false, "Invalid Price"};

    if (quantity < 10 || quantity >= 1000)
        return {false, "Invalid Quantity"};
        //return {false, "Invalid quantity: must be between 10 and 1000"};

    if (quantity % 10 != 0)
        return {false, "Invalid Quantity"};
        // return {false, "Invalid quantity: must be a multiple of 10"};

    return {true, "Valid order"};
}