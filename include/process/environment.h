#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <unordered_map>

#include "types/object.h"

class environment
{

public:
    environment();
    ~environment();
    bool define(std::string name, std::shared_ptr<object> value);

private:

    std::unordered_map<std::string, std::shared_ptr<object>> state_map;
};

#endif