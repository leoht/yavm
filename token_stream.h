#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H

#include <iostream>
#include <deque>
#include "token.h"

class TokenStream {
public:
    std::deque<Token*> tokens;
    
    TokenStream();
    void push(Token* token);
    bool has(std::string type);
    Token* current();
    Token* next();
    void flush();
};

#endif
