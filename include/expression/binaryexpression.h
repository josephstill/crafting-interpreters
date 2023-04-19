#ifndef BINARYEXPRESSION_H
#define BINARYEXPRESSION_H

#include <memory>

#include "expression/expression.h"
#include "tokens/token.h"

class binaryexpression: public expression 
{
public:
    binaryexpression(std::shared_ptr<expression> left, std::shared_ptr<token> op, std::shared_ptr<expression> right);
    binaryexpression(const binaryexpression &other);    
    ~binaryexpression();

    virtual std::string to_string(); 
    virtual std::string type_name();

private:
    std::shared_ptr<expression> left; 
    std::shared_ptr<token>      op; 
    std::shared_ptr<expression> right;
};

#endif