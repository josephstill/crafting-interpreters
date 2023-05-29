#ifndef ASTPRINTER_H
#define ASTPRINTER_H

#include "generated/expression/expressionvisitor.h"

class astprinter: public expressionvisitor
{

public:
    astprinter();
    ~astprinter();

    std::shared_ptr<object> expression_to_string(std::shared_ptr<expression> &expr);
    virtual std::shared_ptr<object> visit_ternaryexpression(ternaryexpression *to_visit);
    virtual std::shared_ptr<object> visit_binaryexpression(binaryexpression *to_visit);
    virtual std::shared_ptr<object> visit_groupingexpression(groupingexpression *to_visit);
    virtual std::shared_ptr<object> visit_literalexpression(literalexpression *to_visit);
    virtual std::shared_ptr<object> visit_unaryexpression(unaryexpression *to_visit);
};

#endif
