#ifndef EXCEPTIONTYPE_H
#define EXCEPTIONTYPE_H

#include <string>
#include <unordered_map>

enum exceptiontype 
{
    SCANERROR,
};

extern std::unordered_map<exceptiontype, std::string> exception_names;


#endif