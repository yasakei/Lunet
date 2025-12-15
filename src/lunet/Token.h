#ifndef TOKEN_H
#define TOKEN_H

#include <any>
#include <string>

enum TokenType {
    IDENTIFIER,
    STRING,
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
    bool hasValue{false};
    Token() = default; 
    Token(TokenType t):type(t), hasValue(false){};
    Token(TokenType t, int v):type(t), value(v), hasValue(true){};
    Token(TokenType t, float v):type(t), value(v), hasValue(true){};
    Token(TokenType t, std::string v):type(t), value(v), hasValue(true){};
};

#endif