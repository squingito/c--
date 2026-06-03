#include <string>
#include <vector>
#include <stdint.h>
#include <unordered_map>

#ifndef TYPE_HANDLER_GUARD
#define TYPE_HANDLER_GUARD

#define TYPE_INSERT_OK 0
#define TYPE_INSERT_ERROR 1


enum typeCatgories {
    inBuiltType,
    pointType,
    structType,
    funType,
    arrayType,

};

enum inBuiltTypes {
    unknownType = 0,
    voidType,
    i8Type,
    ui8Type,
    i16Type,
    ui16Type,
    i32Type,
    ui32Type,
    i64Type,
    ui64Type,
    floatType,
    doubleType,
    charType,

};

struct valueType {
    typeCatgories cat;
};

struct baseType: valueType {
    baseType(inBuiltTypes in) {
        kind = in;
        cat = inBuiltType;
    }
    inBuiltTypes kind;
};

struct pointerType: valueType {
    pointerType(valueType* in, uint64_t pointerLev) {
        pType = in;
        cat = pointType;
        lev = pointerLev;
    }
    valueType* pType;
    uint64_t lev;
};

struct member {
    member(std::string name, valueType* type) {
        this->name = name;
        this->typ = type;
    } 
    std::string name;
    valueType* typ;
};

struct structType: valueType {

    std::string name;
    std::vector<member> members;
};

struct functionType: valueType {
    functionType(valueType* retType, std::vector<valueType*> args) {
        cat = funType;
        this->args = args;
        this->retType = retType;
    }
    valueType* retType;
    std::vector<valueType*> args;
};

enum searchCatagorie {
    searchName,
    searchFunction,

};

struct typeKey {
    searchCatagorie cat;
    std::string name;
    uint64_t pointerLev;
    valueType* retType;
    std::vector<valueType*> args;

    bool operator==(const typeKey& other) const{
        if (cat != other.cat) return false;

        switch (cat) {
            case searchName:
                return name == other.name && pointerLev == other.pointerLev;
            default:
                return retType == other.retType && args == other.args && pointerLev == other.pointerLev;
        }
    }


};

struct typeKeyHash {
    std::size_t operator()(const typeKey& key) const {
        std::hash<std::size_t> tempSizeHasher;
        std::size_t hash = tempSizeHasher(static_cast<std::size_t>(key.cat));

        auto mix = [&hash](std::size_t in) {
            hash ^= in + 0x9e3779b97f4a7c15ULL + (hash << 6) + (hash >> 2);
        };
        
        mix(tempSizeHasher(static_cast<std::size_t>(key.pointerLev)));

        if (key.cat == searchName) {
            std::hash<std::string> tempStringHasher;
            mix(tempStringHasher(key.name));
        } else {
            std::hash<valueType*> tempValueTypeHasher;
            mix(tempValueTypeHasher(key.retType));

            for (std::size_t i = 0; i < key.args.size(); i++) {
                mix(tempValueTypeHasher(key.args[i]));
            }
        }

        return hash;
    }
};

class typeHandler {
public:
    typeHandler();
    ~typeHandler();

    valueType* searchType(std::string, int64_t pointerLev);
    valueType* searchType(valueType* retType, std::vector<valueType*> argsType, int64_t pointerLevel);
    int64_t insert(std::string, int64_t pointerLev, valueType* mapping, bool exist);
    int64_t insert(valueType* retType, std::vector<valueType*> argsType, int64_t pointerLevel, valueType*);
    int64_t alius(std::string, int64_t, valueType* mapping);
private:
    std::unordered_map<typeKey,valueType*, typeKeyHash> map;
    std::vector<valueType*> uniqueTypes;

    void init();

};

#endif