#include "types/ostring.h"
#include "types/obool.h"

#include <sstream>

ostring::ostring(const char *c_str):
    object("string"),
    value(c_str) 
{

}

ostring::ostring(std::string cpp_string):
    object("string"),
    value(cpp_string) 
{

}

ostring::ostring(const ostring &other):
    object(other.type_name()),
    value(other.value) 
{

}

std::shared_ptr<object> ostring::operator+(const std::shared_ptr<object> &other)
{
    std::stringstream stream;
    stream << this->value << other;
    return std::shared_ptr<object>(new ostring(stream.str()));
}

std::shared_ptr<object> ostring::operator<(const std::shared_ptr<object> &other) 
{
    if (typeid(*this) == typeid(*other))
    { 
        const std::shared_ptr<ostring> s_other = std::dynamic_pointer_cast<ostring>(other);
        return std::shared_ptr<obool>(new obool(this->value < s_other->value));         
    }
    return object::operator<(other);
}

std::shared_ptr<object> ostring::operator>(const std::shared_ptr<object> &other) 
{
    if (typeid(*this) == typeid(*other))
    { 
        const std::shared_ptr<ostring> s_other = std::dynamic_pointer_cast<ostring>(other);
        return std::shared_ptr<obool>(new obool(this->value > s_other->value)); 
    }
    return object::operator>(other);
}

std::shared_ptr<object> ostring::operator==(const std::shared_ptr<object> &other) 
{
    if (typeid(*this) == typeid(*other))
    { 
        const std::shared_ptr<ostring> s_other = std::dynamic_pointer_cast<ostring>(other);
        return std::shared_ptr<obool>(new obool(this->value == s_other->value));          
    }
    return object::operator==(other);
}     

object &ostring::operator+=(const std::shared_ptr<object> &other)
{
    std::stringstream stream;
    stream << this->value << other;
    this->value = stream.str();
    return *this;
}

bool ostring::operator!() const
{
    return this->value.size() == 0;
}

std::string ostring::to_string() const
{
    return this->value;
} 