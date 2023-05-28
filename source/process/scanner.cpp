#include <cstdlib>
#include <iostream>

#include "process/scanner.h"
#include "types/odouble.h"
#include "types/ostring.h"
#include "types/oexception.h"


std::unordered_map<std::string, tokentype> scanner::keywords = 
{
    {"and",    AND},
    {"class",  CLASS},
    {"else",   ELSE},
    {"false",  FALSE},
    {"for",    FOR},
    {"fun",    FUN},
    {"if",     IF},
    {"nil",    NIL},
    {"or",     OR},
    {"print",  PRINT},
    {"return", RETURN},
    {"super",  SUPER},
    {"this",   THIS},
    {"true",   TRUE},
    {"var",    VAR},
    {"while",  WHILE},
};

scanner::scanner(std::string source):
    source(source),
    tokens(),
    has_error(false)
{
    scan_tokens();
}

scanner::~scanner() 
{

}

void scanner::add_token(tokentype token_type, int token_start, int current, int line_number) 
{
    add_token(token_type, token_start, current, line_number, nullptr);
}

void scanner::add_token(tokentype token_type, int token_start, int current, int line_number, object *opaque) 
{
    std::shared_ptr<object> o_ptr(opaque);
    std::string lexene = this->source.substr(token_start, current - token_start);
    std::shared_ptr<token> new_token(new token(token_type, lexene, line_number, o_ptr));
    this->tokens.push_back(new_token);
}

bool scanner::check(char c, int position)
{
    if (position < this->source.size())
    {
        return this->source[position] == c;
    }
    return false;
}

bool scanner::is_alphabet(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');   
}

bool scanner::is_alpha_numeric(char c)
{
    return is_alphabet(c) || is_digit(c);
}

bool scanner::is_digit(char c)
{
    return c >= '0' && c <= '9';
}

void scanner::scan_tokens()
{
    bool error           = false;
    int  token_start     = 0;
    int  source_position = 0;
    int  line_number     = 1;   

    while (source_position < this->source.size() && !this->has_error)
    {
        token_start = source_position;

        {
            char c = this->source[source_position];
            ++source_position;
            switch (c)
            {
                case '(': 
                {
                    add_token(LEFT_PAREN, token_start, source_position, line_number); 
                    break;
                }
                case ')': 
                {
                    add_token(RIGHT_PAREN, token_start, source_position, line_number); 
                    break;
                }
                case '{': 
                {
                    add_token(LEFT_BRACE, token_start, source_position, line_number); 
                    break;
                }
                case '}': 
                {
                    add_token(RIGHT_BRACE, token_start, source_position, line_number); 
                    break;
                }
                case ',': 
                {
                    add_token(COMMA, token_start, source_position, line_number); 
                    break;
                }
                case '.': 
                {
                    add_token(DOT, token_start, source_position, line_number); 
                    break;
                }
                case '-': 
                {
                    add_token(MINUS, token_start, source_position, line_number); 
                    break;
                }
                case '+': 
                {
                    add_token(PLUS, token_start, source_position, line_number); 
                    break;
                }
                case ';': 
                {
                    add_token(SEMICOLON, token_start, source_position, line_number); 
                    break;
                }
                case '*': 
                {
                    add_token(STAR, token_start, source_position, line_number); 
                    break;
                } 
                case '?':
                {
                    add_token(QUESTION, token_start, source_position, line_number); 
                    break;
                }
                case ':':
                {
                    add_token(COLON, token_start, source_position, line_number); 
                    break;
                }
                case '!':
                {
                    if (this->check('=', source_position))
                    {
                        add_token(BANG_EQUAL, token_start, ++source_position, line_number); 
                    }
                    else
                    {
                        add_token(BANG, token_start, source_position, line_number); 
                    }
                    break;
                }
                case '=':
                {
                    if (this->check('=', source_position))
                    {
                        add_token(EQUAL_EQUAL, token_start, ++source_position, line_number); 
                    }
                    else
                    {
                        add_token(EQUAL, token_start, source_position, line_number); 
                    }
                    break;
                }
                case '<':
                {
                    if (this->check('=', source_position))
                    {
                        add_token(LESS_EQUAL, token_start, ++source_position, line_number); 
                    }
                    else
                    {
                        add_token(LESS, token_start, source_position, line_number); 
                    }
                    break;
                }
                case '>':
                {
                    if (this->check('=', ++source_position))
                    {
                        add_token(GREATER_EQUAL, token_start, ++source_position, line_number); 
                    }
                    else
                    {
                        add_token(GREATER, token_start, source_position, line_number); 
                    }
                    break;  
                } 
                case '/':
                {
                    if (this->check('/', source_position))
                    {
                        while(source_position < this->source.size() && this->source[source_position] != '\n')
                        {
                            ++source_position;
                        }
                    }    
                    else
                    {
                        add_token(SLASH, token_start, source_position, line_number);
                    }
                    break;
                }
                case '"':
                {
                    int line_inc = 0;
                    while (source_position <= this->source.size())
                    {
                        char next_c = this->source[source_position];  
                        ++source_position;
            
                        if (next_c == '\n')
                        {
                            ++line_inc;
                        }
                        else if (next_c == '"')
                        {
                            break;
                        }
                    }

                    if (source_position > this->source.size())
                    {
                        this->has_error = true;
                        throw oexceprion(oexceprion::SCANERROR, "There is an unterminated string.", line_number);
                    }

                    std::string literal = this->source.substr(token_start + 1, (source_position - token_start - 2));
                    ostring *s = new ostring(literal);
                    add_token(STRING, token_start, source_position, line_number, s);

                    line_number += line_inc;
                    break;
                }
                case ' ':
                case '\r':
                case '\t':
                    break;
                case '\n':
                    ++line_number;
                    break;                
                default:
                {
                    if (is_digit(c))
                    {
                        while (source_position <= this->source.size())
                        {
                            char next_c = this->source[source_position];                           
                            if (!is_digit(next_c))
                            {
                                --source_position;
                                break;
                            }
                            ++source_position;
                        }
                        
                        if (source_position <= this->source.size()) 
                        {
                            char next_c = this->source[source_position];
                            ++source_position;                             
                            if (next_c == '.')
                            {
                                while (source_position <= this->source.size())
                                {
                                    next_c = this->source[source_position]; 
                                    if (!is_digit(next_c))
                                    {
                                        --source_position;
                                        break;
                                    }
                                    ++source_position;
                                }                             
                            }
                        } 
                    
                        std::string floating_point_string = this->source.substr(token_start, source_position - token_start);
                        odouble *d = new odouble(floating_point_string);

                        add_token(NUMBER, token_start, source_position, line_number, d);
                    }
                    else if (is_alphabet(c))
                    {
                        while (source_position <= this->source.size())
                        {
                            char next_c = this->source[source_position];
                            ++source_position;
                            if (!is_alpha_numeric(next_c))
                            {
                                --source_position;
                                break;
                            }
                        }   

                        std::string text = this->source.substr(token_start, source_position - token_start);
                        if (scanner::keywords.find(text) != scanner::keywords.end())
                        {
                            tokentype token_type = scanner::keywords[text]; 
                            add_token(token_type, token_start, source_position, line_number);
                        } 
                        else
                        {
                            std::string literal = this->source.substr(token_start, source_position - token_start);
                            ostring *s = new ostring(literal);
                            add_token(STRING, token_start, source_position, line_number, s);
                        }                  
                    }
                    else
                    {
                        this->has_error = true;
                        throw oexceprion(oexceprion::SCANERROR, "There was an unknown token", line_number);
                    }
                }            
            }
        }
    }
}

std::ostream& operator<< (std::ostream& stream, const scanner& s)
{
    if (s.error())
    {
        stream << "[ERROR]" << std::endl;
    }

    for (auto it = s.tokens.begin(); it != s.tokens.end(); ++it)
    {
        stream << *it << std::endl;
    }

    return stream;
}