#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <vector>
#include <cstdarg>

#include "tokens/token.h"
#include "expression/expression.h"
#include "statement/statement.h"

class parser
{

public:

    parser();
    ~parser();
    std::vector<std::shared_ptr<statement>> parse(std::vector<std::shared_ptr<token>> &tokens);

private:
    bool at_end(std::vector<std::shared_ptr<token>> &tokens, int *index) const;
    std::shared_ptr<expression> comparison(std::vector<std::shared_ptr<token>> &tokens, int *index);
    std::shared_ptr<expression> equality(std::vector<std::shared_ptr<token>> &tokens, int *index);
    void error(std::string message, std::shared_ptr<token> tok);
    std::shared_ptr<expression> expr(std::vector<std::shared_ptr<token>> &tokens, int *index);
    std::shared_ptr<statement> expressionstmt(std::vector<std::shared_ptr<token>> &tokens, int *index); 
    std::shared_ptr<expression> factor(std::vector<std::shared_ptr<token>> &tokens, int *index);    
    bool match(std::vector<std::shared_ptr<token>> &tokens, int *index, std::initializer_list<tokentype> types);
    std::shared_ptr<statement> stmt(std::vector<std::shared_ptr<token>> &tokens, int *index); 
    std::shared_ptr<expression> ternary(std::vector<std::shared_ptr<token>> &tokens, int *index);
    std::shared_ptr<expression> primary(std::vector<std::shared_ptr<token>> &tokens, int *index);
    std::shared_ptr<statement> printstmt(std::vector<std::shared_ptr<token>> &tokens, int *index); 
    void synchronize(std::vector<std::shared_ptr<token>> &tokens, int *index);
    std::shared_ptr<expression> term(std::vector<std::shared_ptr<token>> &tokens, int *index);
    std::shared_ptr<expression> unary(std::vector<std::shared_ptr<token>> &tokens, int *index);

    bool                                err;
};

#endif