#include "typeHandler.hpp"

typeHandler::typeHandler() {
    init();
}

valueType* typeHandler::searchType(std::string name, int64_t pointerLev) {
    typeKey key;
    key.name = name;
    key.pointerLev = pointerLev;
    key.cat = searchName;
    auto cur = map.find(key);
    if (cur != map.end()) {
        return cur->second;
    } else if ((key.pointerLev != 0 && (key.pointerLev = 0, (cur = map.find(key), cur != map.end())))) {
        valueType* newType = new pointerType(searchType(name, 0), pointerLev);
        insert(name, pointerLev, newType, false);
        return newType;
    } else {
        return nullptr;
    }

}

valueType* typeHandler::searchType(valueType* retType, std::vector<valueType*> argsType, int64_t pointerLev) {
    typeKey key;
    key.pointerLev = pointerLev;
    key.cat = searchFunction;
    key.retType = retType;
    key.args = argsType;
    auto cur = map.find(key);
    if (cur != map.end()) {
        return cur->second;
    } else if ((key.pointerLev != 0 && (key.pointerLev = 0, (cur = map.find(key), cur != map.end())))) {
        valueType* newType = new pointerType(searchType(retType, argsType, 0), pointerLev);  
        insert(retType, argsType, pointerLev, newType);
        return newType;
    } else {
        return nullptr;
    }
}

int64_t typeHandler::insert(std::string name, int64_t pointerLev, valueType* in, bool exist=false) {
    typeKey key;
    key.name = name;
    key.pointerLev = pointerLev;
    key.cat = searchName;
    auto cur = map.find(key);
    if (cur != map.end()) return TYPE_INSERT_ERROR;
    map[key] = in;
    if (!exist) uniqueTypes.push_back(in);
    return TYPE_INSERT_OK;
}

int64_t typeHandler::insert(valueType* retType, std::vector<valueType*> argsType, int64_t pointerLev, valueType* in) {
    typeKey key;
    key.retType = retType;
    key.args = argsType;
    key.pointerLev = pointerLev;
    key.cat = searchFunction;
    auto cur = map.find(key);
    if (cur != map.end()) return TYPE_INSERT_ERROR;
    map[key] = in;
    uniqueTypes.push_back(in);
    return TYPE_INSERT_OK;
}

int64_t typeHandler::alius(std::string name, int64_t pointerLev, valueType* mapping) {
    return insert(name, pointerLev, mapping, true);
}

void typeHandler::init() {
    baseType* tVoidType = new baseType(voidType);
    insert("void", 0, tVoidType);


    baseType* tI8Type = new baseType(i8Type);
    insert("i8", 0, tI8Type);
    insert("byte", 0, tI8Type, true);

    baseType* tuI8Type = new baseType(ui8Type);
    insert("ui8", 0, tuI8Type);
    insert("ubyte", 0, tuI8Type, true);


    baseType* tI16Type = new baseType(i16Type);
    insert("i16", 0, tI16Type);
    insert("word", 0, tI16Type, true);
    
    baseType* tuI16Type = new baseType(ui16Type);
    insert("ui16", 0, tuI16Type);
    insert("uword", 0, tuI16Type, true);


    baseType* tI32Type = new baseType(i32Type);
    insert("i32", 0, tI32Type);
    insert("int", 0, tI32Type, true);
    
    baseType* tuI32Type = new baseType(ui32Type);
    insert("ui32", 0, tuI32Type);
    insert("uint", 0, tuI32Type, true);


    baseType* tI64Type = new baseType(i64Type);
    insert("i64", 0, tI64Type);
    insert("long", 0, tI64Type, true);
    
    baseType* tuI64Type = new baseType(ui64Type);
    insert("ui64", 0, tuI64Type);
    insert("ulong", 0, tuI64Type, true);


    baseType* tFloatType = new baseType(floatType);
    insert("float", 0, tFloatType);
    
    baseType* tDoubleType = new baseType(doubleType);
    insert("double", 0, tDoubleType);

}

typeHandler::~typeHandler() {
    for (std::size_t i = uniqueTypes.size() - 1; i > 0; i--) {
        delete uniqueTypes[i];
        uniqueTypes.pop_back();
    }
    delete uniqueTypes[0];
}