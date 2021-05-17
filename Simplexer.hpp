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
};

const static char* PRINTABLE_TYPES[] = {
    "END_OF_FILE",
    "INVALID",
    "INTEGER",
    "RATIONAL",
    "STRING",
    "SYMBOL"
};

struct Token {
    TokenType type = TokenType::INVALID;
    std::string line;
    std::string symbol;
};

class Lexer {
private:
    std::string m_rawString;
    mutable std::string::const_iterator m_pos;

private:

    // return string with symbol's line and row
    const std::string getSymbolLine() const;

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