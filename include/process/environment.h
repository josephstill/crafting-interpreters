#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <unordered_map>

#include "tokens/token.h"
#include "types/object.h"

class environment
{

public:
    environment();
    ~environment();
    bool define(std::shared_ptr<token>, std::shared_ptr<object> value);
    std::shared_ptr<object> get(std::shared_ptr<token> name);

private:

    std::unordered_map<std::string, std::shared_ptr<object>> state_map;
};

#endif