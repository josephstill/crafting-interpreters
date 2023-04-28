#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <vector>
#include <cstdarg>

#include "tokens/token.h"
#include "expression/expression.h"

class parser
{

public:

    parser(std::vector<std::shared_ptr<token>> &tokens);
    ~parser();
    bool error() const { return this->err; }
    std::shared_ptr<expression> parse();

private:
    std::shared_ptr<expression> comparison(int *index);
    std::shared_ptr<expression> equality(int *index);
    void error(std::string message, std::shared_ptr<token> tok);
    std::shared_ptr<expression> expr(int *index);
    std::shared_ptr<expression> factor(int *index);    
    bool match(int *index, std::initializer_list<tokentype> types);
    std::shared_ptr<expression> ternary(int *index);
    std::shared_ptr<expression> primary(int *index);
    void synchronize(int *index);
    std::shared_ptr<expression> term(int *index);
    std::shared_ptr<expression> unary(int *index);


    bool                                err;
    std::vector<std::shared_ptr<token>> &tokens;

};

#endif