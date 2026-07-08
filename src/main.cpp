#include <cstdlib>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <vector>
#include <regex>



// Pour le lexing
enum class TokenType {
    _return,
    int_lit,
    semi,
};

struct Token {
    TokenType type;
    std::optional<std::string> value;
};



bool isNumber(const std::string& str) {
    std::regex pattern(R"(^-?\d+(\.\d+)?$)");

    return std::regex_match(str, pattern);
}


std::vector<Token> tokenize(const std::string& str) {
    std::vector<Token> tokens;
    std::string buf;
    for (char c : str) {
        if (c == ';') {
            if (!buf.empty()) {  
                if (buf == "return") {
                    tokens.push_back({.type = TokenType::_return});
                    buf = "";
                }
                else if (isNumber(buf)) {
                    tokens.push_back({.type = TokenType::int_lit, .value = buf});
                    buf = "";
                }
                buf.clear();
            }
            tokens.push_back({.type = TokenType::semi});
        }
        else if (std::isalnum(c) || c == '.' || c == '-') {
            buf.push_back(c);
        }
        else if (std::isspace(c)) {
            if (buf == "return") {
                tokens.push_back({.type = TokenType::_return});
                buf = "";
            }
            else if (isNumber(buf)) {
                tokens.push_back({.type = TokenType::int_lit, .value = buf});
                buf = "";
            }
        }
    }
    if (!buf.empty()) {
        if (buf == "return") {
            tokens.push_back({.type = TokenType::_return});
            buf = "";
        }
        else if (isNumber(buf)) {
            tokens.push_back({.type = TokenType::int_lit, .value = buf});
            buf = "";
        }
    }
    return tokens;
}

std::string tokens_to_asm(const std::vector<Token>& tokens) {
    std::string output;
    for 
}




int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Pas assez d'arguments.\n"
            << "comp <file>\n";
        return EXIT_FAILURE;
    }


    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Impossible d'ouvrirce fichier: "
            << argv[1] << '\n';
        return EXIT_FAILURE;
    }
    
    std::stringstream ss;
    ss << file.rdbuf();
    std::string str = ss.str();
        
    std::cout << argv[1]<< '\n';
    std::cout << str << std::endl;
    std::vector<Token> contents = tokenize(str);
    return EXIT_SUCCESS;
}


