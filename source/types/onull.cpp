#include "types/onull.h"
#include "types/obool.h"

onull::onull():
    object("null") 
{

}

onull::onull(const onull &other):
    object("null")
{

}

onull::~onull() 
{

}

std::shared_ptr<object> onull::operator==(const std::shared_ptr<object> &other) 
{
    if (typeid(*this) == typeid(other))
    {
        return std::shared_ptr<obool>(new obool(true));
    }
    return object::operator==(other);
}

std::string onull::to_string() const 
{
    return "nill";
}
