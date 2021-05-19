#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <cctype>
#include <iterator>

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

    // get symbol from current position
    const Token parseSymbol(Token& tk) const;
    // get number from current position
    const Token parseNumber(Token& tk) const;
    // get string from current position
    const Token parseString( Token& tk) const;

public:
    Lexer() { m_pos = m_rawString.begin();  }
    Lexer(std::string_view string) : m_rawString(string) { m_pos = m_rawString.begin(); }

    // read file content
    bool readFile(std::string_view fileName);
    
    // set lexer string
    void setString(std::string_view string) { m_rawString = string; m_pos = m_rawString.begin(); }

    // return Token structure from current index
    const Token next() const;
};