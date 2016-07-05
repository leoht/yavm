#ifndef _ATTRIBUTE_H
#define _ATTRIBUTE_H

#include "value.h"

class Attribute {
public:
    typedef enum { V_PRIVATE, V_PUBLIC, V_PROTECTED } visibility_t;
    
    bool is_static;
    std::string name;
    Value *value;
    visibility_t visibility;
    
    Attribute(std::string name, Value *value, visibility_t visibility, bool is_static);
};

#endif
