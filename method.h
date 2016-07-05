#ifndef _METHOD_H
#define _METHOD_H

#include <string>
#include <vector>

class Method {
public:
    typedef enum { V_PRIVATE, V_PUBLIC, V_PROTECTED } visibility_t;
    
    bool is_static;
    
    std::string name;
    std::vector<std::string> arguments;
    std::string body;
    visibility_t visibility;
    
    Method(std::string, std::string, std::vector<std::string>, visibility_t visibility, bool is_static);
};

#endif
