#ifndef _CLASS_H
#define _CLASS_H

#include <string>
#include <vector>
#include "method.h"

class Value;
class Attribute;
class Object;
class Context;

class Class {
public:
    bool is_primitive;
    
    std::string name;
    std::vector<Method*> methods;
    std::vector<Attribute*> attributes;
    
    Class(std::string);
    std::string getName();
    void addMethod(Method* method);
    bool hasMethod(std::string);
    bool hasStaticMethod(std::string);
    Method* getMethod(std::string name);
    std::vector<Method*> getMethods();
    
    Value call(std::string method_name, Object* instance, Context* context, std::vector<Value> arguments);
    Value callStatic(std::string method_name, Context* context, std::vector<Value> arguments);
    
    std::string to_string() const;
    
private:
    Value callNew(Context* context);
};

std::ostream& operator<<(std::ostream& s, const Class& c);

#endif
