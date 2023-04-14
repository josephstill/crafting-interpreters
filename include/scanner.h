#include <string>
#include <vector>

#include "tokens.h"

class scanner
{
public:
    scanner(std::string source);
    ~scanner();
    bool scan_tokens();

private:
    void add_token(tokentype token_type, int token_start, int current, int line_number);
    //void add_token(tokentype token_type, int token_start, int current, int line_number);
    bool check_next(char c, int position);

    std::string             source;
    std::vector<token>      tokens; 
};