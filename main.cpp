#include <iostream>
#include <map>
#include <sstream>
#include "instruction_parser.h"
#include "context.h"
#include "value.h"

int main(void) {
    
    Context* context = Context::create();
    InstructionParser* i = new InstructionParser(context);
    
    Class* A = new Class("A");
    context->registerClass(A);
    
    // context->scope->set("a", Value(42));
    // std::cout << context->scope->get("a") << std::endl;
    // 
    while (true) {
        std::string input;
        
        std::cout << "input > ";
        std::getline(std::cin, input);
        
        try {
            std::istringstream iss(input);
            Value res;

            for (std::string instr; std::getline(iss, instr, ';'); ) {
                res = i->parse(instr);
            }
            
            // only keep last returned value
            std::cout << "--> " << res << std::endl;
            
            // std::cout << "--> a = " << *(context->scope->get("a")) << std::endl;
        } catch (std::string e) {
            std::cout << e << std::endl;
        }
        
        i->clear();
    }
    
    return 0;
}
