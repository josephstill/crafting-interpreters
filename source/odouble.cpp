#include <sstream>
#include <string>

#include "odouble.h"

odouble::odouble(double value):
    value(value)
{

}

odouble::odouble(std::string value)
{
    size_t idx = 0;
    this->value = std::stod(value, &idx);
}

odouble::odouble(const odouble &other):
    value(other.value)
{

}

odouble::~odouble()
{

}

std::string odouble::to_string() const 
{
    std::stringstream stream;
    stream << this->value;
    return stream.str();
}

std::string odouble::type_name() const 
{
    return "double";
}