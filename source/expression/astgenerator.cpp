
#include <sstream>

#include "expression/astprinter.h"
#include "types/ostring.h"

astprinter::astprinter() {}

astprinter::~astprinter() {}

std::shared_ptr<object> astprinter::expression_to_string(std::shared_ptr<expression> &expr)
{
    return expr->accept(this);
}

std::shared_ptr<object> astprinter::visit_ternaryexpression(ternaryexpression *to_visit)
{
    std::stringstream stream;   
    stream << "( " << this->expression_to_string(to_visit->left) << " " << to_visit->o1 << " " << this->expression_to_string(to_visit->center) << " " << to_visit->o2 << " " << this->expression_to_string(to_visit->right) << " )";    
    std::shared_ptr<object> ret(new ostring(stream.str()));
    return ret;
}

std::shared_ptr<object> astprinter::visit_binaryexpression(binaryexpression *to_visit) 
{
    std::stringstream stream;
    stream << "( " << this->expression_to_string(to_visit->left) << " " << to_visit->op << " " << this->expression_to_string(to_visit->right) << " )";
    std::shared_ptr<object> ret(new ostring(stream.str()));
    return ret;
}

std::shared_ptr<object> astprinter::visit_groupingexpression(groupingexpression *to_visit) 
{
    std::stringstream stream;
    stream << "( " << this->expression_to_string(to_visit->exp) << " )";
    std::shared_ptr<object> ret(new ostring(stream.str()));
    return ret;

}

std::shared_ptr<object> astprinter::visit_literalexpression(literalexpression *to_visit) 
{
    std::stringstream stream;
    stream << "( " << to_visit->value << " )";
    std::shared_ptr<object> ret(new ostring(stream.str()));
    return ret;
}

std::shared_ptr<object> astprinter::visit_unaryexpression(unaryexpression *to_visit) 
{
    std::stringstream stream;
    stream << "( " << to_visit->op << " " << this->expression_to_string(to_visit->right) << " )";
    std::shared_ptr<object> ret(new ostring(stream.str()));
    return ret;
}


