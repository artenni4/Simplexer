#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <cctype>
#include <iterator>


// typedef not implemented ni

enum class TokenType {
    END_OF_FILE, // always in the end, controls flow
    INVALID, // set if lexer did not recognize symbol
    COMMENT, //ni
    // ===== data types ======
    INTEGER,
    RATIONAL,
    STRING,
    // == end of data types ==
    SYMBOL, // language symbol
    // ===== operators =======
    PLUS,
    PLUS_PLUS, // ni
    PLUS_EQUAL, // ni
    MINUS,
    MINUS_MINUS, // ni
    MINUS_EQUAL, // ni
    ASTERISK,
    ASTERISK_EQUAL, // ni
    SLASH,
    SLASH_EQUAL, // ni
    EQUAL, // ni
    DOUBLE_EQUAL, // ni
    LESS_THAN, // ni
    LESS_OR_EQUAL, // ni
    GREATER_THAN, //ni
    GREATER_OR_EQUAL, // ni
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
    void parseSymbol(Token& tk) const;
    // get number from current position
    void parseNumber(Token& tk) const;
    // get string from current position
    void parseString(Token& tk) const;
    // processes all signs, use to get any combination for token type
    void parseOperator(Token& tk) const;
    // get comment token
    void parseComment(Token& tk) const;

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