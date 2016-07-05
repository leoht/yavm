#ifndef _OBJECT_H
#define _OBJECT_H

#include <vector>
#include "class.h"
#include "attribute.h"

class Object {
public:
    static Object* instantiate(Class* c);
    Object();
    
    Class* isa;
    std::string id;
    std::vector<Attribute*> attributes;
    
    void addAttribute(Attribute*);
    Attribute* getAttribute(std::string);
    std::vector<Attribute*> getAttributes();
    
    std::string to_string() const;
};

std::ostream& operator<<(std::ostream& s, const Object& o);

#endif
