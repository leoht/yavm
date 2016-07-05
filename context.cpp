#include "context.h"

Context* Context::create() {
    return new Context();
}

Context::Context() {
    root_scope = new Scope();
    scope = root_scope;
}

void Context::registerClass(Class* c) {
    classes.push_back(c);
}

Class* Context::getClass(std::string name) {
    for (std::vector<Class*>::iterator it = classes.begin() ; it != classes.end() ; it++) {
        Class* c = *it;
        
        if (c->name == name) {
            return c;
        }
    }
    
    return NULL;
}
