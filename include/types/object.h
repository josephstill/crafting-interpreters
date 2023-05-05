#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <memory>
#include <unordered_map>

class object
{
public:
    virtual ~object() {}
    virtual std::string to_string() const = 0; 
    std::string type_name() const;

    virtual std::shared_ptr<object> operator+(const std::shared_ptr<object> &other);
    virtual std::shared_ptr<object> operator-(const std::shared_ptr<object> &other);
    virtual std::shared_ptr<object> operator*(const std::shared_ptr<object> &other);   
    virtual std::shared_ptr<object> operator/(const std::shared_ptr<object> &other);

    virtual std::shared_ptr<object> operator<(const std::shared_ptr<object> &other);
    virtual std::shared_ptr<object> operator<=(const std::shared_ptr<object> &other);
    virtual std::shared_ptr<object> operator>(const std::shared_ptr<object> &other);
    virtual std::shared_ptr<object> operator>=(const std::shared_ptr<object> &other);
    virtual std::shared_ptr<object> operator!=(const std::shared_ptr<object> &other);
    virtual std::shared_ptr<object> operator==(const std::shared_ptr<object> &other);

    virtual object &operator=(const std::shared_ptr<object> &other);
    virtual object &operator+=(const std::shared_ptr<object> &other);
    virtual object &operator-=(const std::shared_ptr<object> &other);
    virtual object &operator*=(const std::shared_ptr<object> &other);
    virtual object &operator*=(double other);    
    virtual object &operator/=(const std::shared_ptr<object> &other);    

    virtual bool operator!() const;

    friend std::ostream& operator<<(std::ostream& stream, const object &o);
    friend std::ostream& operator<<(std::ostream& stream, const object *o);
    friend std::ostream& operator<<(std::ostream& stream, const std::shared_ptr<object> &o);

protected:

    object(std::string type_name);

private:

    std::string name;

};

#endif