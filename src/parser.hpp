#pragma once
#include <cstdlib>
#include <iostream>
#include "tokenization.hpp"
#include <vector>


namespace node {

    struct Expr {
        Token int_lit;
    };
    
    struct Exit {
        Expr expr;
    };
}


class Parser {

public:
    inline explicit Parser(std::vector<Token> tokens)
        : m_tokens(std::move(tokens))
    {
    }  

    std::optional<node::Expr> parse_expr() {
        if (peek(1) && peek(1).value().type == TokenType::int_lit) {
            return node::Expr{.int_lit = consume()};
        } else {
            return {};
        }

    }
    
    inline node::Exit parse() {
        node::Exit exit_node;
        while(peek()) {
            if (peek().value().type == TokenType::exit) {
                if (auto expr = parse_expr()) {
                    exit_node = node::Exit{.expr = expr.value()};
                } else {
                    std::cerr << "You messed up at parsing\n";
                    exit(EXIT_FAILURE);
                }

                if (peek().value().type == TokenType::semi) {
                    consume();
                
                } else {
                    std::cerr << "You messed up at parsing2";
                    exit(EXIT_FAILURE);
                }
            }
            
        }
        return exit_node;
    }

private:
    [[nodiscard]] std::optional<Token> peek(const size_t n = 0) const {
        if (m_ind+n >= m_tokens.size()) {
            return {};
        } else {
            return m_tokens.at(m_ind);
        }
    }
    
    inline Token consume(const size_t n = 1) {
        Token token =  m_tokens.at(m_ind);
        m_ind = m_ind + n;
        return token;
    }
    
    const std::vector<Token> m_tokens;
    size_t m_ind = 0;
    
};
