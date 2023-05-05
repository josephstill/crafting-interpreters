#include <sstream>
#include <string>
#include <typeinfo>

#include "types/odouble.h"
#include "types/obool.h"

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

std::shared_ptr<object> odouble::operator+(const std::shared_ptr<object> &other) 
{
    if (typeid(*this) == typeid(*other))
    {   
        const std::shared_ptr<odouble> d_other = std::dynamic_pointer_cast<odouble>(other);
        double new_val = this->value + d_other->value;
        return std::shared_ptr<odouble>(new odouble(new_val));
    }

    return object::operator+(other);
}

std::shared_ptr<object> odouble::operator-(const std::shared_ptr<object> &other) 
{
    if (typeid(*this) == typeid(*other))
    {    
        const std::shared_ptr<odouble> d_other = std::dynamic_pointer_cast<odouble>(other);
        double new_val = this->value - d_other->value;
        return std::shared_ptr<odouble>(new odouble(new_val));
    }

    return object::operator-(other);
}

std::shared_ptr<object> odouble::operator*(const std::shared_ptr<object> &other) 
{
    if (typeid(*this) == typeid(*other))
    {    
        const std::shared_ptr<odouble> d_other = std::dynamic_pointer_cast<odouble>(other);
        double new_val = this->value * d_other->value;
        return std::shared_ptr<odouble>(new odouble(new_val));
    }

    return object::operator*(other);
}

std::shared_ptr<object> odouble::operator/(const std::shared_ptr<object> &other) 
{
    if (typeid(*this) == typeid(*other))
    {    
        const std::shared_ptr<odouble> d_other = std::dynamic_pointer_cast<odouble>(other);
        double new_val = this->value / d_other->value;
        return std::shared_ptr<odouble>(new odouble(new_val));
    }

    return object::operator/(other);
}  

std::shared_ptr<object> odouble::operator<(const std::shared_ptr<object> &other) 
{
    if (typeid(*this) == typeid(*other))
    { 
        const std::shared_ptr<odouble> b_other = std::dynamic_pointer_cast<odouble>(other);
        return std::shared_ptr<obool>(new obool(this->value < b_other->value));        
    }
    return object::operator<(other);
}

std::shared_ptr<object> odouble::operator>(const std::shared_ptr<object> &other) 
{
    if (typeid(*this) == typeid(*other))
    { 
        const std::shared_ptr<odouble> b_other = std::dynamic_pointer_cast<odouble>(other);
        return std::shared_ptr<obool>(new obool(this->value > b_other->value));           
    }
    return object::operator>(other);
}

std::shared_ptr<object> odouble::operator==(const std::shared_ptr<object> &other) 
{
    if (typeid(*this) == typeid(*other))
    { 
        const std::shared_ptr<odouble> b_other = std::dynamic_pointer_cast<odouble>(other);
        return std::shared_ptr<obool>(new obool(this->value == b_other->value));           
    }
    return object::operator==(other);    
}     

object &odouble::operator=(const std::shared_ptr<object> &other) 
{
    if (typeid(*this) == typeid(*other))
    {
        const std::shared_ptr<odouble> d_other = std::dynamic_pointer_cast<odouble>(other);
        this->value = d_other->value;
        return *this;
    }

    return object::operator+=(other);
}

object &odouble::operator+=(const std::shared_ptr<object> &other)
{
    if (typeid(*this) == typeid(*other))
    {
        const std::shared_ptr<odouble> d_other = std::dynamic_pointer_cast<odouble>(other);
        this->value += d_other->value;
        return *this;
    }

    return object::operator+=(other);
}

object &odouble::operator-=(const std::shared_ptr<object> &other) 
{
    if (typeid(*this) == typeid(*other))
    {
        const std::shared_ptr<odouble> d_other = std::dynamic_pointer_cast<odouble>(other);
        this->value -= d_other->value;
        return *this;
    }

    return object::operator+=(other);    
}

object &odouble::operator*=(const std::shared_ptr<object> &other) 
{
    if (typeid(*this) == typeid(*other))
    {
        const std::shared_ptr<odouble> d_other = std::dynamic_pointer_cast<odouble>(other);
        this->value *= d_other->value;
        return *this;
    }

    return object::operator+=(other);
}

object &odouble::operator*=(double other)
{
    this->value *= other;
    return *this;
}

object &odouble::operator/=(const std::shared_ptr<object> &other) 
{
    if (typeid(*this) == typeid(*other))
    {
        const std::shared_ptr<odouble> d_other = std::dynamic_pointer_cast<odouble>(other);
        this->value /= d_other->value;
        return *this;
    }

    return object::operator+=(other);
}   

bool odouble::operator!() const 
{
    return this->value == 0.0;
}

std::string odouble::to_string() const 
{
    std::stringstream stream;
    stream << this->value;
    return stream.str();
}
