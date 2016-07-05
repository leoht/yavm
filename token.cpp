#include "token.h"

const std::string Token::INTEGER = "INTEGER";
const std::string Token::OP_PLUS = "OP_PLUS";
const std::string Token::END_OF_FILE = "EOF";
const std::string Token::END_OF_LINE = "EOL";
const std::string Token::OP_MINUS = "OP_MINUS";
const std::string Token::OP_MUL = "OP_MUL";
const std::string Token::OP_DIV = "OP_DIV";
const std::string Token::COMMA = "COMMA";
const std::string Token::LEFT_PAREN = "LEFT_PAREN";
const std::string Token::RIGHT_PAREN = "RIGHT_PAREN";
const std::string Token::LEFT_BRACK = "LEFT_BRACK";
const std::string Token::RIGHT_BRACK = "RIGHT_BRACK";
const std::string Token::OP_ASSIGN = "OP_ASSIGN";
const std::string Token::NAME = "NAME";
const std::string Token::LITTERAL_STR = "LITTERAL_STR";
const std::string Token::DOT = "DOT";
const std::string Token::RETURN = "RETURN";
const std::string Token::ATTRIBUTE = "ATTRIBUTE";
const std::string Token::NIL = "NIL";
const std::string Token::BOOL_TRUE = "TRUE";
const std::string Token::BOOL_FALSE = "FALSE";
const std::string Token::EQUALS = "EQUALS";
const std::string Token::NEQUALS = "NEQUALS";
const std::string Token::LTHAN = "LTHAN";
const std::string Token::GTHAN = "GTHAN";
const std::string Token::CLASS = "CLASS";
const std::string Token::DEF = "DEF";
const std::string Token::END = "END";

Token::Token(std::string type, std::string value) : type(type), value(value) {
}

std::string Token::to_string() const {
    return "Token(" + type + ", " + value + ")";
}

bool Token::is(std::string t) const {
    return t == type;
}

std::ostream& operator<<(std::ostream &s, const Token &token) {
    return s << token.to_string();
}
