#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <memory>

#include "tokens/tokentype.h"
#include "types/object.h"

class token: public object
{

public:
    token(tokentype token_type, std::string lexene, int line_number, object *data);
    token(const token &other);
    ~token();

    virtual std::string to_string() const; 
    virtual std::string type_name() const;  

private:

    tokentype                   token_type;
    std::string                 lexene;
    int                         line_number;
    std::shared_ptr<object>     opaque;
};
  
#endif