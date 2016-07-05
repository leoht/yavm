#include "expression_parser.h"
#include <ctype.h>
#include <sstream>

ExpressionParser::ExpressionParser(TokenStream* stream, Token* current, Context* ctx) {
    token_stream = stream;
    current_token = current;
    context = ctx;
}

void ExpressionParser::expect(std::string token_type) {
    if (current_token->is(token_type)) {
        current_token = token_stream->next();
    } else {
        // std::cout << *current_token << std::endl;
        throw "Unexpected token: " + current_token->to_string();
    }
}

Value ExpressionParser::atom() {
    Token* token = current_token;
    
    // Try to find a sub-expression
    // with parenthesis
    if (token->is(Token::LEFT_PAREN)) {
        expect(Token::LEFT_PAREN);
        Value result = sum();
        expect(Token::RIGHT_PAREN);
        
        return result;
    } else if (token->is(Token::ATTRIBUTE)) {
        std::string name = token->value;
        expect(Token::ATTRIBUTE);
        
        if (context->is_object_context) {
            Object* obj = context->current_instance;
            Attribute* a = obj->getAttribute(name);
            
            return *(a->value);
        } else {
            throw std::string("Cannot evaluate attribute @" + name + " in non-object context.");
        }
    } else if (token->is(Token::NAME)) {
        expect(Token::NAME);
        std::string name = token->value;

        if (context->getClass(name) != NULL) {
            return parseMethodCall(name, false);
        }
        
        if (current_token->is(Token::DOT)) {
            return parseMethodCall(name, true);
        }
        
        Value v = context->scope->get(name);
        return v;
    } else if (token->is(Token::LITTERAL_STR)) {
        // std::cout << *token << std::endl;
        expect(Token::LITTERAL_STR);
        
        return Value(token->value);
    } else if (token->is(Token::BOOL_TRUE)) {
        expect(Token::BOOL_TRUE);
        
        return Value(true);
    } else if (token->is(Token::BOOL_FALSE)) {
        expect(Token::BOOL_FALSE);
        
        return Value(false);
    } else if (token->is(Token::NIL)) {
        expect(Token::NIL);
        
        return NIL_VALUE;
    } else {
        expect(Token::INTEGER);
        
        return Value(stoi(token->value));
    }
}

Value ExpressionParser::factor() {
    if (current_token->is(Token::OP_PLUS)) {
        expect(Token::OP_PLUS);
        
        return factor();
    }
    if (current_token->is(Token::OP_MINUS)) {
        expect(Token::OP_MINUS);
        
        // dirty hack, TODO: overload Value::operator-()
        return Value(0) - factor();
    }
    
    return atom();
}

Value ExpressionParser::product() {
    Value prod = factor();
    
    while (current_token->is(Token::OP_MUL) || current_token->is(Token::OP_DIV)) {
        if (current_token->is(Token::OP_MUL)) {
            expect(Token::OP_MUL);
            prod = prod * factor();
        } else {
            expect(Token::OP_DIV);
            Value n = factor();
            
            if (n.getInt32() == 0) {
                throw std::string("Division by zero");
            }
            
            prod = prod / n;
        }
    }
    
    return prod;
}

Value ExpressionParser::sum() {
    Value result = product();
    
    while (current_token->is(Token::OP_PLUS) || current_token->is(Token::OP_MINUS)) {
        if (current_token->type == Token::OP_PLUS) {
            expect(Token::OP_PLUS);
            result = result + product();
        } else {
            expect(Token::OP_MINUS
            );
            result = result - product();
        }
    }
    
    return result;
}

Value ExpressionParser::parseMethodCall(std::string name, bool on_instance) {
    Value val;
    Class* c;
    
    if (!on_instance) {
        c = context->getClass(name);
        val = Value(c);
    } else {
        val = context->scope->get(name);
        
        if (val.isObject()) {
            c = val.getObject()->isa;
        }
    }
    
    while (current_token->is(Token::DOT)) {
        expect(Token::DOT);
        name = current_token->value;
        expect(Token::NAME);
        
        std::vector<Value> arguments;
        
        if (current_token->is(Token::LEFT_PAREN)) { // begin arguments
            expect(Token::LEFT_PAREN);
            while (!current_token->is(Token::RIGHT_PAREN)) {
                if (current_token->is(Token::NAME) || current_token->is(Token::INTEGER) || current_token->is(Token::LITTERAL_STR)) {
                    Value v = parse();
                    arguments.push_back(v);
                    if (current_token->is(Token::COMMA)) {
                        expect(Token::COMMA);
                    }
                }
            }
        }
        
        if (val.isNil()) {
            // Method call on nil returns nil.
            return val;
        } else if (val.isClass()) {
            val = c->callStatic(name, context, arguments);
        } else if (val.isObject()) {
            val = c->call(name, val.getObject(), context, arguments);
        } else {
            throw std::string("Cannot call method " + name + " on non-object value.");
        }
        
    }
    
    return val;
}

Value ExpressionParser::parse() {
    if (token_stream->has(Token::EQUALS)) {
        Value lv = sum();
        expect(Token::EQUALS);
        Value rv = sum();
        
        return Value(lv.getInt32() == rv.getInt32());
    }
    
    return sum();
}
