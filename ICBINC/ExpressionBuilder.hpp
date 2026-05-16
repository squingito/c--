#include "tokens.hpp";


struct syntaxBlock {

};

struct valueBlockSB: syntaxBlock {

};

struct refBlockSB: valueBlockSB {
    refBlockSB(identTok* in) {
        
    }

};

struct intBlockSB: valueBlockSB {

};

struct postFixValSB: valueBlockSB {

};

struct preFixValSB: valueBlockSB {

};

struct binaryOpSB: valueBlockSB {

};

struct trinaryOpSB: valueBlockSB {

};





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