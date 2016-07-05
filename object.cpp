#include "object.h"
#include <cstdlib>

std::string generate_uuid(int max) {
  std::string buf = "";
  std::string hexdigit = "0123456789abcdef";
  if(max < 1)
    return "";
  --max;
  
  for(int i = 0; i < max; ++i)
    buf += hexdigit[rand() % hexdigit.length()];

  return "0x" + buf;
}

Object* Object::instantiate(Class *c) {
    if (c == NULL) {
        throw std::string("object.cpp: Cannot instantiate null class.");
    }
    
    Object* o = new Object();
    o->isa = c;
    o->id = generate_uuid(10);
    
    return o;
}

Object::Object() {
}

void Object::addAttribute(Attribute* attr) {
    attributes.push_back(attr);
}

Attribute* Object::getAttribute(std::string name) {
    for (std::vector<Attribute*>::iterator it = attributes.begin() ; it != attributes.end() ; ++it) {
        Attribute* a = *it;
        
        if (a->name == name) {
            return a;
        }
    }
    
    return NULL;
}

std::vector<Attribute*> Object::getAttributes() {
    return attributes;
}

std::string Object::to_string() const {
    return std::string("<" + isa->name + ":" + id + ">");
}

std::ostream& operator<<(std::ostream& s, const Object& o) {
    s << o.to_string();
    
    return s;
}
