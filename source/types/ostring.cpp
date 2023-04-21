#include "types/ostring.h"

ostring::ostring(const char *c_str):
    value(c_str) 
{

}

ostring::ostring(std::string cpp_string):
    value(cpp_string) 
{

}

ostring::ostring(const ostring &other):
    value(other.value) 
{

}

std::string ostring::to_string() const
{
    return this->value;
} 

std::string ostring::type_name()  const
{
    return "string";
}