#pragma once
#include <cctype>
#include <string>
#include <optional>
#include <vector>
#include <regex>

enum class TokenType {
    exit,
    int_lit,
    semi,
};

struct Token {
    TokenType type;
    std::optional<std::string> value;
};


inline bool isNumber(const std::string& str) {
    static const std::regex pattern(R"(^-?\d+(\.\d+)?$)");
    return std::regex_match(str, pattern);
}

class Tokenizer {    
public:
    inline explicit Tokenizer(std::string src)
        : m_src(std::move(src))
    {
    }    


    inline std::vector<Token> tokenize() {
        std::vector<Token> tokens;
        std::string buf;

        while(peek()) {
            if (peek() == ';') {
                if (!buf.empty()) {
                    if (buf == "exit") {
                        tokens.push_back({.type = TokenType::exit});
                        buf.clear();
                    } else if (isNumber(buf)) {
                        tokens.push_back({.type = TokenType::int_lit,
                                         .value = buf});
                        buf.clear();
                    }
                }
                tokens.push_back({.type = TokenType::semi});
                consume();
            }
            else if (std::isalnum(peek().value()) ||
                peek().value() == '.' ||
                peek().value() == '-') {
                buf.push_back(consume());
            }
            else if (std::isspace(peek().value())) {
                if (!buf.empty()) {
                    if (buf == "exit") {
                        tokens.push_back({.type = TokenType::exit});
                        buf.clear();
                    } else if (isNumber(buf)) {
                        tokens.push_back({.type = TokenType::int_lit,
                                         .value = buf});
                        buf.clear();
                    }
                }
                consume();
            }
        }
        
        if (!buf.empty()){
            if (buf == "exit") {
                tokens.push_back({.type = TokenType::exit});
                buf.clear();
            }
            else if (isNumber(buf)) {
                tokens.push_back({.type = TokenType::int_lit, .value = buf});
                buf.clear();
            }
        }
        return tokens;
    }
    
private:
    
    [[nodiscard]] std::optional<char> peek() const {
        if (m_ind >= m_src.size()){
            return {};
        } else {
            return m_src.at(m_ind);
        }
    }
    char consume() {
        return m_src.at(m_ind++);
    } 
    const std::string m_src;
    size_t m_ind = 0;



        
};
