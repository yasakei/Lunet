#include <iostream>
#include "Lexer.h"

Lexer::Lexer(std::string src) {
    source = src;
    pos = -1;
    current = '\0';
    Advance();
}

void Lexer::Advance() {
    pos += 1;
    current = source[pos];
}

TokenRet Lexer::MakeTokens() {
    std::vector<Token> tokens;

    while (current != '\0') {
        if (current == ' ' || current == '\t' || current == '\n' || current == '\r') {
            Advance();
        } else if (DIGITS.find(current) != std::string::npos) {
            tokens.push_back(MakeNumber());
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
        } else if (current == '"') { // Handle string literals
            Advance(); // Skip the opening quote
            std::string strValue = "";
            while (current != '\0' && current != '"') {
                strValue += current;
                Advance();
            }
            if (current == '"') {
                Advance(); // Skip the closing quote
            }
            tokens.push_back(Token(TokenType::STRING, strValue)); // Treat as string literal
        } else if (isalpha(current)) { // Handle identifiers and function calls
            std::string idStr = "";
            while (current != '\0' && (isalnum(current) || current == '_')) {
                idStr += current;
                Advance();
            }
            tokens.push_back(Token(TokenType::IDENTIFIER, idStr));
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

    while (current != ' ' && (DIGITS.find(current) != std::string::npos || current == '.')) {
        if (current == '.') {
            if (dotCount == 1) break;
            dotCount += 1;
            numStr += ".";
        } else {
            numStr += current;
        }
        Advance(); // Advance to the next character
    }

    if (dotCount == 0) {
        return Token(TokenType::INT, std::stoi(numStr));
    } else {
        return Token(TokenType::FLOAT, static_cast<float>(std::stof(numStr)));
    }
}