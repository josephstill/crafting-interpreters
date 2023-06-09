#ifndef STATEMENT_H
#define STATEMENT_H

#include <memory>
#include "types/object.h"
#include "expression/expression.h"

class statementvisitor;

class statement 
{

public:
    ~statement() {}
    virtual std::string to_string() const = 0; 
    virtual std::string type_name() const = 0;  

    virtual void accept(statementvisitor *visitor) = 0;

    friend std::ostream& operator<<(std::ostream& stream, const statement &s)
    {
        stream << s.to_string();
        return stream;
    }   

protected:
    statement()
    {

    }
};



#endif