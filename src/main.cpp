#include <cstdlib>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <vector>

#include "tokenization.hpp"
#include "parser.hpp"
#include "generation.hpp"


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

    Parser parser(std::move(tokens));
    node::Exit tree = parser.parse();
    Generator generator(std::move(tree));
    {
        std::ofstream fileOut("asm.s");
        fileOut << generator.generate();
    }
    system("aarch64-linux-gnu-as asm.s -o asm.o");
    system("aarch64-linux-gnu-ld asm.o -o exec");
    return EXIT_SUCCESS;
}




