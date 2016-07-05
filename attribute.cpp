#include "attribute.h"

Attribute::Attribute(std::string name, Value* value, visibility_t visibility, bool is_static) :
    name(name), value(value), visibility(visibility), is_static(is_static) {
}
