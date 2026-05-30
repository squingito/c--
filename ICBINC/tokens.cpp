#include "tokens.hpp"

std::string tokenSubTypeToString(tokenSubType type) {
    switch (type) {

        case undefinedSub: return "undefinedSub";

        // op types
        case opScopeRes: return "opScopeRes";
        case opInc: return "opInc";
        case opDec: return "opDec";
        case opRefElementSelect: return "opRefElementSelect";
        case opPointerElementSelect: return "opPointerElementSelect";
        case opLogicalNot: return "opLogicalNot";
        case opBitwiseNot: return "opBitwiseNot";
        case opCast: return "opCast";
        case opAddress: return "opAddress";
        case opStar: return "opBinaryMulti";
        case opBinaryDiv: return "opBinaryDiv";
        case opBinaryMod: return "opBinaryMod";
        case opPlus: return "opPlus";
        case opMinus: return "opMinus";
        case opShiftLeft: return "opShiftLeft";
        case opShiftRight: return "opShiftRight";
        case opLessThen: return "opLessThen";
        case opLessThenEq: return "opLessThenEq";
        case opGreaterThen: return "opGreaterThen";
        case opGreaterThenEq: return "opGreaterThenEq";
        case opEq: return "opEq";
        case opNotEq: return "opNotEq";
        case opBitwiseAnd: return "opBitwiseAnd";
        case opBitwiseXor: return "opBitwiseXor";
        case opBitwiseOr: return "opBitwiseOr";
        case opLogicalAnd: return "opLogicalAnd";
        case opLogicalOr: return "opLogicalOr";
        case opIf: return "opIf";
        case opElse: return "opElse";
        case opAssign: return "opAssign";
        case opAssAdd: return "opAssAdd";
        case opAssMinus: return "opAssMinus";
        case opAssTimes: return "opAssTimes";
        case opAssDiv: return "opAssDiv";
        case opAssMod: return "opAssMod";
        case opAssLeftShift: return "opAssLeftShift";
        case opAssRightShift: return "opAssRightShift";
        case opAssBitAnd: return "opAssBitAnd";
        case opAssBitXor: return "opAssBitXor";
        case opAssBitOr: return "opAssBitOr";

        // delim types
        case delimLeftPar: return "delimLeftPar";
        case delimRightPar: return "delimRightPar";
        case delimLeftBrac: return "delimLeftBrac";
        case delimRightBrac: return "delimRightBrac";
        case delimLeftCurly: return "delimLeftCurly";
        case delimRightCurly: return "delimRightCurly";
        case delimComma: return "delimComma";
        case delimSemiCol: return "delimSemiCol";

        // keywords
        case kwIf: return "kwIf";
        case kwElse: return "kwElse";
        case kwWhile: return "kwWhile";
        case kwFor: return "kwFor";
        case kwDo: return "kwDo";
        case kwRet: return "kwRet";
        case kwBreak: return "kwBreak";
        case kwContinue: return "kwContinue";
        case kwSwitch: return "kwSwitch";
        case kwDefault: return "kwDefault";
        case kwCase: return "kwCase";
        case kwConst: return "kwConst";
        case kwStatic: return "kwStatic";
        case kwClass: return "kwClass";
        case kwStruct: return "kwStruct";
        case kwUnion: return "kwUnion";
        case kwEnum: return "kwEnum";
        case kwTypedef: return "kwTypedef";
        case kwThis: return "kwThis";
        case kwTrue: return "kwTrue";
        case kwFalse: return "kwFalse";
        case kwNullptr: return "kwNullptr";
        case kwPublic: return "kwPublic";
        case kwPrivate: return "kwPrivate";
        case kwProtected: return "kwProtected";
        case kwNew: return "kwNew";
        case kwDelete: return "kwDelete";

        default:
            return "Unknown";
    }
}

std::string tokenTypeToString(tokenType type) {
    switch (type) {

        case undefinedTok:
            return "undefinedTok";

        case identTok:
            return "identTok";

        case keywordTok:
            return "keywordTok";

        case operationTok:
            return "operationTok";

        case delimTok:
            return "delimTok";

        case intTok:
            return "intTok";

        default:
            return "Unknown";
    }
}