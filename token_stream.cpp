#include "token_stream.h"

TokenStream::TokenStream() {
}

void TokenStream::push(Token* token) {
    tokens.push_back(token);
}

Token* TokenStream::current() {
    return tokens.front();
}

Token* TokenStream::next() {
    Token* next = tokens.front();
    tokens.pop_front();
    
    return next;
}

void TokenStream::flush() {
    tokens.clear();
}

bool TokenStream::has(std::string type) {
    for (std::deque<Token*>::iterator i = tokens.begin() ; i != tokens.end() ; i++) {
        if ((*i)->is(type)) {
            return true;
        }
    }
    
    return false;
}
