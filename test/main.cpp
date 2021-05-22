#include "../Simplexer.hpp"
#include <iostream>
#include <vector>

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

template <class T, class U>
bool CHECK_EQUAL(const T& expr, const U& eq, std::string_view description = "") {
    std::cout << "Test " << description << " : ";
    if (expr != eq) {
        std::cout << "Failed" << std::endl;
        return false;
    }
    else {
        std::cout << "OK" << std::endl;
        return true;
    }
}

void fileScanTest() {
    const char* fileName = "test.txt";
    Simplexer::Lexer lex;

    if (!lex.readFile(fileName)) {
        std::cerr << "Failed to read file " << fileName << std::endl;
        return;
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
}

void typeAndSymbolsTest() {
    Simplexer::Lexer lex;
    Simplexer::Token t;

    lex.setString("123");
    t = lex.next();
    CHECK_EQUAL(t.type, Simplexer::TokenType::INTEGER, "integer type");
    CHECK_EQUAL(t.symbol, "123", "integer symbol");

    lex.setString("'hello'");
    t = lex.next();
    CHECK_EQUAL(t.type, Simplexer::TokenType::STRING, "string type");
    CHECK_EQUAL(t.symbol, "hello", "string symbol");

    lex.setString("'abc \\' def\\g'");
    t = lex.next();
    CHECK_EQUAL(t.type, Simplexer::TokenType::STRING, "string with back slash");
    CHECK_EQUAL(t.symbol, "abc ' def\\g", "string with back slash symbol");

    lex.setString("12.355");
    t = lex.next();
    CHECK_EQUAL(t.type, Simplexer::TokenType::RATIONAL, "rational type");
    CHECK_EQUAL(t.symbol, "12.355", "rational symbol");

    lex.setString("+-*/");
    t = lex.next();
    CHECK_EQUAL(t.type, Simplexer::TokenType::PLUS, "plus operator");

    t = lex.next();
    CHECK_EQUAL(t.type, Simplexer::TokenType::MINUS, "minus operator");

    t = lex.next();
    CHECK_EQUAL(t.type, Simplexer::TokenType::ASTERISK, "asterisk operator");

    t = lex.next();
    CHECK_EQUAL(t.type, Simplexer::TokenType::SLASH, "slash operator");

    
    lex.setString("++ += -- -= *= /=");
    t = lex.next();
    CHECK_EQUAL(t.type, Simplexer::TokenType::PLUS_PLUS, "plus plus operator");

    t = lex.next();
    CHECK_EQUAL(t.type, Simplexer::TokenType::PLUS_EQUAL, "plus equal operator");

    t = lex.next();
    CHECK_EQUAL(t.type, Simplexer::TokenType::MINUS_MINUS, "minus minus operator");

    t = lex.next();
    CHECK_EQUAL(t.type, Simplexer::TokenType::MINUS_EQUAL, "minus equal operator");

    t = lex.next();
    CHECK_EQUAL(t.type, Simplexer::TokenType::ASTERISK_EQUAL, "asterisk equal operator");

    t = lex.next();
    CHECK_EQUAL(t.type, Simplexer::TokenType::SLASH_EQUAL, "slash equal operator");


    // TODO other cases
}

int main(int argc, char** argv) {

    typeAndSymbolsTest();

    //fileScanTest();

    return 0;
}