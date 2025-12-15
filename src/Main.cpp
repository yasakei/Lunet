#include <iostream>
#include <Lunet.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <any>
#include "lunet/Parser.h"
#include "lunet/Interpreter.h"

std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::STRING: return "STRING";
        case TokenType::LPAREN: return "LPAREN";
        case TokenType::RPAREN: return "RPAREN";
        case TokenType::INT: return "INT";
        case TokenType::FLOAT: return "FLOAT";
        case TokenType::PLUS: return "PLUS";
        case TokenType::MINUS: return "MINUS";
        case TokenType::MUL: return "MUL";
        case TokenType::DIV: return "DIV";
        default: return "UNKNOWN";
    }
}

std::string anyToString(const std::any& value) {
    if (value.type() == typeid(int)) {
        return std::to_string(std::any_cast<int>(value));
    } else if (value.type() == typeid(float)) {
        return std::to_string(std::any_cast<float>(value));
    } else if (value.type() == typeid(double)) {
        return std::to_string(std::any_cast<double>(value));
    } else if (value.type() == typeid(std::string)) {
        return std::any_cast<std::string>(value);
    } else {
        return "Unknown Value";
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cout << "Could not open file: " << argv[1] << std::endl;
        return 1;
    }

    std::stringstream buffer;
    char temp;

    while (file.get(temp)) {
        buffer << temp;
    }

    std::string lunet = buffer.str();

    Lexer lexer = Lexer(lunet);
    TokenRet tokenRet = lexer.MakeTokens();

    if (tokenRet.error.hasError) {
        std::cout << tokenRet.error.Get() << std::endl;
    } else {
        // Parse the tokens
        Parser parser(tokenRet.tokens);
        ParseResult parseResult = parser.Parse();

        if (parseResult.hasError) {
            std::cout << "Parse error occurred" << std::endl;
        } else if (parseResult.node) {
            // Interpret the result
            Interpreter interpreter;
            std::any result = interpreter.Visit(parseResult.node);
        } else {
            std::cout << "No AST node created - possibly a parsing issue" << std::endl;
        }
    }

    return 0;
};
