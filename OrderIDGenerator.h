#ifndef ORDERIDGENERATOR_H
#define ORDERIDGENERATOR_H

#include <string>
#include <sstream>
using namespace std;

class OrderIDGenerator {
private:
    static int counter;

public:
    static string generateOrderID() {
        counter++;
        stringstream ss;
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

int OrderIDGenerator::counter = 0;

#endif