#include <sstream>

#include "types/oexception.h"

std::unordered_map<oexception::exceptiontype, std::string> oexception::exception_names = 
{
    {SCANERROR, "Scanner Error"},
    {PARSEERROR, "Parser Error"},
    {RUNTIMEERROR, "Runtime Error"},
};

oexception::oexception(exceptiontype type, std::string reason, int line_number):
    object("exception"),
    line_number(line_number),
    reason(reason),
    type(type) 
{

}

oexception::oexception(const oexception &other):
    object(other.type_name()),
    line_number(other.line_number),
    reason(other.reason),
    type(other.type)  
{

}

oexception::~oexception() 
{

}

std::string oexception::to_string() const 
{
    std::stringstream stream;
    stream << exception_names[this->type] << ": [line " << this->line_number << "] : " << this->reason;
    return stream.str();
}
