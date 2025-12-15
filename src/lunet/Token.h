#ifndef TOKEN_H
#define TOKEN_H

#include <any>

enum TokenType {
    IDENTIFIER,
    LPAREN,
    RPAREN,
    INT,
    FLOAT,
    PLUS,
    MINUS,
    MUL,
    DIV
};

struct Token {
    std::any value{};
    TokenType type{};
    Token(TokenType t):type(t){};
    Token(TokenType t, int v):type(t), value(v){};
    Token(TokenType t, float v):type(t), value(v){};
};

#endif