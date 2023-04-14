#include <cstdlib>
#include <iostream>

#include "scanner.h"


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
    add_token(token_type, token_start, current, line_number, NULL);
}

void scanner::add_token(tokentype token_type, int token_start, int current, int line_number, void *opaque) 
{
    std::string lexene = this->source.substr(token_start, current - token_start);
    token new_token(token_type, lexene, line_number, opaque);
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

bool scanner::is_floating_point(char c)
{
    return c >= '0' && c <= '9' || c == '.';        
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
                case '\"':
                {
                    int line_inc = 0;
                    while (source_position < this->source.size() && this->source[source_position] != '\"')
                    {
                        if (this->source[source_position] != '\n')
                        {
                            ++line_inc;
                        }
                        ++source_position;
                    }

                    if (source_position >= this->source.size())
                    {
                        this->has_error = true;
                    }

                    std::string literal = this->source.substr(token_start + 1, (source_position - token_start - 1));
                    add_token(STRING, token_start, source_position, line_number);

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
                        while (source_position + 1 <= this->source.size())
                        {
                            char next_c = this->source[source_position + 1];
                            ++source_position;
                            if (!is_floating_point(next_c))
                            {
                                break;
                            }
                        }

                        std::string floating_point_string = this->source.substr(token_start, source_position - token_start);
                        double *floating_point = (double *) malloc(sizeof(double));
                        *floating_point = std::stod(floating_point_string);
                        add_token(NUMBER, token_start, source_position, line_number, (void *) floating_point);
                    }
                    else if (is_alphabet(c))
                    {
                        while (source_position + 1 <= this->source.size())
                        {
                            char next_c = this->source[source_position + 1];
                            ++source_position;
                            if (!is_alpha_numeric(next_c))
                            {
                                break;
                            }
                        }   

                        std::string text = this->source.substr(token_start, source_position - token_start);
                        if (scanner::keywords.find(text) != scanner::keywords.end())
                        {
                            tokentype token_type = scanner::keywords[text]; 
                            add_token(token_type, token_start, source_position, line_number);
                        }                   
                    }
                    else
                    {
                        this->has_error = true;
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