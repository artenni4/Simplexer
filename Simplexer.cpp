#include "Simplexer.hpp"

void Lexer::readFile(std::string_view fileName) {
    std::ifstream fin(fileName.data());

    if (fin) {
        std::cout << "File " << fileName << " opened" << std::endl;

        // get all content of a file
        fin.unsetf(std::ios::skipws); // should include newlines
        m_rawString.assign(std::istream_iterator<char>(fin), std::istream_iterator<char>());

        m_rawString += '\0';
        // reset string index
        m_pos = m_rawString.begin();

        std::cout << "File content was read" << std::endl;
        fin.close();
    }
    else {
        std::cerr << "Failed to open file " << fileName << std::endl;
    }
}

const std::string Lexer::getSymbolLine() const {
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
    return res.str();
}

const Token Lexer::parseSymbol() const
{
    Token tk;
    tk.type = TokenType::SYMBOL;
    // fill in string for token
    while (std::isalpha(*m_pos) || std::isdigit(*m_pos)) {
        tk.symbol += *m_pos++;
    }
    --m_pos; // return to the last character
    
    return tk;
}

const Token Lexer::parseNumber() const
{
    Token tk;
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

    return tk;
}

const Token Lexer::parseString() const
{
    Token tk;
    tk.type = TokenType::STRING;
    // remember starting quote and fill string to same quote
    char quote = *m_pos++;
    while (*m_pos != quote) {
        // TODO: handle this -> \ in strings
        tk.symbol += *m_pos++;
    }
    // do not skip ending quote like this m_pos++; 
    // because parse functions should stop on last character
    return tk;
}

const Token Lexer::next() const {
    Token tk;

    // skip spaces
    while (std::isspace(*m_pos)) { ++m_pos; }

    if (std::isalpha(*m_pos)) { // symbol
        tk = parseSymbol();
    }
    else if (*m_pos == '\'' || *m_pos == '"') { // string
        tk = parseString();
    }
    else if (std::isdigit(*m_pos)) { // integer or rational
        tk = parseNumber();
    }
    else if (*m_pos == '.') {
        if (isdigit(*(m_pos + 1))) { // if char after current position is a digit
            tk = parseNumber(); // parse number
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
        case '+': tk.type = TokenType::PLUS; break;
        case '-': tk.type = TokenType::MINUS; break;
        case '*': tk.type = TokenType::ASTERISK; break;
        case '/': tk.type = TokenType::SLASH; break;
        // TODO: other cases
        default:
            tk.type = TokenType::INVALID;
        }
    }

    // so as any parsing stops on last character
    ++m_pos; // move pointer forward
    
    // set symbol line
    tk.line = getSymbolLine();

    return tk;
}
