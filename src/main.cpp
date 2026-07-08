#include <cstdlib>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <vector>

#include "tokenization.hpp"


std::string tokens_to_asm(const std::vector<Token>& tokens) {
    std::stringstream output;
    output << ".global _start\n_start:\n";
    for (int i = 0; i+2 < tokens.size(); ++i) {
        if (tokens.at(i).type == TokenType::exit &&
            tokens.at(i+1).type == TokenType::int_lit &&
            tokens.at(i+2).type == TokenType::semi) {
            output << "\tmov x0, "<< tokens.at(i+1).value.value()<< '\n'
                << "\tmov x8, #93\n\tsvc 0\n";
        }
    }
    return output.str();
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Pas assez d'arguments.\n"
            << "comp <file>\n";
        return EXIT_FAILURE;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Impossible d'ouvrir ce fichier: "
            << argv[1] << '\n';
        return EXIT_FAILURE;
    }
    
    std::stringstream ss;
    ss << file.rdbuf();
    std::string code_source = ss.str();
        
    std::cout << argv[1]<< '\n';
    std::cout << code_source << std::endl;
    Tokenizer tokenizer(std::move(code_source));
    std::vector<Token> tokens = tokenizer.tokenize();
    {
        std::ofstream fileOut("asm.s");
        std::cout << tokens_to_asm(tokens);
        fileOut << tokens_to_asm(tokens);
    }
    system("aarch64-linux-gnu-as asm.s -o asm.o");
    system("aarch64-linux-gnu-ld asm.o -o exec");
    return EXIT_SUCCESS;
}




