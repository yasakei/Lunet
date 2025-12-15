#include "Parser.h"
#include <iostream>
#include <any>
#include <memory>

struct ASTNode {
    virtual ~ASTNode() = default;
};

struct NumberNode : ASTNode {
    std::any value;
    NumberNode(std::any val) : value(val) {}
};

struct BinaryOpNode : ASTNode {
    std::shared_ptr<ASTNode> left;
    std::shared_ptr<ASTNode> right;
    TokenType op;
    BinaryOpNode(std::shared_ptr<ASTNode> l, TokenType operation, std::shared_ptr<ASTNode> r)
        : left(l), op(operation), right(r) {}
};

struct FunctionCallNode : ASTNode {
    std::string functionName;
    std::vector<std::shared_ptr<ASTNode>> arguments;
    FunctionCallNode(std::string name, std::vector<std::shared_ptr<ASTNode>> args)
        : functionName(name), arguments(args) {}
};

Parser::Parser(std::vector<Token> tokens_) {
    tokens = tokens_;
    pos = -1;
    Advance();
}

Token Parser::Advance() {
    pos++;
    if (pos < tokens.size()) {
        current = tokens[pos];
    } else {
        current = Token(TokenType::INT, 0);
    }
    return current;
}

ParseResult Parser::Parse() {
    ParseResult result = {ParseExpression(), IllegalCharacterError(), false};
    return result;
}

std::shared_ptr<ASTNode> Parser::ParseExpression() {
    std::shared_ptr<ASTNode> left = ParseTerm();

    while (current.type == TokenType::PLUS || current.type == TokenType::MINUS) {
        TokenType op = current.type;
        Advance();
        std::shared_ptr<ASTNode> right = ParseTerm();
        left = std::make_shared<BinaryOpNode>(left, op, right);
    }

    return left;
}

std::shared_ptr<ASTNode> Parser::ParseTerm() {
    std::shared_ptr<ASTNode> left = ParseFactor();

    while (current.type == TokenType::MUL || current.type == TokenType::DIV) {
        TokenType op = current.type;
        Advance();
        std::shared_ptr<ASTNode> right = ParseFactor();
        left = std::make_shared<BinaryOpNode>(left, op, right);
    }

    return left;
}

std::shared_ptr<ASTNode> Parser::ParseFactor() {
    Token token = current;

    if (token.type == TokenType::INT || token.type == TokenType::FLOAT) {
        Advance();
        return std::make_shared<NumberNode>(token.value);
    }
    else if (token.type == TokenType::STRING) {
        std::string strValue = std::any_cast<std::string>(token.value);
        Advance();
        return std::make_shared<NumberNode>(strValue);
    }
    else if (token.type == TokenType::IDENTIFIER) {
        std::string identifierName = std::any_cast<std::string>(token.value);
        Advance();

        if (current.type == TokenType::LPAREN) {
            Advance();

            std::vector<std::shared_ptr<ASTNode>> args;

            if (current.type != TokenType::RPAREN) {
                std::shared_ptr<ASTNode> arg = ParseExpression();
                if (arg) {
                    args.push_back(arg);
                }
            }

            if (current.type == TokenType::RPAREN) {
                Advance();
                return std::make_shared<FunctionCallNode>(identifierName, args);
            }
        }

        return nullptr;
    }

    return nullptr;
}