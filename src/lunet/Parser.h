//yasakei
#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>
#include "Token.h"
#include "Error.h"

struct ASTNode;
struct StatementListNode;  

struct ParseResult {
    std::shared_ptr<ASTNode> node;
    IllegalCharacterError error;
    bool hasError = false;
};

class Parser {
public:
    Parser(std::vector<Token> tokens_);

    ParseResult Parse();
    std::vector<std::shared_ptr<ASTNode>> ParseStatements();

private:
    std::vector<Token> tokens;
    int pos = -1;
    Token current;

    Token Advance();
    std::shared_ptr<ASTNode> ParseExpression();
    std::shared_ptr<ASTNode> ParseTerm();
    std::shared_ptr<ASTNode> ParseFactor();
};

#endif