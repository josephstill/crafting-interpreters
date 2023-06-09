#include "types/object.h"
#include "types/obool.h"
#include "types/oexception.h"
#include "types/onull.h"

#include <sstream>

object::object(std::string type_name):
    name(type_name)
{

}

std::shared_ptr<object> object::operator+(const std::shared_ptr<object> &other) 
{
    std::stringstream stream;
    stream << this->type_name() << " does not support addition by " << other->type_name();
    throw oexception(oexception::RUNTIMEERROR, stream.str(), -1);

    return std::shared_ptr<object>(nullptr);    
}

std::shared_ptr<object> object::operator-(const std::shared_ptr<object> &other) 
{
    std::stringstream stream;
    stream << this->type_name() << " does not support cubtraction by " << other->type_name();
    throw oexception(oexception::RUNTIMEERROR, stream.str(), -1);

    return std::shared_ptr<object>(nullptr); 
}

std::shared_ptr<object> object::operator*(const std::shared_ptr<object> &other) 
{
    std::stringstream stream;
    stream << this->type_name() << " does not support multiplication by " << other->type_name();
    throw oexception(oexception::RUNTIMEERROR, stream.str(), -1);

    return std::shared_ptr<object>(nullptr); 
}

std::shared_ptr<object> object::operator/(const std::shared_ptr<object> &other) 
{
    std::stringstream stream;
    stream << this->type_name() << " does not support division by " << other->type_name();
    throw oexception(oexception::RUNTIMEERROR, stream.str(), -1);

    return std::shared_ptr<object>(nullptr); 
}   

std::shared_ptr<object> object::operator<(const std::shared_ptr<object> &other) 
{
    std::stringstream stream;
    stream << this->type_name() << " does not support comparison to " << other->type_name();
    throw oexception(oexception::RUNTIMEERROR, stream.str(), -1);

    return std::shared_ptr<object>(nullptr); 
}

std::shared_ptr<object> object::operator<=(const std::shared_ptr<object> &other) 
{
    return std::shared_ptr<obool>(new obool(this->operator>(other)->operator!())); 
}

std::shared_ptr<object> object::operator>(const std::shared_ptr<object> &other) 
{
    std::stringstream stream;
    stream << this->type_name() << " does not support comparison to " << other->type_name();
    throw oexception(oexception::RUNTIMEERROR, stream.str(), -1);

    return std::shared_ptr<object>(nullptr); 
}

std::shared_ptr<object> object::operator>=(const std::shared_ptr<object> &other) 
{
    return std::shared_ptr<obool>(new obool(this->operator<(other)->operator!())); 
}

std::shared_ptr<object> object::operator!=(const std::shared_ptr<object> &other) 
{
    return std::shared_ptr<obool>(new obool(this->operator==(other)->operator!())); 
}

std::shared_ptr<object> object::operator==(const std::shared_ptr<object> &other) 
{
    return std::shared_ptr<obool>(new obool(false));
}

object &object::operator=(const std::shared_ptr<object> &other) 
{
    std::stringstream stream;
    stream << this->type_name() << " does not support assignment by " << other->type_name();
    throw oexception(oexception::RUNTIMEERROR, stream.str(), -1);

    return *this;
}

object &object::operator+=(const std::shared_ptr<object> &other) 
{
    std::stringstream stream;
    stream << this->type_name() << " does not support add by " << other->type_name();
    throw oexception(oexception::RUNTIMEERROR, stream.str(), -1);

    return *this;
}

object &object::operator-=(const std::shared_ptr<object> &other) 
{
    std::stringstream stream;
    stream << this->type_name() << " does not support subtract by " << other->type_name();
    throw oexception(oexception::RUNTIMEERROR, stream.str(), -1);

    return *this;
}

object &object::operator*=(const std::shared_ptr<object> &other) 
{
    std::stringstream stream;
    stream << this->type_name() << " does not support multiply by " << other->type_name();
    throw oexception(oexception::RUNTIMEERROR, stream.str(), -1);

    return *this;
}

object &object::operator*=(double other) 
{
    std::stringstream stream;
    stream << this->type_name() << " does not support multiply by double";
    throw oexception(oexception::RUNTIMEERROR, stream.str(), -1);

    return *this;    
}   

object &object::operator/=(const std::shared_ptr<object> &other) 
{
    std::stringstream stream;
    stream << this->type_name() << " does not support divide by " << other->type_name();
    throw oexception(oexception::RUNTIMEERROR, stream.str(), -1);

    return *this;
}   

bool object::operator!() const 
{
    std::stringstream stream;
    stream << this->type_name() << " does not suport boolean operations";
    throw oexception(oexception::RUNTIMEERROR, stream.str(), -1);

    return false;    
}

std::string object::type_name() const
{
    return this->name;
}

std::ostream& operator<<(std::ostream& stream, const object &o)
{
    stream << o.to_string();
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const object *o)
{
    stream << o->to_string();
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const std::shared_ptr<object> &o)
{
    stream << o->to_string();
    return stream;
}   