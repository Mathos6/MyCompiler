#pragma once

#include "parser.hpp"
#include <sstream>
#include <string>



class Generator {

public:
    inline Generator(node::Exit root)
        : m_root(std::move(root))
    {
        
    }


    [[nodiscard]] std::string generate() const {
        std::stringstream output;
        output << ".global _start\n_start:\n";
        
        output << "\tmov x0, " << m_root.expr.int_lit.value.value()<< '\n'
            << "\tmov x8, #93\n\tsvc 0\n";


        return output.str();
    }



private:
    const node::Exit m_root;
    
};
