#include "scope.h"

Scope* Scope::create() {
    return new Scope();
}

Scope::Scope() {
    symbol_table = std::map<std::string, Value>();
}

Scope::Scope(Scope* parent) : parent(parent) {
    symbol_table = std::map<std::string, Value>();
}

Scope* Scope::child() {
    Scope* child =  new Scope();
    child->parent = this;
    
    return child;
}

Scope* Scope::root() {
    Scope* scope = this;
    while (scope->parent != NULL) {
        scope = scope->parent;
    }
    
    return scope;
}

Value Scope::set(std::string name, Value val) {
    symbol_table[name] = val;
    // std::cout << *(symbol_table[name]) << std::endl;
    
    return val;
}

Value Scope::get(std::string name) {
    if (symbol_table.find(name) == symbol_table.end()) {
        throw std::string("Undefined variable: " + name);
    }
    
    return symbol_table[name];
}
