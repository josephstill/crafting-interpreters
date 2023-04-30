#include <sstream>
#include <string>

#include "types/odouble.h"

odouble::odouble(double value):
    object("double"),
    value(value)
{

}

odouble::odouble(std::string value):
    object("double")
{
    size_t idx = 0;
    this->value = std::stod(value, &idx);
}

odouble::odouble(const odouble &other):
    object(other.type_name()),
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
