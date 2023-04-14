#include "tokens.h"

token::token(tokentype token_type, std::string lexene, int line_number):
    token_type(token_type),
    lexene(lexene),
    line_number(line_number) 
{

}

token::token(const token &other):
    token_type(other.token_type),
    lexene(other.lexene),
    line_number(other.line_number) 
{

}

token::~token() 
{

}