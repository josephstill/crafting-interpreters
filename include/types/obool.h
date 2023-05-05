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


    virtual std::shared_ptr<object> operator<(const std::shared_ptr<object> &other);
    virtual std::shared_ptr<object> operator>(const std::shared_ptr<object> &other);
    virtual std::shared_ptr<object> operator==(const std::shared_ptr<object> &other);        

    virtual bool operator!() const { return !this->value; }

    virtual std::string to_string() const; 

private:
    bool value;
};

#endif