#include <iostream>
#include <Lunet.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    std::ifstream file(argv[1]);
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
        for (auto& token:tokenRet.tokens) {
            std::cout << token.type << ", " << token.value << std::endl;
        }
    }

    return 0;
}