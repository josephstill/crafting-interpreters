#include <cstdlib>
#include <iostream>

#include "token.h"


token::token(tokentype token_type, std::string lexene, int line_number, object *opaque):
    token_type(token_type),
    lexene(lexene),
    line_number(line_number),
    opaque(opaque) 
{

}

token::token(const token &other):
    token_type(other.token_type),
    lexene(other.lexene),
    line_number(other.line_number),
    opaque(other.opaque) 
{

}

token::~token() 
{

}

std::ostream& operator<< (std::ostream& stream, const token& t)
{
    stream << t.line_number << ": " << t.lexene;
    return stream;
}