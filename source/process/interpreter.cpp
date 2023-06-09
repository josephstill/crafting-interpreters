#include "process/interpreter.h"

#include <iostream>

#include "types/odouble.h"
#include "types/obool.h"
#include "types/onull.h"
#include "types/oexception.h"

interpreter::interpreter() 
{

}

interpreter::~interpreter() 
{

}

std::shared_ptr<object> interpreter::evaluate(std::shared_ptr<expression> &exp)
{
    return exp->accept(this);
}

void interpreter::execute(std::shared_ptr<statement> &stmt)
{
    stmt->accept(this);
}

void interpreter::interpret(std::vector<std::shared_ptr<statement>> statements)
{
    for (std::shared_ptr<statement> stmt : statements)
    {
        this->execute(stmt);
    }
}

std::shared_ptr<object> interpreter::visit_binaryexpression(binaryexpression *to_visit) 
{
    std::shared_ptr<object> left = this->evaluate(to_visit->left);    
    std::shared_ptr<object> right = this->evaluate(to_visit->right);   
    try
    {
        switch (to_visit->op->get_token_type()) 
        {
            case MINUS:
            {
                return left->operator-(right);
            }
            break;
            case SLASH:
            {
                return left->operator/(right);
            }
            case STAR:
            {
                return left->operator*(right);
            }
            break;
            case PLUS:
            {
                return left->operator+(right);
            }
            break;
            case GREATER:
            {
                return left->operator>(right);  
            }         
            break;
            case GREATER_EQUAL:
            {
                return left->operator>=(right);  
            }         
            break;
            case LESS:
            {
                return left->operator<(right);  
            }         
            break;
            case LESS_EQUAL:
            {
                return left->operator<=(right);  
            }         
            break;
            case BANG_EQUAL:
            {
                return left->operator!=(right);  
            }         
            break;
            case EQUAL_EQUAL:
            {
                return left->operator==(right);  
            }         
            break;                                                            
            default:
                break;
        }   
    }  
    catch(const oexceprion &e)
    {
        throw oexceprion(oexceprion::INTERPRETERERROR, e.to_string(), to_visit->op->line());
    }
    return std::shared_ptr<object>(new onull());
}     

void interpreter::visit_expressionstatement(expressionstatement *to_visit) 
{
    this->evaluate(to_visit->exp);
}

std::shared_ptr<object> interpreter::visit_groupingexpression(groupingexpression *to_visit) 
{
   return this->evaluate(to_visit->exp);
}

std::shared_ptr<object> interpreter::visit_literalexpression(literalexpression *to_visit) 
{
    return to_visit->value;
}

void interpreter::visit_printstatement(printstatement *to_visit) 
{
    std::shared_ptr<object> val = this->evaluate(to_visit->exp);
    std::cout << val;
}

std::shared_ptr<object> interpreter::visit_ternaryexpression(ternaryexpression *to_visit) 
{
    std::shared_ptr<object> left = this->evaluate(to_visit->left);   
    std::shared_ptr<object> center = this->evaluate(to_visit->center);       
    std::shared_ptr<object> right = this->evaluate(to_visit->right);

    if (to_visit->o1->get_token_type() == QUESTION && to_visit->o2->get_token_type() == COLON)
    {
        if (!left->operator!())
        {
            return center;
        }
        else
        {
            return right;
        }
    }

    throw oexceprion(oexceprion::INTERPRETERERROR, "Unknown opeerator ", to_visit->o1->line());    
    return std::shared_ptr<object>(new onull());
}

std::shared_ptr<object> interpreter::visit_unaryexpression(unaryexpression *to_visit) 
{
    try
    {    
        std::shared_ptr<object> right = this->evaluate(to_visit->right);
        switch (to_visit->op->get_token_type())
        {
            case MINUS:
            {
                right->operator*=(-1);
                return right;
            }
            break;
            case BANG:
            {
                return std::shared_ptr<object>(new obool(right->operator!()));
            }
            default:
                break;
        }
    }
    catch(const oexceprion &e)
    {
        throw oexceprion(oexceprion::INTERPRETERERROR, e.to_string(), to_visit->op->line());
    }
    return std::shared_ptr<object>(new onull());
}
