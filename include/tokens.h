#include <string>
#include <memory>

enum tokentype 
{
  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
  COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

  BANG, BANG_EQUAL,
  EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL,
  LESS, LESS_EQUAL,

  IDENTIFIER, STRING, NUMBER,

  AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
  PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

  END
};

class tokendata 
{

public:
    
    tokendata(void *data);
    ~tokendata();
    void *data() { return this->opaque; }
    
private:    
    void *opaque;
};

class token
{

public:
    token(tokentype token_type, std::string lexene, int line_number, void *data);
    token(const token &other);
    ~token();

    friend std::ostream& operator<< (std::ostream& stream, const token& t);

private:

    tokentype                   token_type;
    std::string                 lexene;
    int                         line_number;
    std::shared_ptr<tokendata>  opaque;
};
  