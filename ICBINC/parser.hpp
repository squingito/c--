#include "tokenizer.hpp"
#include "syntaxBlocks.hpp"
#include <exception>
#include "unexpectedTokException.hpp"
#include <vector>

#ifndef PARSER_HEADER_GUARD
#define PARSER_HEADER_GUARD


class parser {
    public:
        parser(tokenizer* tokenizer);
        ~parser();
        static parser* createParser(std::string fileName);
        valueBlockSB* parseTest() {
            return parseExpression(0);
        }


    private:
        tokenizer* tokenReader;
        typeHandler* th;

        int64_t getPrecedence(tokenSubType);
        valueBlockSB* parseRawVal();
        valueBlockSB* parsePostFixVal();
        valueBlockSB* parsePreFixVal();
        valueBlockSB* parseExpression(int64_t);



        

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

#endif