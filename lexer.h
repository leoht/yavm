#include "token_stream.h"

class Lexer {
    
    std::string text;
    int pos;
    char current_char;
    
    void advance();
    void skip_whitespace();
    int read_integer();
    std::string read_string();
    std::string read_name();
    Token* next_token();
    
public:
    Lexer();
    TokenStream* tokenize(std::string text);
};
