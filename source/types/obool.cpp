#include <sstream>

#include "types/obool.h"

obool::obool(bool value):
    value(value) 
{

}

obool::obool(std::string value) 
{
    std::istringstream stream(value);
    stream >> std::boolalpha >> this->value;
}

obool::obool(const obool &other):
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

std::string obool::type_name() const 
{
    return "bool";
}  