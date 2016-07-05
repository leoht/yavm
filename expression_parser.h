#include <iostream>
#include "token_stream.h"
#include "context.h"
#include "value.h"

class ExpressionParser {
    
public:
    Context* context;
    Token* current_token;
    TokenStream* token_stream;
    std::string text;
    
    ExpressionParser(TokenStream* stream, Token* current, Context* context);
    void expect(std::string token_type);
    
    Value atom();
    Value factor();
    Value product();
    Value sum();
    
    Value parseMethodCall(std::string, bool on_instance);
    Value parse();
};
