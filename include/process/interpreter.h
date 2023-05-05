#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "generated/expressionvisitor.h"

class interpreter: public expressionvisitor
{

public:
    interpreter();
    ~interpreter();
    std::shared_ptr<object> evaluate(std::shared_ptr<expression> &expr);    
    virtual std::shared_ptr<object> visit_ternaryexpression(ternaryexpression *to_visit);
    virtual std::shared_ptr<object> visit_binaryexpression(binaryexpression *to_visit);
    virtual std::shared_ptr<object> visit_groupingexpression(groupingexpression *to_visit);
    virtual std::shared_ptr<object> visit_literalexpression(literalexpression *to_visit);
    virtual std::shared_ptr<object> visit_unaryexpression(unaryexpression *to_visit);

};

#endif