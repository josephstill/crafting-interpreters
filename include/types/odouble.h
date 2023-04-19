#ifndef ODOUBLE_H
#define ODOUBLE_H

#include "types/object.h"

class odouble: public object
{

public:
    odouble(double value);
    odouble(std::string value);
    odouble(const odouble &other);
    ~odouble();

    virtual std::string to_string() const; 
    virtual std::string type_name() const;    

private:
    double value;
};

#endif