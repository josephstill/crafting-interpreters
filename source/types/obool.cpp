#include <sstream>

#include "types/obool.h"

obool::obool(bool value):
    object("bool"),
    value(value) 
{

}

obool::obool(std::string value):
    object("bool") 
{
    std::istringstream stream(value);
    stream >> std::boolalpha >> this->value;
}

obool::obool(const obool &other):
    object(other.type_name()),
    value(other.value) 
{

}

obool::~obool() 
{

}

std::string obool::to_string() const 
{
    std::stringstream stream;
    stream << std::boolalpha << this->value;
    return stream.str();
}