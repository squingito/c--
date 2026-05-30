

#ifndef SYNTAX_BLOCKS_HEADER_GUARD
#define SYNTAX_BLOCKS_HEADER_GUARD

#include "tokens.hpp"
#include <iostream>

extern int64_t parType;
std::string printManager(std::string in);

std::string printManager(std::string in, std::string in2);


struct syntaxBlock {
    charPos pos;

};

struct valueBlockSB: syntaxBlock {
    virtual std::string toString() {
        return "";
    };
};

struct refBlockSB: valueBlockSB {
    refBlockSB(token* in) {
        if (in->type == identTok) {
            ref = in->str;
            pos = in->pos;
        } else {
            pos = {-1, -1};
        }
        delete in;
        
    }
    std::string toString() {
        std::string ret = "\"" + ref + "\"";
        return ret;
    }

    std::string ref;
};

struct intBlockSB: valueBlockSB {
    intBlockSB(token* in) {
        if (in->type == intTok) {
            val = std::stoi(in->str);
            pos = in->pos;
        } else {
            pos = {-1, -1};
        }
        delete in;
        
    }
    std::string toString() {
        return std::to_string(val);
    }

    int64_t val;



};

struct postFixValSB: valueBlockSB {
    postFixValSB(valueBlockSB* inBlock, token* in) {
        if (in->type == operationTok) {
            valBlock = inBlock;
            pos = in->pos;
            opType = in->subType;
        } else {
            pos = {-1, -1};
        }
        delete in;
    }
    std::string toString() {
        std::string ret = "PostFix_" + tokenSubTypeToString(opType) + printManager(valBlock->toString());
        return ret;
    }
    valueBlockSB* valBlock;
    tokenSubType opType;
};

struct preFixValSB: valueBlockSB {
    preFixValSB() {
        valBlock = nullptr;
    }
    preFixValSB(token* in, valueBlockSB* inBlock) {
        if (in->type == operationTok) {
            valBlock = inBlock;
            pos = in->pos;
            opType = in->subType;
        } else {
            pos = {-1, -1};
        }
        delete in;
    }
    std::string toString() {
        std::string ret = "PreFix_" + tokenSubTypeToString(opType) + printManager(valBlock->toString());
        return ret;
    }
    tokenSubType opType;
    valueBlockSB* valBlock;
};

struct binaryOpSB: valueBlockSB {
    binaryOpSB(valueBlockSB* leftBlock, token* op, valueBlockSB* rightBlock) {
        if (op->type == operationTok || op->type == delimTok) {
            this->leftBlock = leftBlock;
            this->rightBlock = rightBlock;
            pos = op->pos;
            opType = op->subType;
        } else {
            pos = {-1, -1};
        }
        delete op;
    }
    std::string toString() {
        std::string ret = tokenSubTypeToString(opType) + printManager(leftBlock->toString(), rightBlock->toString());
        return ret;
    }
    tokenSubType opType;
    valueBlockSB* leftBlock;
    valueBlockSB* rightBlock;

};
/*
struct trinaryOpSB: valueBlockSB {
    binaryOpSB(valueBlockSB* condBlock, token* op, valueBlockSB* rightBlock) {
        if (op->type == operationTok) {
            this->leftBlock = leftBlock;
            this->rightBlock = rightBlock;
            pos = in->pos;
        } else {
            pos = {-1, -1};
        }
        delete in;
    }
    valueBlockSB* condBlock;
    valueBlockSB* ifBlock;
    valueBlockSB* elseBlock;
};
*/




/*



Program →
    GlobalDeclaration*


GlobalDeclaration →
    FunDec
    VarDec


Statement →
    VarDec
    FunDec
    ControlStatement
    ExpressionStatement
    Block


Block →
    “{“ [Statement]* “}”


VarDec →
    Type VarInit [“,” VarInit]* ;


VarInit →
    ident [“=“ Expression]


FunDec →
    Type ident “(“ [ParamList] “)” FunBody


FunBody 
    VarDec
    ControlStatement
    ExpressionStatement
    Block


ParamList →
    Param [“,” Param]*


Param →
    Type ident


ExpressionStatement →
    Expression “;”


ControlStatement
    IfState
    ForState
    WhileState
    “Break” “;”
    “Continue” “;”
    “Return” [expression] “;”


IfState
    “if” “(“ expression “)” statement [“else” statement]


ForState
    “for” “(“ [forInit] “;” [Expression] “;” [expression] “)” statement


ForInit
    Type VarInit [“,” VarInit]* 
    Expression


WhileState
    “while” “(“ expression “)” statement


Expression → //using pratt 
    Value [op value]*


Value
    prefixVal 


PrefixVal
    op prefixVal
    PostfixVal


PostfixVal
    RawVal [op]*


RawVal
    lit
    ident
    “(“ Expression “)”
        

    

    


*/

#endif