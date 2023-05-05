#ifndef ONULL_H
#define ONULL_H

#include "types/object.h"

class onull: public object
{

public:
    onull();
    onull(const onull &other);
    ~onull();

    virtual std::shared_ptr<object> operator==(const std::shared_ptr<object> &other);
    virtual bool operator!() const { return true; }
    
    virtual std::string to_string() const; 

};

#endif