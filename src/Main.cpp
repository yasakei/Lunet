#include <iostream>
#include <Lunet.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <any>

std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::IDENTIFIER: return "IDENTIFIER";
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
        for (auto& token: tokenRet.tokens) {
            std::cout << tokenTypeToString(token.type) << ", ";
            if (!token.hasValue) {
                std::cout << "NULL" << std::endl;
            } else {
                std::cout << anyToString(token.value) << std::endl;
            }
        }
    }

    return 0;
}