#include "class.h"
#include "object.h"
#include "context.h"
#include "instruction_parser.h"

Class::Class(std::string n) {
    name = n;
    
    std::vector<std::string> args;
    args.push_back("name");
    
    this->addMethod(new Method("new", "", std::vector<std::string>(), Method::V_PUBLIC, true));
    this->addMethod(new Method("sayHello", "return 'Hello ' + name", args, Method::V_PUBLIC, true));
    this->addMethod(new Method("hello", "return @foo + @bar", std::vector<std::string>(), Method::V_PUBLIC, false));
    this->addMethod(new Method("hi", "return @foo - @bar", std::vector<std::string>(), Method::V_PUBLIC, false));
    
    this->addMethod(new Method("class", "", std::vector<std::string>(), Method::V_PUBLIC, false));
}

std::string Class::getName() {
    return name;
}

void Class::addMethod(Method* method) {
    methods.push_back(method);
}

bool Class::hasMethod(std::string name) {
    for (std::vector<Method*>::iterator it = methods.begin() ; it != methods.end() ; ++it) {
        Method* m = *it;
        
        if (m->name == name && m->is_static == false) {
            return true;
        }
    }
    
    return false;
}

bool Class::hasStaticMethod(std::string name) {
    for (std::vector<Method*>::iterator it = methods.begin() ; it != methods.end() ; ++it) {
        Method* m = *it;
        
        if (m->name == name && m->is_static == true) {
            return true;
        }
    }
    
    return false;
}

Method* Class::getMethod(std::string name) {
    for (std::vector<Method*>::iterator it = methods.begin() ; it != methods.end() ; ++it) {
        Method* m = *it;
        
        if (m->name == name) {
            return m;
        }
    }
    
    return NULL;
}

std::vector<Method*> Class::getMethods() {
    return methods;
}

Value Class::callStatic(std::string method_name, Context* context, std::vector<Value> arguments) {
    if (method_name == "new") {
        return callNew(context);
    }
    
    Method* m = getMethod(method_name);
    
    if (m == NULL) {
        throw std::string("Undefined static method "+name+"::"+method_name);
    }
    
    InstructionParser* p = new InstructionParser(context);
    
    return p->parse(m->body);
}

Value Class::call(std::string method_name, Object* instance, Context* context, std::vector<Value> arguments) {
    Method* m = getMethod(method_name);
    
    if (method_name == "class") {
        return Value(this);
    }
    
    if (m != NULL) {
        InstructionParser* p = new InstructionParser(context);
        context->is_object_context = true;
        context->current_instance = instance;
        
        // Create narrower scope for method
        Scope* childScope = context->scope->child();
        context->scope = childScope;
        
        // Inject arguments into child scope
        std::vector<Value>::iterator vit = arguments.begin();
        for (std::vector<std::string>::iterator nit = m->arguments.begin() ; nit != m->arguments.end() ; ++nit) {
            std::string name = *nit;
            Value v = *vit;
            
            context->scope->set(name, v);
            ++vit;
        }
        
        // Eval method
        Value retValue = p->parse(m->body);
        
        // Return to parent scope
        context->scope = context->scope->parent;
        context->is_object_context = false;
        context->current_instance = NULL;
        
        return retValue;
    }
    
    throw std::string("Undefined method "+instance->to_string()+"::"+method_name);
}

Value Class::callNew(Context* context) {
    Object* obj = Object::instantiate(this);
    obj->addAttribute(new Attribute("foo", new Value(42), Attribute::V_PUBLIC, false));
    obj->addAttribute(new Attribute("bar", new Value(6), Attribute::V_PUBLIC, false));
    
    return Value(obj);
}

std::string Class::to_string() const {
    return "<Class:" + name + ">";
}

std::ostream& operator<<(std::ostream& s, const Class& c) {
    s << c.to_string();
    
    return s;
}
