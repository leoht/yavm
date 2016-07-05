#ifndef _CONTEXT_H
#define _CONTEXT_H

#include <vector>
#include "class.h"
#include "scope.h"

class Context {

public:
    Scope* root_scope;
    Scope* scope;
    std::vector<Class*> classes;
    bool is_object_context;
    Object* current_instance;
    bool in_class;
    bool in_method;
    std::string current_class_name;
    std::string current_method_name;
    
    static Context* create();
    
    Context();
    void registerClass(Class*);
    Class* getClass(std::string);
};

#endif
