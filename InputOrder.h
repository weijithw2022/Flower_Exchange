#include <string>
#include <tuple>
using namespace std;

class InputOrder{
    private:
        string clientOrderId;
        string instrument;
        int side;
        double price;
        int quantity;
    public:
        InputOrder(string clientOrderId, string instrument, int side, double price, int quantity){
            this->clientOrderId = clientOrderId;
            this->instrument = instrument;
            this->side = side;
            this->quantity = quantity;
            this->price = price;
        }

        // tuple<int, string> validate_order();
        
        string getClientOrderId() const { return clientOrderId; }
        string getInstrument() const { return instrument; }
        int getSide() const { return side; }
        int getQuantity() const { return quantity; }
        double getPrice() const { return price; }
};

