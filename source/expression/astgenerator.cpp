
#include <sstream>

#include "expression/astprinter.h"
#include "types/ostring.h"

astprinter::astprinter() {}

astprinter::~astprinter() {}

std::shared_ptr<object> astprinter::expression_to_string(expression *expr)
{
    return expr->visit(*this);
}

std::shared_ptr<object> astprinter::visit_binaryexpression(binaryexpression *to_visit) 
{
    std::stringstream stream;
    stream << "( " << this->expression_to_string(to_visit->left.get()) << " " << to_visit->op.get() << " " << this->expression_to_string(to_visit->right.get()) << " )";
    std::shared_ptr<object> ret(new ostring(stream.str()));
    return ret;
}

std::shared_ptr<object> astprinter::visit_groupingexpression(groupingexpression *to_visit) 
{
    std::stringstream stream;
    stream << "( " << this->expression_to_string(to_visit->exp.get()) << " )";
    std::shared_ptr<object> ret(new ostring(stream.str()));
    return ret;

}

std::shared_ptr<object> astprinter::visit_literalexpression(literalexpression *to_visit) 
{
    std::stringstream stream;
    stream << "( " << to_visit->value.get() << " )";
    std::shared_ptr<object> ret(new ostring(stream.str()));
    return ret;
}

std::shared_ptr<object> astprinter::visit_unaryexpression(unaryexpression *to_visit) 
{
    std::stringstream stream;
    stream << "( " << to_visit->op.get() << " " << this->expression_to_string(to_visit->right.get()) << " )";
    std::shared_ptr<object> ret(new ostring(stream.str()));
    return ret;
}


