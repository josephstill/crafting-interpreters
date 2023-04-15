#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <memory>

#include "tokentype.h"
#include "object.h"

class token
{

public:
    token(tokentype token_type, std::string lexene, int line_number, object *data);
    token(const token &other);
    ~token();

    friend std::ostream& operator<< (std::ostream& stream, const token& t);

private:

    tokentype                   token_type;
    std::string                 lexene;
    int                         line_number;
    std::shared_ptr<object>     opaque;
};
  
#endif