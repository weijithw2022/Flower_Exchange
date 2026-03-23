#ifndef ORDERIDGENERATOR_H
#define ORDERIDGENERATOR_H

#include <string>
#include <sstream>

class OrderIDGenerator {
private:
    static int counter;

public:
    static std::string generateOrderID() {
        counter++;
        std::stringstream ss;
        ss << "ord" << counter;
        return ss.str();
    }

    static void resetCounter() {
        counter = 0;
    }

    static int getCurrentCounter() {
        return counter;
    }
};

#endif