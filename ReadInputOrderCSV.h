#ifndef READINPUTORDER_H
#define READINPUTORDER_H

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "InputOrder.h"

class ReadInputOrder
{
public:
    static std::vector<InputOrder> readCSV(const std::string &filename)
    {
        std::vector<InputOrder> orders;
        std::ifstream file(filename);

        if (!file.is_open())
            throw std::runtime_error("Could not open file: " + filename);

        std::string line;
        std::getline(file, line);

        while (std::getline(file, line))
        {
            if (line.empty())
                continue;

            std::istringstream ss(line);
            std::string clientOrderId, instrument, sideStr, quantityStr, priceStr;

            std::getline(ss, clientOrderId, ',');
            std::getline(ss, instrument, ',');
            std::getline(ss, sideStr, ',');
            std::getline(ss, quantityStr, ',');
            std::getline(ss, priceStr, ',');

            int side = std::stoi(trim(sideStr));
            int quantity = std::stoi(trim(quantityStr));
            double price = std::stod(trim(priceStr));

            orders.emplace_back(
                trim(clientOrderId),
                trim(instrument),
                side,
                price,
                quantity);
        }

        file.close();
        return orders;
    }

private:
    static std::string trim(const std::string &s)
    {
        std::size_t start = s.find_first_not_of(" \t\r\n");
        std::size_t end = s.find_last_not_of(" \t\r\n");
        return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
    }
};

#endif