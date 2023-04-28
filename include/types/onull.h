#ifndef ONULL_H
#define ONULL_H

#include "types/object.h"

class onull: public object
{

public:
    onull();
    onull(const onull &other);
    ~onull();

    virtual std::string to_string() const; 
    virtual std::string type_name() const;    
};

#endif