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

std::shared_ptr<object> obool::operator<(const std::shared_ptr<object> &other) 
{
    if (typeid(*this) == typeid(*other))
    { 
        const std::shared_ptr<obool> b_other = std::dynamic_pointer_cast<obool>(other);
        return std::shared_ptr<obool>(new obool(this->value < b_other->value));
    }
    return object::operator<(other);
}

std::shared_ptr<object> obool::operator>(const std::shared_ptr<object> &other) 
{
    if (typeid(*this) == typeid(*other))
    { 
        const std::shared_ptr<obool> b_other = std::dynamic_pointer_cast<obool>(other); 
        return std::shared_ptr<obool>(new obool(this->value > b_other->value));       
    }
    return object::operator>(other);
}

std::shared_ptr<object> obool::operator==(const std::shared_ptr<object> &other) 
{
    if (typeid(*this) == typeid(*other))
    { 
        const std::shared_ptr<obool> b_other = std::dynamic_pointer_cast<obool>(other);
        return std::shared_ptr<obool>(new obool(this->value == b_other->value));
    }
    return object::operator==(other);
}     

std::string obool::to_string() const 
{
    std::stringstream stream;
    stream << std::boolalpha << this->value;
    return stream.str();
}