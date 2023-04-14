#include <string>
#include <vector>
#include <unordered_map>

#include "tokens.h"

class scanner
{
public:
    scanner(std::string source);
    ~scanner();
    bool error() const { return this->has_error; }

    friend std::ostream& operator<< (std::ostream& stream, const scanner& s);

private:
    void add_token(tokentype token_type, int token_start, int current, int line_number);
    void add_token(tokentype token_type, int token_start, int current, int line_number, void *opaque);
    bool check(char c, int position);
    bool is_alphabet(char c);
    bool is_alpha_numeric(char c);
    bool is_digit(char c);
    bool is_floating_point(char c);
    void scan_tokens();

    std::string                                       source;
    std::vector<token>                                tokens; 
    bool                                              has_error;
    static std::unordered_map<std::string, tokentype> keywords;
};