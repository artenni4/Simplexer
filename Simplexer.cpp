#include "Simplexer.hpp"

namespace Simplexer {

    Lexer::Lexer() { 
        m_pos = m_rawString.begin();
    }

    Lexer::Lexer(std::string_view string) : 
        m_rawString(string) 
    { 
        m_pos = m_rawString.begin();
    }

    void Lexer::setString(std::string_view string) {
        m_rawString = string;
        m_pos = m_rawString.begin();
        m_rawString += '\0';
    }

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

    void Lexer::getSymbolLine(std::string& ln) const {
        std::stringstream res;
        std::size_t row = 0, line = 1; // start line from 1, not from 0
        std::string::const_iterator lastNl = m_rawString.begin(); // last new line

        for (std::string::const_iterator it = m_rawString.begin(); it != m_pos; ++it) {
            if (*it == '\n') {
                line++;
                lastNl = it + 1; // skip \n character
            }
        }
        row = m_pos - lastNl + 1; // shift one char to right, so first is 1 but not 0

        res << '(' << line << ',' << row << ')';
        ln = res.str();
    }

    void Lexer::parseSymbol(Token& tk) const
    {
        tk.type = TokenType::SYMBOL;
        // fill in string for token
        while (std::isalpha(*m_pos) || std::isdigit(*m_pos)) {
            tk.symbol += *m_pos++;
        }
        --m_pos; // return to the last character
    }

    void Lexer::parseNumber(Token& tk) const
    {
        // get all digits and skip if point is on the first place
        while (std::isdigit(*m_pos)) {
            tk.symbol += *m_pos++;
        }

        // check for point after previous loop
        if (*m_pos == '.') { // add point to symbol string and define type as RATIONAL
            tk.symbol += *m_pos++;
            while (std::isdigit(*m_pos)) {
                tk.symbol += *m_pos++;
            }
            tk.type = TokenType::RATIONAL;
        }
        else { // if there is no point then type is INTEGER
            tk.type = TokenType::INTEGER;
        }
        --m_pos; // return to the last character
    }

    void Lexer::parseString(Token& tk) const {
        tk.type = TokenType::STRING;
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
                tk.type = TokenType::INVALID;
                break;
            }
            else if (*m_pos == '\\') { // if encounter backslash
                if (*(m_pos + 1) == quote) { // and next char is quote parseString started with
                    // then swallow this quote
                    tk.symbol += *++m_pos;
                    ++m_pos; // skip the quote
                }
                else {
                    tk.symbol += *m_pos++;
                }
            }
            else {
                tk.symbol += *m_pos++;
            }
        }
    }

    void Lexer::parseOperator(Token& tk) const {
        auto next = m_pos + 1; // store next character after current position
        switch (*m_pos) {
        case '+':
            if (*next == '+') {
                tk.type = TokenType::PLUS_PLUS;
                ++m_pos;
            }
            else if (*next == '=') {
                tk.type = TokenType::PLUS_EQUAL;
                ++m_pos;
            }
            else {
                tk.type = TokenType::PLUS;
            }
            break;
        case '-':
            if (*next == '-') {
                tk.type = TokenType::MINUS_MINUS;
                ++m_pos;
            }
            else if (*next == '=') {
                tk.type = TokenType::MINUS_EQUAL;
                ++m_pos;
            }
            else {
                tk.type = TokenType::MINUS;
            }
            break;
        case '*':
            if (*next == '=') {
                tk.type = TokenType::ASTERISK_EQUAL;
                ++m_pos;
            }
            else {
                tk.type = TokenType::ASTERISK;
            }
            break;
        case '/':
            if (*next == '=') {
                tk.type = TokenType::SLASH_EQUAL;
                ++m_pos;
            }
            else {
                tk.type = TokenType::SLASH;
            }
            break;
        case '=':
            if (*next == '=') {
                tk.type = TokenType::DOUBLE_EQUAL;
                ++m_pos;
            }
            else {
                tk.type = TokenType::EQUAL;
            }
            break;
        case '<':
            if (*next == '=') {
                tk.type = TokenType::LESS_OR_EQUAL;
                ++m_pos;
            }
            else {
                tk.type = TokenType::LESS_THAN;
            }
            break;
        case '>':
            if (*next == '=') {
                tk.type = TokenType::GREATER_OR_EQUAL;
                ++m_pos;
            }
            else {
                tk.type = TokenType::GREATER_THAN;
            }
            break;
        }

    }

    void Lexer::parseComment(Token& tk) const {
        if (*m_pos == '/' && *(m_pos + 1) == '/') {
            tk.type = TokenType::COMMENT;
            m_pos += 2; // skip these two slashes
            while (*m_pos != '\n' && *m_pos != '\0') {
                tk.symbol += *m_pos++;
            }
            --m_pos;
        }
        else { // ill-formed call to function
            tk.type = TokenType::INVALID;
        }
    }

    const Token Lexer::next() const {
        Token tk;

        // skip spaces
        while (std::isspace(*m_pos)) { ++m_pos; }

        // set symbol line
        getSymbolLine(tk.line);

        if (std::isalpha(*m_pos)) { // symbol
            parseSymbol(tk);
        }
        else if (*m_pos == '\'' || *m_pos == '"') { // string
            parseString(tk);
        }
        else if (std::isdigit(*m_pos)) { // integer or rational
            parseNumber(tk);
        }
        else if (*m_pos == '.') {
            if (isdigit(*(m_pos + 1))) { // if char after current position is a digit
                parseNumber(tk); // parse number
            }
            else { // else assume as a standalone point
                tk.type = TokenType::POINT;
            }
        }
        else if (*m_pos == '\0') {
            tk.type = TokenType::END_OF_FILE;
        }
        else {
            switch (*m_pos) {
            case '/': // can be a comment
                if (*(m_pos + 1) == '/') { // handle as a comment
                    parseComment(tk);
                    break;
                }
                [[fallthrough]]; // fall below if not a comment
            case '-':
            case '*':
            case '+':
            case '=':
            case '<':
            case '>':
                parseOperator(tk);
                break;
            case ',': tk.type = TokenType::COMMA; break;
            case ';': tk.type = TokenType::SEMICOLON; break;
            case ':': tk.type = TokenType::COLON; break;
            case '(': tk.type = TokenType::LEFT_PARAN; break;
            case ')': tk.type = TokenType::RIGHT_PARAN; break;
            case '[': tk.type = TokenType::LEFT_SQUARE; break;
            case ']': tk.type = TokenType::RIGHT_SQUARE; break;
            case '{': tk.type = TokenType::LEFT_CURLY; break;
            case '}': tk.type = TokenType::RIGHT_CURLY; break;
                // TODO: other cases
            default:
                tk.type = TokenType::INVALID;
            }
        }

        // always return EOF when m_pos is on the last character
        if (tk.type != TokenType::END_OF_FILE) {
            // as far as any parsing process stops on last character
            ++m_pos; // move pointer forward
        }

        return tk;
    }

}