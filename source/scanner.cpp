#include "scanner.h"

scanner::scanner(std::string source):
    source(source),
    tokens()
{

}

scanner::~scanner() 
{

}

void scanner::add_token(tokentype token_type, int token_start, int current, int line_number) 
{
    std::string lexene = this->source.substr(token_start, current - token_start);
    token new_token(token_type, lexene, line_number);
    this->tokens.push_back(new_token);
}

// void scanner::add_token(tokentype token_type, int token_start, int current, int line_number) 
// {

// }

bool scanner::check_next(char c, int position)
{
    if (position + 1 < this->source.size())
    {
        return this->source[position + 1] == c;
    }
    return false;
}

bool scanner::scan_tokens()
{
    bool error           = false;
    int  token_start     = 0;
    int  source_position = 0;
    int  line_number     = 1;   

    while (source_position < this->source.size() && !error)
    {
        token_start = source_position;

        {
            char c = this->source[source_position];
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
                    if (this->check_next('=', source_position))
                    {
                        add_token(BANG_EQUAL, token_start, source_position++, line_number); 
                    }
                    else
                    {
                        add_token(BANG, token_start, source_position, line_number); 
                    }
                    break;
                }
                case '=':
                {
                    if (this->check_next('=', source_position))
                    {
                        add_token(EQUAL_EQUAL, token_start, source_position++, line_number); 
                    }
                    else
                    {
                        add_token(EQUAL, token_start, source_position, line_number); 
                    }
                    break;
                }
                case '<':
                {
                    if (this->check_next('=', source_position))
                    {
                        add_token(LESS_EQUAL, token_start, source_position++, line_number); 
                    }
                    else
                    {
                        add_token(LESS, token_start, source_position, line_number); 
                    }
                    break;
                }
                case '>':
                {
                    if (this->check_next('=', source_position))
                    {
                        add_token(GREATER_EQUAL, token_start, source_position++, line_number); 
                    }
                    else
                    {
                        add_token(GREATER, token_start, source_position, line_number); 
                    }
                    break;  
                } 
                case '/':
                {
                    if (this->check_next('/', source_position))
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
                    while (!this->check_next('\"', source_position))
                    {
                        
                    }
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
                    error = true;
                }            
            }
            ++source_position;
        }
    }
    return !error;
}