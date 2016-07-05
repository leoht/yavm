#include <iostream>
#ifndef TOKEN_H
#define TOKEN_H

class Token {
    
public:
    static const std::string END_OF_FILE;
    static const std::string END_OF_LINE;
    static const std::string INTEGER;
    static const std::string OP_PLUS;
    static const std::string OP_MINUS;
    static const std::string OP_MUL;
    static const std::string OP_DIV;
    static const std::string COMMA;
    static const std::string LEFT_PAREN;
    static const std::string RIGHT_PAREN;
    static const std::string LEFT_BRACK;
    static const std::string RIGHT_BRACK;
    static const std::string OP_ASSIGN;
    static const std::string NAME;
    static const std::string LITTERAL_STR;
    static const std::string DOT;
    static const std::string RETURN;
    static const std::string ATTRIBUTE;
    static const std::string NIL;
    static const std::string BOOL_TRUE;
    static const std::string BOOL_FALSE;
    
    static const std::string EQUALS;
    static const std::string NEQUALS;
    static const std::string LTHAN;
    static const std::string GTHAN;
    
    static const std::string CLASS;
    static const std::string DEF;
    static const std::string END;
    
    std::string type;
    std::string value;
    
    Token(std::string type, std::string value);
    std::string to_string() const;
    bool is(std::string t) const;
};

std::ostream& operator<<(std::ostream &s, const Token &token);

#endif
