#include "process/environment.h"

environment::environment() 
{

}

environment::~environment() 
{

}

bool environment::define(std::string name, std::shared_ptr<object> value) 
{
    this->state_map[name] = value;
    return true;
}