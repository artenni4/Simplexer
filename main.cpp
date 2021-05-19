#include <iostream>
#include "Simplexer.hpp"


int main(int argc, char** argv) {
    
    const char* fileName = "test.txt";
    Lexer lex;
    if (!lex.readFile(fileName)) {
        std::cerr << "Failed to read file " << fileName << std::endl;
    }
    else {
        std::cout << "Filed " << fileName << "was successfuly read" << std::endl;
    }
    

    for (auto t = lex.next(); t.type != TokenType::END_OF_FILE; t = lex.next()) {
        std::cout << "Type: " << PRINTABLE_TYPES[static_cast<int>(t.type)] << " Symbol: " << t.symbol << " Line: " << t.line << std::endl;
    }

    return 0;
}