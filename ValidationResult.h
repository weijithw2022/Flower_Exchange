#ifndef VALIDATIONRESULT_H
#define VALIDATIONRESULT_H

#include <string>

struct ValidationResult
{
    bool valid;
    std::string field;
    std::string message;

    static ValidationResult pass()
    {
        return {true, "", ""};
    }

    static ValidationResult fail(const std::string &field, const std::string &message)
    {
        return {false, field, message};
    }
};

#endif