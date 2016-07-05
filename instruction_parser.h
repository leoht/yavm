#include <iostream>
#include <map>
#include "expression_parser.h"
#include "lexer.h"
#include "context.h"
#include "object.h"
#include "value.h"

class InstructionParser {
    
public:
    Lexer* lexer;
    ExpressionParser* expression_parser;
    Token* current_token;
    TokenStream* token_stream;
    std::string text;
    Context* context;
    
    InstructionParser(Context* context);
    void expect(std::string token_type);

    Value parseClassDeclaration();
    Value doParse();
    Value parse(std::string);
    
    void clear();
};
