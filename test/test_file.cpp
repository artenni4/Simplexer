#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Simplexer.hpp"


std::string getTokenLine(const Simplexer::Token& tk) {
    std::stringstream ss;
    ss << '(' << tk.symbolLine << ':' << tk.symbolRow << ')';
    return ss.str();
}

void printTokens(const std::vector<Simplexer::Token>& ts) {
    for (auto iter = ts.begin(); iter != ts.end(); ++iter) {
        std::stringstream buff;

        // line
        buff << "Line: " << getTokenLine(*iter);
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
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        exit(-1);
	}
	
	Simplexer::Lexer lex;
	// try to read file
	if (lex.readFile(argv[1])) { // on success
        std::vector<Simplexer::Token> tokens;
        for (auto T = lex.next(); T.type != Simplexer::TokenType::END_OF_FILE; T = lex.next()) {
            tokens.emplace_back(T);
        }
        printTokens(tokens);
	}
	else { // on failure
		std::cout << "Failed to read file. Exiting..." << std::endl;
	}

	return 0;
}