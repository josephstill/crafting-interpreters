#include "process/parser.h"
#include "tokens/tokentype.h"

#include <iostream>
#include <sstream>

#include "types/obool.h"
#include "types/oexception.h"
#include "types/onull.h"

#include "generated/expression/ternaryexpression.h"
#include "generated/expression/binaryexpression.h"
#include "generated/expression/groupingexpression.h"
#include "generated/expression/literalexpression.h"
#include "generated/expression/unaryexpression.h"

parser::parser(std::vector<std::shared_ptr<token>> &tokens):
    err(false), 
    tokens(tokens) 
{

}

parser::~parser() 
{

}

std::shared_ptr<expression> parser::comparison(int *index)
{
    /**
     * comparison → term ( ( ">" | ">=" | "<" | "<=" ) term )*;
     */
    std::shared_ptr<expression> exp = this->term(index);
    while (this->match(index, {GREATER, GREATER_EQUAL, LESS, LESS_EQUAL}))
    {
        std::shared_ptr<token> oper = this->tokens[(*index) - 1];
        std::shared_ptr<expression> right = this->term(index);
        exp = std::shared_ptr<expression>(new binaryexpression(exp, oper, right));
    }

    return exp;
}

std::shared_ptr<expression> parser::equality(int *index)
{
    /**
     * equality → comparison ( ( "!=" | "==" ) comparison )*; 
     */
    std::shared_ptr<expression> exp = this->comparison(index);
    while (this->match(index, {BANG_EQUAL, EQUAL_EQUAL}))
    {
        std::shared_ptr<token> oper = this->tokens[(*index) - 1];
        std::shared_ptr<expression> right = this->comparison(index);
        exp = std::shared_ptr<expression>(new binaryexpression(exp, oper, right));
    }

    return exp;
}

void parser::error(std::string message, std::shared_ptr<token> tok)
{
    throw oexceprion(oexceprion::PARSEERROR, message, tok->line());    
}

std::shared_ptr<expression> parser::expr(int *index)
{
    /**
     * expression → ternary ( ( ",") ternary )*;
     */ 
    std::shared_ptr<expression> exp = this->ternary(index);  
    while (this->match(index, {COMMA}))
    { 
        std::shared_ptr<token> oper = this->tokens[(*index) - 1];
        std::shared_ptr<expression> right = this->ternary(index);
        exp = std::shared_ptr<expression>(new binaryexpression(exp, oper, right));
    }
    return exp; 
}

std::shared_ptr<expression> parser::factor(int *index)
{
    /**
     * factor → unary ( ( "/" | "*" ) unary )*;
     */
    std::shared_ptr<expression> exp = this->unary(index);
    while (this->match(index, {SLASH, STAR}))
    {
        std::shared_ptr<token> oper = this->tokens[(*index) - 1];
        std::shared_ptr<expression> right = this->unary(index);
        exp = std::shared_ptr<expression>(new binaryexpression(exp, oper, right));
    }
    return exp;
}    

bool parser::match(int *index, std::initializer_list<tokentype> types)
{
    if (*index < this->tokens.size())
    {
        tokentype current = this->tokens[*index]->get_token_type();
        for (tokentype t : types)
        {
            if (t == current)
            {
                *index += 1;
                return true;
            }
        }
    }
    return false;
}

std::shared_ptr<expression> parser::ternary(int *index)
{
    /**
     * ternary → equality ((?) equality (:) equality)?; 
     */    
    std::shared_ptr<expression> exp = this->equality(index); 
    if (this->match(index, {QUESTION})) 
    { 
        std::shared_ptr<token> o1 = this->tokens[(*index) - 1];
        std::shared_ptr<expression> center = this->equality(index);

        if (!this->match(index, {COLON}))
        {
            this->error("Expected colon", this->tokens[(*index) - 2]);
        }
        std::shared_ptr<token> o2 = this->tokens[(*index) - 1];
        std::shared_ptr<expression> right = this->equality(index);

        if (!right)
        {
            this->error("Expected expression", this->tokens[(*index) - 2]);
        }
        exp = std::shared_ptr<expression>(new ternaryexpression(exp, o1, center, o2, right));
    } 
    return exp;
}

std::shared_ptr<expression> parser::parse()
{
    try
    {
        int index = 0;
        return this->expr(&index);
    }
    catch(const oexceprion &e)
    {
        std::cout << e << std::endl;
        throw oexceprion(oexceprion::PARSEERROR, e.to_string(), e.line());    
    }
    return std::shared_ptr<expression>(nullptr);
}

std::shared_ptr<expression> parser::primary(int *index)
{
    /**
     * primary → NUMBER | STRING | "true" | "false" | "nil"
     *           "(" expression ")"; 
     */
    if (this->match(index, {FALSE})) 
    { 
        std::shared_ptr<object> value(new obool(false));
        return std::shared_ptr<expression>(new literalexpression(value));
    }
    
    if (this->match(index, {TRUE})) 
    { 
        std::shared_ptr<object> value(new obool(true));
        return std::shared_ptr<expression>(new literalexpression(value));
    }
    
    if (this->match(index, {NIL})) 
    { 
        std::shared_ptr<object> value(new onull());
        return std::shared_ptr<expression>(new literalexpression(value));
    }

    if (this->match(index, {NUMBER, STRING})) 
    {
        return std::shared_ptr<expression>(new literalexpression(this->tokens[(*index) - 1]->literal()));        
    }

    if (this->match(index, {LEFT_PAREN})) 
    {
        std::shared_ptr<expression> exp = this->expr(index);
        if (!this->match(index, {RIGHT_PAREN}))
        {
            this->error("Expected right parenthesis", this->tokens[(*index) - 2]);
        }
        return std::shared_ptr<expression>(new groupingexpression(exp));                     
    }    

    std::stringstream stream;
    stream << "Unexpected token " << this->tokens[(*index)]->to_string(); 
    this->error(stream.str(), this->tokens[(*index)]);

    return std::shared_ptr<expression>(nullptr);
}


void parser::synchronize(int *index)
{
    *index += 1;
    
    while (*index < this->tokens.size())
    {
        if (this->tokens[*index - 1]->get_token_type() == SEMICOLON)
        {
            return;
        }
        
        switch (this->tokens[*index]->get_token_type())
        {
            case CLASS:
            case FUN:
            case VAR:
            case FOR:
            case IF:
            case WHILE:
            case PRINT:
            case RETURN:
                return;
        }
            
        *index += 1;
    }
}

std::shared_ptr<expression> parser::term(int *index)
{
    /**
     * term → factor ( ( "-" | "+" ) factor )*;  
     */
    std::shared_ptr<expression> exp = this->factor(index);
    while (this->match(index, {MINUS, PLUS}))
    {
        std::shared_ptr<token> oper = this->tokens[(*index) - 1];
        std::shared_ptr<expression> right = this->factor(index);
        exp =  std::shared_ptr<expression>(new binaryexpression(exp, oper, right));
    }
    return exp;
}

std::shared_ptr<expression> parser::unary(int *index) 
{
    /**
     *  unary  → ( "!" | "-" ) unary
     *           | primary;
     */
    if (this->match(index, {BANG, MINUS}))
    {
        std::shared_ptr<token> oper = this->tokens[(*index) - 1];
        std::shared_ptr<expression> right = this->unary(index);
        return std::shared_ptr<expression>(new unaryexpression(oper, right));
    }
    return this->primary(index);
}