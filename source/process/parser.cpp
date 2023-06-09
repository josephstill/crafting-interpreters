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
#include "generated/expression/variableexpression.h"

#include "generated/statement/printstatement.h"
#include "generated/statement/expressionstatement.h"
#include "generated/statement/varstatement.h"

parser::parser():
    err(false)
{

}

parser::~parser() 
{

}

bool parser::at_end(std::vector<std::shared_ptr<token>> &tokens, int *index) const
{
    return *index >= tokens.size();
}

std::shared_ptr<expression> parser::comparison(std::vector<std::shared_ptr<token>> &tokens, int *index)
{
    /**
     * comparison → term ( ( ">" | ">=" | "<" | "<=" ) term )*;
     */
    std::shared_ptr<expression> exp = this->term(tokens, index);
    while (this->match(tokens, index, {GREATER, GREATER_EQUAL, LESS, LESS_EQUAL}))
    {
        std::shared_ptr<token> oper = tokens[(*index) - 1];
        std::shared_ptr<expression> right = this->term(tokens, index);
        exp = std::shared_ptr<expression>(new binaryexpression(exp, oper, right));
    }

    return exp;
}

std::shared_ptr<token> parser::consume(std::vector<std::shared_ptr<token>> &tokens, int *index, tokentype typ, std::string err)
{
    if (*index < tokens.size())
    {
        if (tokens[*index]->get_token_type() == typ)
        {
            std::shared_ptr<token> ret = tokens[*index];
            *index += 1;
            return ret;
        }    
    }
    this->error(err, tokens[(*index) - 1]);
    return std::shared_ptr<token>(nullptr);
}

std::shared_ptr<statement> parser::declaration(std::vector<std::shared_ptr<token>> &tokens, int *index)
{
    if (this->match(tokens, index, {VAR})) 
    {
        std::shared_ptr<token> name = this->consume(tokens, index, IDENTIFIER, "Expect variable name.");

        std::shared_ptr<object> value(new onull());
        std::shared_ptr<expression> asn(new literalexpression(value));
        
        if (this->match(tokens, index, {EQUAL}))
        {
            asn = this->expr(tokens, index);
        }

        this->consume(tokens, index, SEMICOLON, "Expect ';' after variable declaration.");
        return std::shared_ptr<statement>(new varstatement(name, asn));
    } 
    return this->stmt(tokens, index);
}

std::shared_ptr<expression> parser::equality(std::vector<std::shared_ptr<token>> &tokens, int *index)
{
    /**
     * equality → comparison ( ( "!=" | "==" ) comparison )*; 
     */
    std::shared_ptr<expression> exp = this->comparison(tokens, index);
    while (this->match(tokens, index, {BANG_EQUAL, EQUAL_EQUAL}))
    {
        std::shared_ptr<token> oper = tokens[(*index) - 1];
        std::shared_ptr<expression> right = this->comparison(tokens, index);
        exp = std::shared_ptr<expression>(new binaryexpression(exp, oper, right));
    }

    return exp;
}

void parser::error(std::string message, std::shared_ptr<token> tok)
{
    throw oexception(oexception::PARSEERROR, message, tok->line());    
}

std::shared_ptr<expression> parser::expr(std::vector<std::shared_ptr<token>> &tokens, int *index)
{
    /**
     * expression → ternary ( ( ",") ternary )*;
     */ 
    std::shared_ptr<expression> exp = this->ternary(tokens, index);  
    while (this->match(tokens, index, {COMMA}))
    { 
        std::shared_ptr<token> oper = tokens[(*index) - 1];
        std::shared_ptr<expression> right = this->ternary(tokens, index);
        exp = std::shared_ptr<expression>(new binaryexpression(exp, oper, right));
    }
    return exp; 
}

std::shared_ptr<statement> parser::expressionstmt(std::vector<std::shared_ptr<token>> &tokens, int *index)
{
    std::shared_ptr<expression> exp = this->expr(tokens, index);
    if (!this->match(tokens, index, {SEMICOLON}))
    {
        this->error("Expected a ;", tokens[(*index)]);
    }

    return std::shared_ptr<statement>(new expressionstatement(exp));
} 

std::shared_ptr<expression> parser::factor(std::vector<std::shared_ptr<token>> &tokens, int *index)
{
    /**
     * factor → unary ( ( "/" | "*" ) unary )*;
     */
    std::shared_ptr<expression> exp = this->unary(tokens, index);
    while (this->match(tokens, index, {SLASH, STAR}))
    {
        std::shared_ptr<token> oper = tokens[(*index) - 1];
        std::shared_ptr<expression> right = this->unary(tokens, index);
        exp = std::shared_ptr<expression>(new binaryexpression(exp, oper, right));
    }
    return exp;
}    

bool parser::match(std::vector<std::shared_ptr<token>> &tokens, int *index, std::initializer_list<tokentype> types)
{
    if (*index < tokens.size())
    {
        tokentype current = tokens[*index]->get_token_type();
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

std::shared_ptr<statement> parser::stmt(std::vector<std::shared_ptr<token>> &tokens, int *index)
{
    if (this->match(tokens, index, {PRINT}))
    {
        return this->printstmt(tokens, index);
    }

    return this->expressionstmt(tokens, index);
}

std::shared_ptr<expression> parser::ternary(std::vector<std::shared_ptr<token>> &tokens, int *index)
{
    /**
     * ternary → equality ((?) equality (:) equality)?; 
     */    
    std::shared_ptr<expression> exp = this->equality(tokens, index); 
    if (this->match(tokens, index, {QUESTION})) 
    { 
        std::shared_ptr<token> o1 = tokens[(*index) - 1];
        std::shared_ptr<expression> center = this->equality(tokens, index);

        if (!this->match(tokens, index, {COLON}))
        {
            this->error("Expected colon", tokens[(*index) - 2]);
        }
        std::shared_ptr<token> o2 = tokens[(*index) - 1];
        std::shared_ptr<expression> right = this->equality(tokens, index);

        if (!right)
        {
            this->error("Expected expression", tokens[(*index) - 2]);
        }
        exp = std::shared_ptr<expression>(new ternaryexpression(exp, o1, center, o2, right));
    } 
    return exp;
}

std::vector<std::shared_ptr<statement>> parser::parse(std::vector<std::shared_ptr<token>> &tokens)
{
    int index = 0;
    std::vector<std::shared_ptr<statement>> ret;
    try
    {
        while (!this->at_end(tokens, &index)) 
        {
            ret.push_back(this->declaration(tokens, &index));
        }
    }
    catch(const oexception &e)
    {
        std::cout << e << std::endl;
        throw oexception(oexception::PARSEERROR, e.to_string(), e.line());    
    }
    return ret;
}

std::shared_ptr<expression> parser::primary(std::vector<std::shared_ptr<token>> &tokens, int *index)
{
    /**
     * primary → NUMBER | STRING | "true" | "false" | "nil"
     *           "(" expression ")"; 
     */
    if (this->match(tokens, index, {FALSE})) 
    { 
        std::shared_ptr<object> value(new obool(false));
        return std::shared_ptr<expression>(new literalexpression(value));
    }
    
    if (this->match(tokens, index, {TRUE})) 
    { 
        std::shared_ptr<object> value(new obool(true));
        return std::shared_ptr<expression>(new literalexpression(value));
    }
    
    if (this->match(tokens, index, {NIL})) 
    { 
        std::shared_ptr<object> value(new onull());
        return std::shared_ptr<expression>(new literalexpression(value));
    }

    if (this->match(tokens, index, {NUMBER, STRING})) 
    {
        return std::shared_ptr<expression>(new literalexpression(tokens[(*index) - 1]->literal()));        
    }

    if (this->match(tokens, index, {IDENTIFIER})) 
    {
        return std::shared_ptr<expression>(new variableexpression(tokens[(*index) - 1]));
    }

    if (this->match(tokens, index, {LEFT_PAREN})) 
    {
        std::shared_ptr<expression> exp = this->expr(tokens, index);
        if (!this->match(tokens, index, {RIGHT_PAREN}))
        {
            this->error("Expected right parenthesis", tokens[(*index) - 2]);
        }
        return std::shared_ptr<expression>(new groupingexpression(exp));                     
    }    

    std::stringstream stream;
    stream << "Unexpected token " << tokens[(*index)]->to_string(); 
    this->error(stream.str(), tokens[(*index)]);

    return std::shared_ptr<expression>(nullptr);
}


std::shared_ptr<statement> parser::printstmt(std::vector<std::shared_ptr<token>> &tokens, int *index)
{
    std::shared_ptr<expression> exp = this->expr(tokens, index);
    if (!this->match(tokens, index, {SEMICOLON}))
    {
        this->error("Expected a ;", tokens[(*index)]);
    }

    return std::shared_ptr<statement>(new printstatement(exp));
}

void parser::synchronize(std::vector<std::shared_ptr<token>> &tokens, int *index)
{
    *index += 1;
    
    while (*index < tokens.size())
    {
        if (tokens[*index - 1]->get_token_type() == SEMICOLON)
        {
            return;
        }
        
        switch (tokens[*index]->get_token_type())
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

std::shared_ptr<expression> parser::term(std::vector<std::shared_ptr<token>> &tokens, int *index)
{
    /**
     * term → factor ( ( "-" | "+" ) factor )*;  
     */
    std::shared_ptr<expression> exp = this->factor(tokens, index);
    while (this->match(tokens, index, {MINUS, PLUS}))
    {
        std::shared_ptr<token> oper = tokens[(*index) - 1];
        std::shared_ptr<expression> right = this->factor(tokens, index);
        exp =  std::shared_ptr<expression>(new binaryexpression(exp, oper, right));
    }
    return exp;
}

std::shared_ptr<expression> parser::unary(std::vector<std::shared_ptr<token>> &tokens, int *index) 
{
    /**
     *  unary  → ( "!" | "-" ) unary
     *           | primary;
     */
    if (this->match(tokens, index, {BANG, MINUS}))
    {
        std::shared_ptr<token> oper = tokens[(*index) - 1];
        std::shared_ptr<expression> right = this->unary(tokens, index);
        return std::shared_ptr<expression>(new unaryexpression(oper, right));
    }
    return this->primary(tokens, index);
}