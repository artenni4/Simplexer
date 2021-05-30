#include "Simplexer.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"


TEST_CASE("Tokenize integer values", "[integer]") {
    Simplexer::Lexer lex("123456789");
    auto t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::INTEGER);
    REQUIRE(t.symbol == "123456789");
}

TEST_CASE("Tokenize rational values", "[rational]") {
    Simplexer::Lexer lex("123456789.123456789 .123 123. .");
    auto t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::RATIONAL);
    REQUIRE(t.symbol == "123456789.123456789");

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::RATIONAL);
    REQUIRE(t.symbol == ".123");

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::RATIONAL);
    REQUIRE(t.symbol == "123.");

    t = lex.next();
    REQUIRE(t.type != Simplexer::TokenType::RATIONAL);
    REQUIRE(t.symbol.empty() == true);
}

TEST_CASE("Tokenize string", "[string]") {
    Simplexer::Lexer lex("\"hello\" 'hello' 'hell\\'o'");
    auto t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::STRING);
    REQUIRE(t.symbol == "hello");

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::STRING);
    REQUIRE(t.symbol == "hello");

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::STRING);
    REQUIRE(t.symbol == "hell'o");
}

TEST_CASE("Tokenize symbols, comments, etc.", "[other]") {
    Simplexer::Lexer lex("abc //variable");
    auto t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::SYMBOL);
    REQUIRE(t.symbol == "abc");

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::COMMENT);
    REQUIRE(t.symbol == "variable");

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::END_OF_FILE);
    REQUIRE(t.symbol.empty() == true);
}

TEST_CASE("Tokenize operators", "[operator]") {
    Simplexer::Lexer lex("+ ++ += - -- -= * *= / /= < <= > >= = ==");
    auto t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::PLUS);
    REQUIRE(t.symbol.empty() == true);

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::PLUS_PLUS);
    REQUIRE(t.symbol.empty() == true);

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::PLUS_EQUAL);
    REQUIRE(t.symbol.empty() == true);

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::MINUS);
    REQUIRE(t.symbol.empty() == true);

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::MINUS_MINUS);
    REQUIRE(t.symbol.empty() == true);

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::MINUS_EQUAL);
    REQUIRE(t.symbol.empty() == true);

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::ASTERISK);
    REQUIRE(t.symbol.empty() == true);

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::ASTERISK_EQUAL);
    REQUIRE(t.symbol.empty() == true);

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::SLASH);
    REQUIRE(t.symbol.empty() == true);

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::SLASH_EQUAL);
    REQUIRE(t.symbol.empty() == true);

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::LESS_THAN);
    REQUIRE(t.symbol.empty() == true);

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::LESS_OR_EQUAL);
    REQUIRE(t.symbol.empty() == true);

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::GREATER_THAN);
    REQUIRE(t.symbol.empty() == true);

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::GREATER_OR_EQUAL);
    REQUIRE(t.symbol.empty() == true);

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::EQUAL);
    REQUIRE(t.symbol.empty() == true);

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::DOUBLE_EQUAL);
    REQUIRE(t.symbol.empty() == true);
}

TEST_CASE("Tokenize separators", "[separator]") {
    Simplexer::Lexer lex(", . : ; ( ) { } [ ]");
    auto t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::COMMA);
    REQUIRE(t.symbol.empty() == true);

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::POINT);
    REQUIRE(t.symbol.empty() == true);

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::COLON);
    REQUIRE(t.symbol.empty() == true);

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::SEMICOLON);
    REQUIRE(t.symbol.empty() == true);

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::LEFT_PARAN);
    REQUIRE(t.symbol.empty() == true);

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::RIGHT_PARAN);
    REQUIRE(t.symbol.empty() == true);

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::LEFT_CURLY);
    REQUIRE(t.symbol.empty() == true);

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::RIGHT_CURLY);
    REQUIRE(t.symbol.empty() == true);

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::LEFT_SQUARE);
    REQUIRE(t.symbol.empty() == true);

    t = lex.next();
    REQUIRE(t.type == Simplexer::TokenType::RIGHT_SQUARE);
    REQUIRE(t.symbol.empty() == true);
}