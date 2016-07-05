#include "method.h"

Method::Method(std::string name, std::string body, std::vector<std::string> arguments, visibility_t visibility, bool is_static) :
    name(name), body(body), arguments(arguments), visibility(visibility), is_static(is_static) {
}
