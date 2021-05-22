#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <cctype>
#include <iterator>

namespace Simplexer {

    // All possible token types
    enum class TokenType {
        END_OF_FILE, // always in the end, controls flow
        INVALID, // set if lexer did not recognize symbol
        COMMENT,
        // ===== data types ======
        INTEGER,
        RATIONAL,
        STRING,
        // == end of data types ==
        SYMBOL, // language symbol
        // ===== operators =======
        PLUS,
        PLUS_PLUS,
        PLUS_EQUAL,
        MINUS,
        MINUS_MINUS,
        MINUS_EQUAL,
        ASTERISK,
        ASTERISK_EQUAL,
        SLASH,
        SLASH_EQUAL,
        EQUAL,
        DOUBLE_EQUAL,
        LESS_THAN,
        LESS_OR_EQUAL,
        GREATER_THAN,
        GREATER_OR_EQUAL,
        // === end of operators ==
        // ===== separators ======
        COMMA,
        POINT,
        SEMICOLON,
        COLON,
        LEFT_PARAN,
        RIGHT_PARAN,
        LEFT_SQUARE,
        RIGHT_SQUARE,
        LEFT_CURLY,
        RIGHT_CURLY,
        // === end of separatos ==
    };

    // use for printing enum values
    // by passing enum's value as index to the array
    const static char* PRINTABLE_TYPES[] = {
        "END_OF_FILE",
        "INVALID",
        "COMMENT",
        "INTEGER",
        "RATIONAL",
        "STRING",
        "SYMBOL",
        "PLUS",
        "PLUS_PLUS",
        "PLUS_EQUAL",
        "MINUS",
        "MINUS_MINUS",
        "MINUS_EQUAL",
        "ASTERISK",
        "ASTERISK_EQUAL",
        "SLASH",
        "SLASH_EQUAL",
        "EQUAL",
        "DOUBLE_EQUAL",
        "LESS_THAN",
        "LESS_OR_EQUAL",
        "GREATER_THAN",
        "GREATER_OR_EQUAL",
        "COMMA",
        "POINT",
        "SEMICOLON",
        "COLON",
        "LEFT_PARAN",
        "RIGHT_PARAN",
        "LEFT_SQUARE",
        "RIGHT_SQUARE",
        "LEFT_CURLY",
        "RIGHT_CURLY",
    };

    // Token class
    // Holds everything needed for token
    struct Token {
        TokenType type = TokenType::INVALID;
        std::string line;
        std::string symbol;
    };

    // Class that represents lexical analyzer
    class Lexer {
    private:
        std::string m_rawString; // string to analyze
        mutable std::string::const_iterator m_pos; // current lexer position in string

    private:

        // return string with symbol's line and row
        const std::string getSymbolLine() const;

        // get symbol from current position
        void parseSymbol(Token&) const;
        // get number from current position
        void parseNumber(Token&) const;
        // get string from current position
        void parseString(Token&) const;
        // processes all signs, use to get any combination for token type
        void parseOperator(Token&) const;
        // get comment token
        void parseComment(Token&) const;

    public:
        Lexer();
        Lexer(std::string_view);

        // read file content
        bool readFile(std::string_view);

        // set lexer string
        void setString(std::string_view);

        // return Token structure from current index
        const Token next() const;
    };

}