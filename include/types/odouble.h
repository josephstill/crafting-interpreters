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

    virtual std::shared_ptr<object> operator+(const std::shared_ptr<object> &other);
    virtual std::shared_ptr<object> operator-(const std::shared_ptr<object> &other);
    virtual std::shared_ptr<object> operator*(const std::shared_ptr<object> &other);
    virtual std::shared_ptr<object> operator/(const std::shared_ptr<object> &other);       

    virtual std::shared_ptr<object> operator<(const std::shared_ptr<object> &other);
    virtual std::shared_ptr<object> operator>(const std::shared_ptr<object> &other);
    virtual std::shared_ptr<object> operator==(const std::shared_ptr<object> &other);     

    virtual object &operator=(const std::shared_ptr<object> &other);
    virtual object &operator+=(const std::shared_ptr<object> &other);
    virtual object &operator-=(const std::shared_ptr<object> &other);
    virtual object &operator*=(const std::shared_ptr<object> &other);
    virtual object &operator*=(double other);   
    virtual object &operator/=(const std::shared_ptr<object> &other);   
    virtual bool operator!() const;

    virtual std::string to_string() const; 

private:
    double value;
};

#endif