#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

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
    std::string              token;
    std::vector<std::string> tokens;
    std::stringstream        reader(source);
    
    while (std::getline(reader, token, '\n')) 
    {
        tokens.push_back(token);
    }

    for (auto t = tokens.begin(); t != tokens.end(); ++t)
    {
        std::cout << *t << std::endl;
    }
    return 0;
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
    return 0;
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

    return -1;
}