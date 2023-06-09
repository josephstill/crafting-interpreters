#include "process/environment.h"
#include "types/oexception.h"

#include <sstream>

environment::environment() 
{

}

environment::~environment() 
{

}

bool environment::define(std::shared_ptr<token> name, std::shared_ptr<object> value) 
{
    std::string name_v = name->lex();
    this->state_map[name_v] = value;
    return true;
}

std::shared_ptr<object> environment::get(std::shared_ptr<token> name)
{
    std::string name_v = name->lex();
    if (this->state_map.find(name_v) != this->state_map.end())
    {
        return this->state_map[name_v];
    }
    std::stringstream stream;
    stream << "Undefeined variable " << name_v; 
    throw oexception(oexception::RUNTIMEERROR, stream.str(), -1);

    return std::shared_ptr<object>(nullptr);
}