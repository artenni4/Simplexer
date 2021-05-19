#include <iostream>
#include <vector>
#include "Simplexer.hpp"


int main(int argc, char** argv) {
    
    const char* fileName = "test.txt";
    Lexer lex;
    if (!lex.readFile(fileName)) {
        std::cerr << "Failed to read file " << fileName << std::endl;
        return -1;
    }
    else {
        std::cout << "File " << fileName << " was successfuly read" << std::endl;
    }
    
    std::vector<Token> ts;
    for (Token t = lex.next(); t.type != TokenType::END_OF_FILE; t = lex.next()) {
        ts.push_back(t);
    }

    for (auto iter = ts.begin(); iter != ts.end(); ++iter) {
        std::cout << "Type: " << PRINTABLE_TYPES[static_cast<int>(iter->type)] << " Symbol: " << iter->symbol << " Line: " << iter->line << std::endl;
    }

    return 0;
}