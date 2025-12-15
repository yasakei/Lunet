#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <variant>
#include "Token.h"
#include <tuple>
#include <variant>
#include "Error.h"

struct TokenRet {
    std::vector<Token> tokens{};
    IllegalCharacterError error{};

    TokenRet() = default;
    TokenRet(std::vector<Token> tokens_):tokens(tokens_){};
    TokenRet(std::vector<Token> tokens_, IllegalCharacterError error_):tokens(tokens_), error(error_){};
};

class Lexer {
    public:
        Lexer(std::string src);
        void Advance();
        TokenRet MakeTokens();
        Token MakeNumber();

    private:
        std::string source;
        char current;
        int pos;
        const std::string DIGITS = "1234567890";
};

#endif