#include "fileReader.hpp"
#include <unordered_map>

#ifndef TOKENS_HEADER_GUARD
#define TOKENS_HEADER_GUARD

enum tokenType: int8_t {

    eofTok = -1,
    undefinedTok = 0,
    identTok = 1,
    keywordTok = 2,
    operationTok = 3,
    delimTok = 4,
    intTok = 5, 
    typeTok = 6
    

};


std::string tokenTypeToString(tokenType type);

enum tokenSubType: uint8_t {
    undefinedSub = 0,

    // op types
    opScopeRes,
    opInc,
    opDec,
    opRefElementSelect,
    opPointerElementSelect,
    opLogicalNot,
    opBitwiseNot,
    opCast,
    opAddress,
    opStar,
    opBinaryDiv,
    opBinaryMod,
    opPlus,
    opMinus,
    opShiftLeft,
    opShiftRight,
    opLessThen,
    opLessThenEq,
    opGreaterThen,
    opGreaterThenEq,
    opEq,
    opNotEq,
    opBitwiseAnd,
    opBitwiseXor,
    opBitwiseOr,
    opLogicalAnd,
    opLogicalOr,
    opIf,
    opElse,
    opAssign,
    opAssAdd,
    opAssMinus,
    opAssTimes,
    opAssDiv,
    opAssMod,
    opAssLeftShift,
    opAssRightShift,
    opAssBitAnd,
    opAssBitXor,
    opAssBitOr,
    

    //DelimTypes
    delimLeftPar,
    delimRightPar,
    delimLeftBrac,
    delimRightBrac,
    delimLeftCurly,
    delimRightCurly,
    delimComma,
    delimSemiCol,

    //keywords
    kwIf,
    kwElse,
    kwWhile,
    kwFor,
    kwDo,
    kwRet,
    kwBreak,
    kwContinue,
    kwSwitch,
    kwDefault,
    kwCase,
    kwConst,
    kwStatic,
    kwClass,
    kwStruct,
    kwUnion,
    kwEnum,
    kwTypedef,
    kwThis,
    kwTrue,
    kwFalse,
    kwNullptr,
    kwPublic,
    kwPrivate,
    kwProtected,
    kwNew,
    kwDelete,
};



std::string tokenSubTypeToString(tokenSubType type);



static const std::unordered_map<std::string, tokenSubType> keywords = {
    {"if", kwIf},
    {"else", kwElse},
    {"while", kwWhile},
    {"for", kwFor},
    {"do", kwDo},
    {"return", kwRet},
    {"break", kwBreak},
    {"continue", kwContinue},
    {"switch", kwSwitch},
    {"default", kwDefault},
    {"case", kwCase},
    {"const", kwConst},
    {"static", kwStatic},
    {"class", kwClass},
    {"struct", kwStruct},
    {"union", kwUnion},
    {"enum", kwEnum},
    {"typedef", kwTypedef},
    {"this", kwThis},
    {"true", kwTrue},
    {"false", kwFalse},
    {"nullptr", kwNullptr},
    {"public", kwPublic},
    {"private", kwPrivate},
    {"protected", kwProtected},
    {"new", kwNew},
    {"delete", kwDelete},
};

struct token {
    token(std::string in, charPos pos, tokenType type) {
        this->pos = pos;
        this->type = type;
        str = in;
    }
    std::string str;
    charPos pos;
    tokenType type;
    tokenSubType subType;

};



#endif