#include "lexer.h"
#include <ctype.h>

#define DEFINE_TOKEN_CHAR(c, type, val)  \
if (current_char == c) { \
    advance();              \
    return new Token(type, val); \
} \

#define DEFINE_TOKEN_2CHAR(s, type, val)  \
if (current_char == s[0]) { \
    int previous = pos; \
    advance();          \
    if (current_char == s[1]) {        \
        advance(); \
        return new Token(type, val); \
    } else {        \
        pos = previous; \
        current_char = text[pos]; \
    } \
} \

#define DEFINE_TOKEN_STRING(s, type, val)  \
if (isalpha(current_char)) { \
    int previous = pos; \
    std::string tok = read_name(); \
    if (tok == s) { \
        return new Token(type, val); \
    } else { \
        pos = previous; \
        current_char = text[pos]; \
    } \
} \

Lexer::Lexer() {
}

void Lexer::advance() {
    pos += 1;
    
    if (pos > text.length() - 1) {
        current_char = '\0';
    } else {
        current_char = text[pos];
    }
}

void Lexer::skip_whitespace() {
    while (current_char != '\0' && isspace(current_char)) {
        advance();
    }
}

std::string Lexer::read_name() {
    std::string name = "";
    
    while (current_char != '\0' && (isalpha(current_char) || isdigit(current_char) || current_char == '_')) {
        name += current_char;
        advance();
    }
    
    return name;
}

int Lexer::read_integer() {
    std::string result = "";
    
    while (current_char != '\0' && isdigit(current_char)) {
        result += current_char;
        advance();
    }
    
    return stoi(result);
}

std::string Lexer::read_string() {
    std::string result = "";
    char delim = current_char == '\'' ? '\'' : '"';
    
    advance(); // skip opening delimiter
    
    while (current_char != delim) {
        result += current_char;
        advance();
    }
    
    advance(); // skip closing delimiter
    
    return result;
}

Token* Lexer::next_token() {
    while (current_char != '\0') {
        if (isspace(current_char)) {
            skip_whitespace();
            continue;
        }
        
        DEFINE_TOKEN_STRING("return", Token::RETURN, "return");
        DEFINE_TOKEN_STRING("nil", Token::NIL, "nil");
        DEFINE_TOKEN_STRING("true", Token::BOOL_TRUE, "true");
        DEFINE_TOKEN_STRING("false", Token::BOOL_FALSE, "false");
        DEFINE_TOKEN_STRING("class", Token::CLASS, "class");
        DEFINE_TOKEN_STRING("def", Token::DEF, "def");
        DEFINE_TOKEN_STRING("end", Token::END, "end");
        
        DEFINE_TOKEN_2CHAR("==", Token::EQUALS, "==");
        DEFINE_TOKEN_2CHAR("!=", Token::NEQUALS, "!=");
        
        DEFINE_TOKEN_CHAR('+', Token::OP_PLUS, "+")
        DEFINE_TOKEN_CHAR('-', Token::OP_MINUS, "-")
        DEFINE_TOKEN_CHAR('*', Token::OP_MUL, "*")
        DEFINE_TOKEN_CHAR('/', Token::OP_DIV, "/")
        DEFINE_TOKEN_CHAR(',', Token::COMMA, ",")
        DEFINE_TOKEN_CHAR('(', Token::LEFT_PAREN, "(")
        DEFINE_TOKEN_CHAR(')', Token::RIGHT_PAREN, ")")
        DEFINE_TOKEN_CHAR('{', Token::LEFT_BRACK, "{")
        DEFINE_TOKEN_CHAR('}', Token::RIGHT_BRACK, "}")
        DEFINE_TOKEN_CHAR('=', Token::OP_ASSIGN, "=")
        DEFINE_TOKEN_CHAR('.', Token::DOT, ".")
        DEFINE_TOKEN_CHAR('<', Token::LTHAN, "<");
        DEFINE_TOKEN_CHAR('>', Token::GTHAN, ">");
        DEFINE_TOKEN_CHAR('\n', Token::END_OF_LINE, ";")
        DEFINE_TOKEN_CHAR(';',  Token::END_OF_LINE, ";")
        
        if (current_char == '@') {
            advance();
            std::string name = read_name();
            return new Token(Token::ATTRIBUTE, name);
        }
        
        if (isdigit(current_char)) {
            return new Token(Token::INTEGER, std::to_string(read_integer()));
        }
        
        if (isalpha(current_char)) {
            return new Token(Token::NAME, read_name());
        }
        
        if (current_char == '\'' || current_char == '"') {
            return new Token(Token::LITTERAL_STR, read_string());
        }
        
        throw "Unexpected token";
    }
    
    return new Token(Token::END_OF_FILE, "");
}

TokenStream* Lexer::tokenize(std::string txt) {
    text = txt;
    current_char = text[0];
    TokenStream* stream = new TokenStream();
    Token* current;
    
    do {
        current = next_token();
        stream->push(current);
        // std::cout << *current << std::endl;
    } while (current->type != Token::END_OF_FILE);
    
    // clean up
    pos = 0;
    current_char = 0;
    
    return stream;
}
