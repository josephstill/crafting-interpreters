#include <cstdlib>
#include <sstream>

#include "tokens/token.h"


token::token(tokentype token_type, std::string lexene, int line_number, std::shared_ptr<object> opaque):
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

std::string token::to_string() const 
{
    std::stringstream stream;
    stream << this->lexene;
    return stream.str();
} 

std::string token::type_name() const 
{
    return "token";
}  