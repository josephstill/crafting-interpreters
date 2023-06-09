#ifndef OSTRING_H
#define OSTRING_H

#include <string>

#include "types/object.h"

class ostring: public object
{

public:
    ostring(const char *c_str);
    ostring(std::string cpp_string);
    ostring(const ostring &other);

    virtual std::shared_ptr<object> operator+(const std::shared_ptr<object> &other);
    virtual std::shared_ptr<object> operator<(const std::shared_ptr<object> &other);
    virtual std::shared_ptr<object> operator>(const std::shared_ptr<object> &other);
    virtual std::shared_ptr<object> operator==(const std::shared_ptr<object> &other);     

    virtual object &operator+=(const std::shared_ptr<object> &other);
    virtual bool operator!() const;

    virtual std::string to_string() const; 

private:

    std::string value;

};

#endif