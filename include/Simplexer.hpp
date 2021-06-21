#pragma once

#include <string>
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
        std::string symbol;
        std::size_t symbolRow;
        std::size_t symbolLine;
    };

    // Class that represents lexical analyzer
    class Lexer {
    private:
        std::string m_rawString; // string to analyze
        mutable Token m_currToken; // current Token to return 
        mutable std::string::const_iterator m_pos; // current lexer position in string

    private:

        // return string with symbol's line and row
        void Lexer::getSymbolLine() const {
            std::size_t row = 0, line = 1; // start line from 1, not from 0
            std::string::const_iterator lastNl = m_rawString.begin(); // last new line

            for (std::string::const_iterator it = m_rawString.begin(); it != m_pos; ++it) {
                if (*it == '\n') {
                    line++;
                    lastNl = it + 1; // skip \n character
                }
            }
            row = m_pos - lastNl + 1; // shift one char to right, so first is 1 but not 0

            m_currToken.symbolLine = line;
            m_currToken.symbolRow = row;
        }

        // get symbol from current position
        void Lexer::parseSymbol() const
        {
            m_currToken.type = TokenType::SYMBOL;
            // fill in string for token
            while (std::isalpha(*m_pos) || std::isdigit(*m_pos) || *m_pos == '_') {
                m_currToken.symbol += *m_pos++;
            }
            --m_pos; // return to the last character
        }
        // get number from current position
        void Lexer::parseNumber() const
        {
            // get all digits and skip if point is on the first place
            while (std::isdigit(*m_pos)) {
                m_currToken.symbol += *m_pos++;
            }

            // check for point after previous loop
            if (*m_pos == '.') { // add point to symbol string and define type as RATIONAL
                m_currToken.symbol += *m_pos++;
                while (std::isdigit(*m_pos)) {
                    m_currToken.symbol += *m_pos++;
                }
                m_currToken.type = TokenType::RATIONAL;
            }
            else { // if there is no point then type is INTEGER
                m_currToken.type = TokenType::INTEGER;
            }
            --m_pos; // return to the last character
        }
        // get string from current position
        void Lexer::parseString() const {
            m_currToken.type = TokenType::STRING;
            // remember starting quote and fill string to same quote
            char quote = *m_pos++;

            while (true) {
                if (*m_pos == quote) {
                    break;
                }
                else if (*m_pos == '\n' || *m_pos == '\0') {
                    // do not skip ending quote 
                    // because parse functions should stop on last character
                    --m_pos;

                    // if current position is end of file or new line
                    // this means that we have overhead of the string on one charcter
                    // so go back for one position
                    m_currToken.type = TokenType::INVALID;
                    break;
                }
                else if (*m_pos == '\\') { // if encounter backslash
                    if (*(m_pos + 1) == quote) { // and next char is quote parseString started with
                        // then swallow this quote
                        m_currToken.symbol += *++m_pos;
                        ++m_pos; // skip the quote
                    }
                    else {
                        m_currToken.symbol += *m_pos++;
                    }
                }
                else {
                    m_currToken.symbol += *m_pos++;
                }
            }
        }
        // processes all signs, use to get any combination for token type
        void Lexer::parseOperator() const {
            auto next = m_pos + 1; // store next character after current position
            switch (*m_pos) {
            case '+':
                if (*next == '+') {
                    m_currToken.type = TokenType::PLUS_PLUS;
                    ++m_pos;
                }
                else if (*next == '=') {
                    m_currToken.type = TokenType::PLUS_EQUAL;
                    ++m_pos;
                }
                else {
                    m_currToken.type = TokenType::PLUS;
                }
                break;
            case '-':
                if (*next == '-') {
                    m_currToken.type = TokenType::MINUS_MINUS;
                    ++m_pos;
                }
                else if (*next == '=') {
                    m_currToken.type = TokenType::MINUS_EQUAL;
                    ++m_pos;
                }
                else {
                    m_currToken.type = TokenType::MINUS;
                }
                break;
            case '*':
                if (*next == '=') {
                    m_currToken.type = TokenType::ASTERISK_EQUAL;
                    ++m_pos;
                }
                else {
                    m_currToken.type = TokenType::ASTERISK;
                }
                break;
            case '/':
                if (*next == '=') {
                    m_currToken.type = TokenType::SLASH_EQUAL;
                    ++m_pos;
                }
                else {
                    m_currToken.type = TokenType::SLASH;
                }
                break;
            case '=':
                if (*next == '=') {
                    m_currToken.type = TokenType::DOUBLE_EQUAL;
                    ++m_pos;
                }
                else {
                    m_currToken.type = TokenType::EQUAL;
                }
                break;
            case '<':
                if (*next == '=') {
                    m_currToken.type = TokenType::LESS_OR_EQUAL;
                    ++m_pos;
                }
                else {
                    m_currToken.type = TokenType::LESS_THAN;
                }
                break;
            case '>':
                if (*next == '=') {
                    m_currToken.type = TokenType::GREATER_OR_EQUAL;
                    ++m_pos;
                }
                else {
                    m_currToken.type = TokenType::GREATER_THAN;
                }
                break;
            }

        }
        // get comment token
        void Lexer::parseComment() const {
            if (*m_pos == '/' && *(m_pos + 1) == '/') {
                m_currToken.type = TokenType::COMMENT;
                m_pos += 2; // skip these two slashes
                while (*m_pos != '\n' && *m_pos != '\0') {
                    m_currToken.symbol += *m_pos++;
                }
                --m_pos;
            }
            else { // ill-formed call to function
                m_currToken.type = TokenType::INVALID;
            }
        }

    public:
        Lexer::Lexer() {
            m_pos = m_rawString.begin();
        }

        Lexer::Lexer(std::string_view string)
        {
            setString(string);
        }

        // iterator (wrapper for next())
        struct Iterator {
            using iterator_category = std::input_iterator_tag;
            using value_type = Token;
            using pointer = Token*;
            using reference = Token&;
        };

        // read file content
        // return true on success
        bool Lexer::readFile(std::string_view fileName) {
            std::ifstream fin(fileName.data());

            if (fin) {
                // get all content of a file
                fin.unsetf(std::ios::skipws); // should include newlines
                m_rawString.assign(std::istream_iterator<char>(fin), std::istream_iterator<char>());

                m_rawString += '\0';
                // reset string index
                m_pos = m_rawString.begin();

                fin.close();
                return true;
            }
            else {
                return false;
            }
        }

        // set lexer string
        void Lexer::setString(std::string_view string) {
            m_rawString.reserve(string.size() + 1); // reserve plus one for EOF
            m_rawString = string;
            m_rawString += '\0';
            m_pos = m_rawString.begin();
        }

        // return Token structure from current index
        Token& Lexer::next() const {

            // skip spaces
            while (std::isspace(*m_pos)) { ++m_pos; }

            // set symbol line
            getSymbolLine();

            if (std::isalpha(*m_pos) || *m_pos == '_') { // symbol if encounted char or underscore
                parseSymbol();
            }
            else if (*m_pos == '\'' || *m_pos == '"') { // string
                parseString();
            }
            else if (std::isdigit(*m_pos)) { // integer or rational
                parseNumber();
            }
            else if (*m_pos == '.') {
                if (isdigit(*(m_pos + 1))) { // if char after current position is a digit
                    parseNumber(); // parse number
                }
                else { // else assume as a standalone point
                    m_currToken.type = TokenType::POINT;
                }
            }
            else if (*m_pos == '\0') {
                m_currToken.type = TokenType::END_OF_FILE;
            }
            else {
                switch (*m_pos) {
                case '/': // can be a comment
                    if (*(m_pos + 1) == '/') { // handle as a comment
                        parseComment();
                        break;
                    }
                    [[fallthrough]]; // fall below if not a comment
                case '-':
                case '*':
                case '+':
                case '=':
                case '<':
                case '>':
                    parseOperator();
                    break;
                case ',': m_currToken.type = TokenType::COMMA; break;
                case ';': m_currToken.type = TokenType::SEMICOLON; break;
                case ':': m_currToken.type = TokenType::COLON; break;
                case '(': m_currToken.type = TokenType::LEFT_PARAN; break;
                case ')': m_currToken.type = TokenType::RIGHT_PARAN; break;
                case '[': m_currToken.type = TokenType::LEFT_SQUARE; break;
                case ']': m_currToken.type = TokenType::RIGHT_SQUARE; break;
                case '{': m_currToken.type = TokenType::LEFT_CURLY; break;
                case '}': m_currToken.type = TokenType::RIGHT_CURLY; break;
                    // TODO: other cases
                default:
                    m_currToken.type = TokenType::INVALID;
                }
            }

            // always return EOF when m_pos is on the last character
            if (m_currToken.type != TokenType::END_OF_FILE) {
                // as far as any parsing process stops on last character
                ++m_pos; // move pointer forward
            }

            return m_currToken;
        }
    };
}