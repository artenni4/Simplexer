#include "Simplexer.hpp"


int main(int argc, char** argv) {
    
    const char* fileName = "test.txt";
    Lexer lex;
    lex.readFile(fileName);

    for (auto t = lex.next(); t.type != TokenType::END_OF_FILE; t = lex.next()) {
        std::cout << "Type: " << PRINTABLE_TYPES[static_cast<int>(t.type)] << " Symbol: " << t.symbol << " Line: " << t.line << std::endl;
    }

    return 0;
}