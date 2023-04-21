#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "scanner.h"
#include "types/oexception.h"

#define NO_ERROR      (0)
#define INPUT_ERROR   (-1)
#define SCANNER_ERROR (-2)

void usage()
{
    std::cout << "Usage: cpplox [script]" << std::endl;
}

void error_report(std::string message, std::string line, int line_number)
{
    std::cerr << message << std::endl << "[" << line_number << "]\t" << line << std::endl;
}

int run(std::string source)
{
    try
    {
        scanner sc(source);
        if (sc.error()) return SCANNER_ERROR;
        std::cout << sc;
    }
    catch (oexceprion e)
    {
        std::cout << e << std::endl;
    }
    return NO_ERROR;
}

int run_file(char *file_path)
{

    std::ifstream source_file(file_path);   
    std::string   source((std::istreambuf_iterator<char>(source_file)), std::istreambuf_iterator<char>());
    return run(source);
}

int run_prompt()
{
    std::string source;
    while (true)
    {
        std::cout << "> ";
        getline(std::cin, source);
        run(source);
    }
    return NO_ERROR;
}

int main(int argc, char **argv)
{
    if (argc > 2)
    {
        usage();
    }
    else if ( argc == 2)
    {
        return run_file(argv[1]);
    }
    else
    {
        return run_prompt();
    }

    return INPUT_ERROR;
}