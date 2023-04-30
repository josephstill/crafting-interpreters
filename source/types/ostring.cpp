#include "types/ostring.h"

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

std::string ostring::to_string() const
{
    return this->value;
} 