#ifndef READINPUTORDER_H
#define READINPUTORDER_H

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "InputOrder.h"
using namespace std;

class ReadInputOrder {
public:
    static vector<InputOrder> readCSV(const string& filename) {
        vector<InputOrder> orders;
        ifstream file(filename);

        if (!file.is_open())
            throw runtime_error("Could not open file: " + filename);

        string line;
        getline(file, line); 

        while (getline(file, line)) {
            if (line.empty()) continue;

            istringstream ss(line);
            string clientOrderId, instrument, sideStr, quantityStr, priceStr;

            getline(ss, clientOrderId, ',');
            getline(ss, instrument,    ',');
            getline(ss, sideStr,       ',');
            getline(ss, quantityStr,   ',');
            getline(ss, priceStr,      ',');

            int    side     = stoi(trim(sideStr));
            int    quantity = stoi(trim(quantityStr));
            double price    = stod(trim(priceStr));

            orders.emplace_back(
                trim(clientOrderId),
                trim(instrument),
                side,
                price,
                quantity
            );
        }

        file.close();
        return orders;
    }

private:
    static string trim(const string& s) {
        size_t start = s.find_first_not_of(" \t\r\n");
        size_t end   = s.find_last_not_of(" \t\r\n");
        return (start == string::npos) ? "" : s.substr(start, end - start + 1);
    }
};

#endif