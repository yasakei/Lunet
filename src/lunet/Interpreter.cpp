// yasakei
#include "Interpreter.h"
#include <iostream>

std::any Interpreter::Visit(std::shared_ptr<ASTNode> node) {
    if (auto numberNode = std::dynamic_pointer_cast<NumberNode>(node)) {
        return VisitNumberNode(numberNode);
    } else if (auto binaryOpNode = std::dynamic_pointer_cast<BinaryOpNode>(node)) {
        return VisitBinaryOpNode(binaryOpNode);
    } else if (auto functionCallNode = std::dynamic_pointer_cast<FunctionCallNode>(node)) {
        return VisitFunctionCallNode(functionCallNode);
    } else if (auto statementListNode = std::dynamic_pointer_cast<StatementListNode>(node)) {
        return VisitStatementListNode(statementListNode);
    }

    return std::any();
}

std::any Interpreter::VisitNumberNode(std::shared_ptr<NumberNode> node) {
    return node->value;
}

std::any Interpreter::VisitBinaryOpNode(std::shared_ptr<BinaryOpNode> node) {
    std::any leftValue = Visit(node->left);
    std::any rightValue = Visit(node->right);

    if (leftValue.type() == typeid(int) && rightValue.type() == typeid(int)) {
        int left = std::any_cast<int>(leftValue);
        int right = std::any_cast<int>(rightValue);

        switch (node->op) {
            case TokenType::PLUS:
                return std::any(left + right);
            case TokenType::MINUS:
                return std::any(left - right);
            case TokenType::MUL:
                return std::any(left * right);
            case TokenType::DIV:
                if (right != 0) {
                    return std::any(static_cast<float>(left) / right);
                } else {
                    std::cout << "Error: Division by zero" << std::endl;
                    return std::any(0);
                }
        }
    } else if (leftValue.type() == typeid(float) || rightValue.type() == typeid(float)) {
        float left = leftValue.type() == typeid(int) ?
                     static_cast<float>(std::any_cast<int>(leftValue)) :
                     std::any_cast<float>(leftValue);
        float right = rightValue.type() == typeid(int) ?
                      static_cast<float>(std::any_cast<int>(rightValue)) :
                      std::any_cast<float>(rightValue);

        switch (node->op) {
            case TokenType::PLUS:
                return std::any(left + right);
            case TokenType::MINUS:
                return std::any(left - right);
            case TokenType::MUL:
                return std::any(left * right);
            case TokenType::DIV:
                if (right != 0.0f) {
                    return std::any(left / right);
                } else {
                    std::cout << "Error: Division by zero" << std::endl;
                    return std::any(0.0f);
                }
        }
    }

    return std::any(0);
}

std::any Interpreter::VisitFunctionCallNode(std::shared_ptr<FunctionCallNode> node) {
    if (node->functionName == "print") {
        for (auto arg : node->arguments) {
            std::any value = Visit(arg);
            if (value.type() == typeid(int)) {
                std::cout << std::any_cast<int>(value) << std::endl;
            } else if (value.type() == typeid(float)) {
                std::cout << std::any_cast<float>(value) << std::endl;
            } else if (value.type() == typeid(std::string)) {
                std::cout << std::any_cast<std::string>(value) << std::endl;
            }
        }
        return std::any();
    }

    std::cout << "Unknown function: " << node->functionName << std::endl;
    return std::any();
}

std::any Interpreter::VisitStatementListNode(std::shared_ptr<StatementListNode> node) {
    for (auto statement : node->statements) {
        Visit(statement);  // Execute each statement
    }
    return std::any();  // Return empty any for statement lists
}