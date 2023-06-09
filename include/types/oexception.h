#ifndef OEXCEPTION_H
#define OEXCEPTION_H

#include <string>
#include <unordered_map>

#include "types/object.h"


class oexception: public object
{

public:
    enum exceptiontype 
    {
        SCANERROR,
        PARSEERROR,
        INTERPRETERERROR,
        RUNTIMEERROR,
    };

    oexception(exceptiontype type, std::string reason, int line_number);
    oexception(const oexception &other);
    ~oexception();

    int line() const { return this->line_number; }
    virtual std::string to_string() const; 
 

private:
    int              line_number;
    std::string      reason;
    exceptiontype    type;
    static std::unordered_map<exceptiontype, std::string> exception_names;

};

#endif