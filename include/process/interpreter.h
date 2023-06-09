#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <vector>
#include "process/environment.h"
#include "generated/statement/statementvisitor.h"
#include "generated/expression/expressionvisitor.h"

class interpreter: public statementvisitor, public expressionvisitor
{

public:
    interpreter();
    ~interpreter();
    void interpret(std::vector<std::shared_ptr<statement>> statements);    
    virtual std::shared_ptr<object> visit_binaryexpression(binaryexpression *to_visit);     
    virtual void visit_expressionstatement(expressionstatement *to_visit);
    virtual std::shared_ptr<object> visit_groupingexpression(groupingexpression *to_visit);
    virtual std::shared_ptr<object> visit_literalexpression(literalexpression *to_visit);    
    virtual void visit_printstatement(printstatement *to_visit);
    virtual std::shared_ptr<object> visit_ternaryexpression(ternaryexpression *to_visit);
    virtual std::shared_ptr<object> visit_unaryexpression(unaryexpression *to_visit);
    virtual std::shared_ptr<object> visit_variableexpression(variableexpression *to_visit);
    virtual void visit_varstatement(varstatement *to_visit);

private:

    std::shared_ptr<object> evaluate(std::shared_ptr<expression> &exp);
    void execute(std::shared_ptr<statement> &stmt);   

    environment env;
};

#endif