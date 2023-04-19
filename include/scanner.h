#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include "tokens/token.h"
#include "types/object.h"

class scanner
{
public:
    scanner(std::string source);
    ~scanner();
    bool error() const { return this->has_error; }

    friend std::ostream& operator<< (std::ostream& stream, const scanner& s);

private:
    void add_token(tokentype token_type, int token_start, int current, int line_number);
    void add_token(tokentype token_type, int token_start, int current, int line_number, object *opaque);
    bool check(char c, int position);
    bool is_alphabet(char c);
    bool is_alpha_numeric(char c);
    bool is_digit(char c);
    void scan_tokens();

    std::string                                       source;
    std::vector<std::shared_ptr<token>>               tokens; 
    bool                                              has_error;
    static std::unordered_map<std::string, tokentype> keywords;
};

#endif