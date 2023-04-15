#ifndef OBJECT_H
#define OBJECT_H

#include <string>

class object
{
public:
    virtual ~object() {}
    virtual std::string to_string() const = 0; 
    virtual std::string type_name() const = 0;

    friend std::ostream& operator<< (std::ostream& stream, const object& o)
    {
        stream << o.to_string();
        return stream;
    }

protected:

    object() {}
};

#endif