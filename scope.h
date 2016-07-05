#ifndef _SCOPE_H
#define _SCOPE_H

#include <map>
#include "value.h"

class Scope {
    
public:
    std::map<std::string, Value> symbol_table;
    Scope* parent;
    
    static Scope* create();
    Scope();
    Scope(Scope* parent);
    Scope* child();
    Scope* root();
    
    Value set(std::string, Value);
    Value get(std::string);
};

#endif
