#ifndef _VALUE_H
#define _VALUE_H

#include <iostream>
#include "object.h"

#define NIL_VALUE Value()

class Value {
    
public:
    typedef enum { INT32, INT64, STRING, BOOL, NIL, OBJECT, CLASS } vtype;
    
    union uval {
        bool is_nil;
        int i32val;
        std::string* strval;
        bool boolval;
        Object* objval;
        Class* classval;
    };
    
    union uval val;
    vtype value_type;
    
    Value();
    Value(int);
    Value(std::string);
    Value(bool);
    Value(Object* obj);
    Value(Class* cl);
    
    int getInt32() const;
    int64_t getInt64() const;
    bool getBool() const;
    std::string getString() const;
    Object* getObject() const;
    Class* getClass() const;
    
    bool is(vtype) const;
    bool isNumeric() const;
    bool isString() const;
    bool isBool() const;
    bool isNil() const;
    bool isObject() const;
    bool isClass() const;
    
    Value operator+(const Value& v);
    Value operator-(const Value& v);
    Value operator*(const Value& v);
    Value operator/(const Value& v);
};

std::ostream& operator<<(std::ostream& s, const Value &v);

#endif
