#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <memory>

#include "types/object.h"

class expressionvisitor;

class expression
{
    
public:
    ~expression() {}
    virtual std::shared_ptr<object> accept(expressionvisitor *visitor) = 0;
    virtual std::string to_string() const = 0; 
    virtual std::string type_name() const = 0;  

    friend std::ostream& operator<<(std::ostream& stream, const expression &e)
    {
        stream << e.to_string();
        return stream;
    }    
    
protected:
    expression()
    {

    }

};

#endif
