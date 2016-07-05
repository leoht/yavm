#include "instruction_parser.h"

#include <ctype.h>
#include <sstream>

InstructionParser::InstructionParser(Context* context) : current_token(NULL), context(context) {
    lexer = new Lexer();
}

void InstructionParser::expect(std::string token_type) {
    if (current_token->is(token_type)) {
        current_token = token_stream->next();
    } else {
        std::cout << *current_token << std::endl;
        throw std::string("Unexpected token.");
    }
}

void InstructionParser::clear() {
    token_stream->flush();
    current_token = NULL;
    text = "";
}


Value InstructionParser::parseClassDeclaration()
{
    if (current_token->is(Token::DEF)) {
        context->in_method = true;
        
        while (!current_token->is(Token::END)) {
            // TODO
        }
    }
    
    
}

Value InstructionParser::doParse() {
    
    if (context->in_class) {
        return parseClassDeclaration();
    }
    
    if (token_stream->has(Token::OP_ASSIGN)) {
        std::string name = current_token->value;
        expect(Token::NAME);
        expect(Token::OP_ASSIGN);
        
        expression_parser = new ExpressionParser(token_stream, current_token, context);    

        Value lv = expression_parser->parse();
        Value v = context->scope->set(name, lv);
        
        return v;
    }
    
    if (current_token->is(Token::CLASS)) {
        expect(Token::CLASS);
        std::string name = current_token->value;
        expect(Token::NAME);
        
        context->in_class = true;
        context->current_class_name = name;
        
        return NIL_VALUE;
    }
    
    // For now return an expr. has no really different effect than just typing this expr.
    if (current_token->is(Token::RETURN)) {
        expect(Token::RETURN);
        
        if (current_token->is(Token::END_OF_FILE) || current_token->is(Token::END_OF_LINE)) {
            return NIL_VALUE;
        }
        
    }
    
    expression_parser = new ExpressionParser(token_stream, current_token, context);    
    return expression_parser->parse();
    
    // if (current_token->is(Token::NAME)) {
    //     Token* token = current_token;
    //     name = current_token->value;
    //     expect(Token::NAME);
    //     
    //     if (current_token->is(Token::END_OF_LINE) || current_token->is(Token::END_OF_FILE)) {
    //         return context->scope->get(name);
    //     }
    //     
    //     if (context->getClass(name) != NULL) {
    //         return parseMethodCall(name);
    //     } else {
    //         if (current_token->is(Token::OP_ASSIGN)) {
    //             expect(Token::OP_ASSIGN);
    //             
    //             Value lv = doParse();
    //             Value v = context->scope->set(name, lv);
    //             
    //             return v;
    //         }
    //     }
    // }
}

Value InstructionParser::parse(std::string txt) {
    text = txt;

    try {
        token_stream = lexer->tokenize(text);
    } catch(char const* e) {
        std::cout << e << std::endl;
    }
    
    current_token = token_stream->next();
    
    return doParse();
}
