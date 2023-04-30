#include <sstream>

#include "types/oexception.h"

std::unordered_map<oexceprion::exceptiontype, std::string> oexceprion::exception_names = 
{
    {SCANERROR, "Scanner Error"},
};

oexceprion::oexceprion(exceptiontype type, std::string reason, int line_number):
    object("exception"),
    line_number(line_number),
    reason(reason),
    type(type) 
{

}

oexceprion::oexceprion(const oexceprion &other):
    object(other.type_name()),
    line_number(other.line_number),
    reason(other.reason),
    type(other.type)  
{

}

oexceprion::~oexceprion() 
{

}

std::string oexceprion::to_string() const 
{
    std::stringstream stream;
    stream << exception_names[this->type] << ": [line " << this->line_number << "] : " << this->reason;
    return stream.str();
}
