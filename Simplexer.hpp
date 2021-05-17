#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cctype>

enum class TokenType {
    END_OF_FILE, // always in the end, controls flow
    INVALID, // set if lexer did not recognize symbol
    // ===== data types ======
    INTEGER,
    RATIONAL,
    STRING,
    // == end of data types ==
    SYMBOL, // language symbol
    // ===== operators =======
    PLUS,
    MINUS,
    ASTERISK,
    SLASH,
    COMMA,
    // === end of operators ==
    // ===== separators ======
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

const static char* PRINTABLE_TYPES[] = {
    "END_OF_FILE",
    "INVALID",
    "INTEGER",
    "RATIONAL",
    "STRING",
    "SYMBOL",
    "PLUS",
    "MINUS",
    "ASTERISK",
    "SLASH",
    "COMMA",
    "SEMICOLON",
    "COLON",
    "LEFT_PARAN",
    "RIGHT_PARAN",
    "LEFT_SQUARE",
    "RIGHT_SQUARE",
    "LEFT_CURLY",
    "RIGHT_CURLY",
};

struct Token {
    TokenType type = TokenType::INVALID;
    std::string line;
    std::string symbol;
};

class Lexer {
private:
    std::string m_rawString; // string to analyze
    mutable std::string::const_iterator m_pos; // current lexer position in string

private:

    // return string with symbol's line and row
    const std::string getSymbolLine() const;

    // get Token with type SYMBOL from current position
    const Token parseSymbol() const;
    // get Token with type INTEGER or RATIONAL from current position
    const Token parseNumber() const;
    // get Token with type STRING from current position
    const Token parseString() const;

public:
    Lexer() { m_pos = m_rawString.begin();  }
    Lexer(std::string_view string) : m_rawString(string) { m_pos = m_rawString.begin(); }

    // read file content
    void readFile(std::string_view fileName);
    
    // set lexer string
    void setString(std::string_view string) { m_rawString = string; m_pos = m_rawString.begin(); }

    // return Token structure from curr index
    const Token next() const;
};