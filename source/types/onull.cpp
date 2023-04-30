#include "types/onull.h"

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

std::string onull::to_string() const 
{
    return "nill";
}
