#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <memory>

#include "tokens/tokentype.h"
#include "types/object.h"

class token: public object
{

public:
    token(tokentype token_type, std::string lexene, int line_number, std::shared_ptr<object> data);
    token(const token &other);
    ~token();

    tokentype get_token_type() const { return this->token_type; }
    int line() const { return this->line_number; }
    std::shared_ptr<object> literal() { return this->opaque; }

    virtual std::string to_string() const;  

private:

    tokentype                   token_type;
    std::string                 lexene;
    int                         line_number;
    std::shared_ptr<object>     opaque;
};
  
#endif