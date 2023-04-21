#ifndef ASTPRINTER_H
#define ASTPRINTER_H

#include "generated/expressionvisitor.h"

class astprinter: public expressionvisitor
{

public:
    astprinter();
    ~astprinter();

    std::shared_ptr<object> expression_to_string(expression *expr);
    virtual std::shared_ptr<object> visit_binaryexpression(binaryexpression *to_visit);
    virtual std::shared_ptr<object> visit_groupingexpression(groupingexpression *to_visit);
    virtual std::shared_ptr<object> visit_literalexpression(literalexpression *to_visit);
    virtual std::shared_ptr<object> visit_unaryexpression(unaryexpression *to_visit);
};

#endif
