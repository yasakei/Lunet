//yasakei
#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Parser.h"
#include <map>
#include <string>
#include <any>

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

struct StatementListNode : ASTNode {
    std::vector<std::shared_ptr<ASTNode>> statements;
    StatementListNode(std::vector<std::shared_ptr<ASTNode>> stmts)
        : statements(stmts) {}
};

class Interpreter {
public:
    std::any Visit(std::shared_ptr<ASTNode> node);

    std::any VisitNumberNode(std::shared_ptr<NumberNode> node);
    std::any VisitBinaryOpNode(std::shared_ptr<BinaryOpNode> node);
    std::any VisitFunctionCallNode(std::shared_ptr<FunctionCallNode> node);
    std::any VisitStatementListNode(std::shared_ptr<StatementListNode> node);

private:
    std::map<std::string, std::any> variables;
};

#endif