#include "value.h"

Value::Value() {
    val.is_nil = 1;
    value_type = Value::NIL;
}

Value::Value(int intval) {
    val.i32val = intval;
    value_type = Value::INT32;
}

Value::Value(std::string str) {
    val.strval = new std::string(str);
    value_type = Value::STRING;
}

Value::Value(bool b) {
    val.boolval = b;
    value_type = Value::BOOL;
}

Value::Value(Object* obj) {
    val.objval = obj;
    value_type = Value::OBJECT;
}

Value::Value(Class* cla) {
    val.classval = cla;
    value_type = Value::CLASS;
}

std::int32_t Value::getInt32() const {
    return val.i32val;
}

std::string Value::getString() const  {
    return *(val.strval);
}

Object* Value::getObject() const  {
    return val.objval;
}

Class* Value::getClass() const {
    return val.classval;
}

bool Value::is(vtype t) const {
    return value_type == t;
}

bool Value::isNil() const {
    return value_type == Value::NIL;
}

bool Value::isNumeric() const {
    return is(Value::INT32) || is(Value::INT64);
}

bool Value::isBool() const {
    return is(Value::BOOL);
}

bool Value::isString() const {
    return is(Value::STRING);
}

bool Value::isObject() const {
    return value_type == Value::OBJECT;
}

bool Value::isClass() const {
    return value_type == Value::CLASS;
}

Value Value::operator+(const Value& v) {
    if (this->isNumeric() && v.isNumeric()) {
        return Value(getInt32() + v.getInt32());
    }
    
    if (this->isString() && v.isString()) {
        return Value(getString() + v.getString());
    }
}

Value Value::operator-(const Value& v) {
    if (this->isNumeric() && v.isNumeric()) {
        return Value(getInt32() - v.getInt32());
    }
}

Value Value::operator*(const Value& v) {
    if (this->isNumeric() && v.isNumeric()) {
        return Value(getInt32() * v.getInt32());
    }
    if (this->isNumeric() && v.isString()) {
        int n = getInt32();
        std::string rhs = v.getString();
        std::string s;
        
        for (int i = 0 ; i < n ; i++) {
            s += rhs;
        }
        
        return Value(s);
    }
}

Value Value::operator/(const Value& v) {
    if (this->isNumeric() && v.isNumeric()) {
        return Value(getInt32() / v.getInt32());
    }
}

std::ostream& operator<<(std::ostream& s, const Value &v) {
    switch (v.value_type) {
        case Value::INT32:
        case Value::INT64:
            s << v.val.i32val; break;
        case Value::STRING:
            s << "'" << *(v.val.strval) << "'"; break;
        case Value::BOOL:
            s << (v.val.boolval ? "true" : "false"); break;
        case Value::OBJECT:
            s << v.val.objval->to_string(); break;
        case Value::CLASS:
            s << v.val.classval->to_string(); break;
        case Value::NIL:
            s << "nil"; break;
    }
    
    return s;
}
