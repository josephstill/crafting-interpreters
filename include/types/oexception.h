#ifndef OEXCEPTION_H
#define OEXCEPTION_H

#include <string>
#include <unordered_map>

#include "types/object.h"



class oexceprion: public object
{

public:
    enum exceptiontype 
    {
        SCANERROR,
        PARSEERROR,
    };

    oexceprion(exceptiontype type, std::string reason, int line_number);
    oexceprion(const oexceprion &other);
    ~oexceprion();

    virtual std::string to_string() const; 
    virtual std::string type_name() const;    

private:
    int              line_number;
    std::string      reason;
    exceptiontype    type;
    static std::unordered_map<exceptiontype, std::string> exception_names;

};

#endif