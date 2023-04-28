#ifndef OBOOL_H
#define OBOOL_H

#include "types/object.h"

class obool: public object
{

public:
    obool(bool value);
    obool(std::string value);
    obool(const obool &other);
    ~obool();

    virtual std::string to_string() const; 
    virtual std::string type_name() const;    

private:
    bool value;
};

#endif