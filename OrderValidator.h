#ifndef ORDERVALIDATOR_H
#define ORDERVALIDATOR_H

#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include "InputOrder.h"
#include "ValidationResult.h"
#include "Side.h"

using namespace std;

class OrderValidator
{
public:
    using Rule = function<ValidationResult(const InputOrder&)>;

    static ValidationResult validate(const InputOrder& order)
    {
        for (const auto& rule : rules())
        {
            ValidationResult result = rule(order);
            if (!result.valid)
                return result;
        }
        return ValidationResult::pass();
    }

private:
    static const vector<Rule>& rules()
    {
        static const vector<Rule> validationRules = {
            validateClientOrderId,
            validateInstrument,
            validateSide,
            validatePrice,
            validateQuantityRange,
            validateQuantityMultiple
        };
        return validationRules;
    }

    static ValidationResult validateClientOrderId(const InputOrder& order)
    {
        if (order.getClientOrderId().empty())
            return ValidationResult::fail("ClientOrderId", "Missing Client Order ID");
        return ValidationResult::pass();
    }

    static ValidationResult validateInstrument(const InputOrder& order)
    {
        if (order.getInstrument().empty())
            return ValidationResult::fail("Instrument", "Missing Instrument");

        static const vector<std::string> valid = {
            "Rose", "Lavender", "Lotus", "Tulip", "Orchid"
        };
        if (std::find(valid.begin(), valid.end(), order.getInstrument()) == valid.end())
            return ValidationResult::fail("Instrument", "Invalid Instrument");

        return ValidationResult::pass();
    }

    static ValidationResult validateSide(const InputOrder& order)
    {
        if (order.getSide() != Side::Buy && order.getSide() != Side::Sell)
            return ValidationResult::fail("Side", "Invalid Side");
        return ValidationResult::pass();
    }

    static ValidationResult validatePrice(const InputOrder& order)
    {
        if (order.getPrice() <= 0)
            return ValidationResult::fail("Price", "Invalid Price");
        return ValidationResult::pass();
    }

    static ValidationResult validateQuantityRange(const InputOrder& order)
    {
        if (order.getQuantity() < 10 || order.getQuantity() >= 1000)
            return ValidationResult::fail("Quantity", "Invalid Quantity");
            // return ValidationResult::fail("Quantity", "Invalid quantity: must be between 10 and 1000");
        return ValidationResult::pass();
    }

    static ValidationResult validateQuantityMultiple(const InputOrder& order)
    {
        if (order.getQuantity() % 10 != 0)
            return ValidationResult::fail("Quantity", "Invalid Quantity");
            // return ValidationResult::fail("Quantity", "Invalid quantity: must be a multiple of 10");
        return ValidationResult::pass();
    }
};

#endif