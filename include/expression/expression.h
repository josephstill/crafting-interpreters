#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <memory>

#include "types/object.h"

class expressionvisitor;

class expression: public object
{
public:
    ~expression() {}
    virtual std::shared_ptr<object> accept(expressionvisitor &visitor) = 0;
    
protected:
    expression():
        object("expression") 
    {

    }

};

#endif
