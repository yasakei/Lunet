#include <iostream>
#include "Lexer.h"

Lexer::Lexer(std::string src) {
    source = src;
    pos = -1;
    current = ' ';
    Advance();
}

void Lexer::Advance() {
    pos += 1;
    current = source[pos];
}

TokenRet Lexer::MakeTokens() {
    std::vector<Token> tokens;

    while (current != ' ') {
        if (current == '\t') {
            Advance();
        } else if (DIGITS.find(current) != std::string::npos) {
            tokens.push_back(MakeNumber());
            Advance();
        } else if (current == '+') {
            tokens.push_back(Token(TokenType::PLUS));
            Advance();
        } else if (current == '-') {
            tokens.push_back(Token(TokenType::MINUS));
            Advance();
        } else if (current == '*') {
            tokens.push_back(Token(TokenType::MUL));
            Advance();
        } else if (current == '/') {
            tokens.push_back(Token(TokenType::DIV));
            Advance();
        } else if (current == '(') {
            tokens.push_back(Token(TokenType::LPAREN));
            Advance();
        } else if (current == ')') {
            tokens.push_back(Token(TokenType::RPAREN));
            Advance();
        } else {
            char ch = current;
            Advance();
            tokens.clear();

            IllegalCharacterError error = IllegalCharacterError(ch);
            error.hasError = true;

            return TokenRet(tokens, error);
        }
    }

    return TokenRet(tokens);
}

Token Lexer::MakeNumber() {
    std::string numStr = "";
    int dotCount = 0;

    while (current != ' ' && DIGITS.find(current+".") != std::string::npos) {
        if (current == '.') {
            if (dotCount == 1) break;
            dotCount += 1;
            numStr += ".";
        } else {
            numStr += current;
        }
    }

    if (dotCount == 0) {
        return Token(TokenType::INT, std::stoi(numStr));
    } else {
        return Token(TokenType::FLOAT, static_cast<float>(std::stof(numStr)));
    }
}