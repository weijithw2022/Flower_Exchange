#ifndef VALIDATIONRESULT_H
#define VALIDATIONRESULT_H

#include <string>

using namespace std;

struct ValidationResult
{
    bool        valid;
    string field;
    string message;

    static ValidationResult pass()
    {
        return {true, "", ""};
    }

    static ValidationResult fail(const string& field, const string& message)
    {
        return {false, field, message};
    }
};

#endif