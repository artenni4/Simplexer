#include <iostream>
#include <vector>
#include "Simplexer.hpp"

void printTokens(const std::vector<Simplexer::Token> ts) {
    for (auto iter = ts.begin(); iter != ts.end(); ++iter) {
        std::stringstream buff;

        // line
        buff << "Line: " << iter->line;
        while (buff.str().size() < 15) {
            buff << ' ';
        }

        // type
        buff << " Type: " << Simplexer::PRINTABLE_TYPES[static_cast<int>(iter->type)];
        while (buff.str().size() < 35) {
            buff << ' ';
        }
        
        // symbol
        buff << " Symbol: " << iter->symbol;

        std::cout << buff.str() << std::endl;
    }
}

int main(int argc, char** argv) {

    const char* fileName = "test.txt";
    Simplexer::Lexer lex;
    if (!lex.readFile(fileName)) {
        std::cerr << "Failed to read file " << fileName << std::endl;
        return -1;
    }
    else {
        std::cout << "File " << fileName << " was successfuly read" << std::endl;
    }

    bool err = false;
    std::vector<Simplexer::Token> ts;
    for (auto t = lex.next(); t.type != Simplexer::TokenType::END_OF_FILE; t = lex.next()) {
        ts.push_back(t);
        if (t.type == Simplexer::TokenType::INVALID) err = true;
    }

    printTokens(ts);

    if (err) {
        std::cout << "\n\nSome errors occured during analysis" << std::endl;
    }

    return 0;
}