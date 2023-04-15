#include <sstream>

#include "oexception.h"

oexceprion::oexceprion(exceptiontype type, std::string reason, int line_number):
    line_number(line_number),
    reason(reason),
    type(type) 
{

}

oexceprion::oexceprion(const oexceprion &other):
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

std::string oexceprion::type_name() const 
{
    return "exception";
} 