#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "generated/statement/statementvisitor.h"

class interpreter: public statementvisitor
{

public:
    interpreter();
    ~interpreter();
    std::shared_ptr<object> execute(std::shared_ptr<statement> &stmt);    
    virtual void visit_expressionstatement(expressionstatement *to_visit);
    virtual void visit_printstatement(printstatement *to_visit);

};

#endif