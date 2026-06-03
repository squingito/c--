#include "parser.hpp"

/*
class parser {
    public:
        parser(tokenizer* tokenizer);
        ~parser();
        static parser* createParser(std::string fileName);
        syntaxBlock* parseTest();


    private:
        tokenizer* tokenReader;



        valueBlockSB* parseRawVal()
        valueBlockSB* parsePostFixVal();
        valueBlockSB* parsePreFixVal();
        valueBlockSB* parseExpression();

        

};



*/

parser::parser(tokenizer* tokenizer) {
    tokenReader = tokenizer;
    th = tokenizer->getTypeHandler();
    
}

parser::~parser() {
    delete tokenReader;
}

parser* parser::createParser(std::string fileName) {
    tokenizer* tok = createTokenizer(fileName);
    if (tok) {
        return new parser(tok);
    } else {
        return nullptr;
    }
}

valueBlockSB* parser::parseRawVal() {
    token* cur = tokenReader->next();
    if (cur->type == identTok) {
        return new refBlockSB(cur);
    } else if (cur->type == intTok) {
        return new intBlockSB(cur);
    } else if (cur->type == delimTok && cur->subType == delimLeftPar) {
        valueBlockSB* hold = parseExpression(0);
        cur = tokenReader->next();
        if (cur->type != delimTok || cur->subType != delimRightPar) {
            throw unexpectedTokException(cur, delimTok, delimRightPar, "");
        }
        return hold;
    } else {
        throw unexpectedTokException(cur, undefinedTok, undefinedSub, "RawValue");
    }
    
}



valueBlockSB* parser::parsePostFixVal() {
    valueBlockSB* base = parseRawVal();
    token* lahead;
    tokenType tokType;
    tokenSubType tokSubType;
    
    do  {
        lahead = tokenReader->lookAhead(0);
        tokType = lahead->type;
        tokSubType = lahead->subType;
        if (tokSubType == opInc || tokSubType == opDec) {
            base = new postFixValSB(base, tokenReader->next());
        } else if (tokSubType == opRefElementSelect || tokSubType == opPointerElementSelect) {
            token* op = tokenReader->next();
            token* lahead = tokenReader->lookAhead(0);
            if (lahead->type != identTok) {
                throw unexpectedTokException(lahead, identTok, undefinedSub, "");
            }
            token* member = tokenReader->next();
            base = new binaryOpSB(base, op, new refBlockSB(member));
        } else if (tokSubType == delimLeftBrac) {
            token* op = tokenReader->next();
            valueBlockSB* inner = parseExpression(0);
            token* lahead = tokenReader->lookAhead(0);
            if (lahead->subType != delimRightBrac) throw unexpectedTokException(lahead, delimTok, delimRightBrac, "");
            tokenReader->next();
            base = new binaryOpSB(base, op, inner);
        } else if (tokSubType == delimLeftPar) {
            // parse funCall
        } else break;
        
    } while (1);
    return base;
}

valueBlockSB* parser::parsePreFixVal() {
    token* lahead;
    tokenType tokType;
    tokenSubType tokSubType;
    preFixValSB hold = preFixValSB();
    preFixValSB* last = &hold;

    do {
        lahead = tokenReader->lookAhead(0);
        tokType = lahead->type;
        tokSubType = lahead->subType;
        if (tokSubType == opInc || tokSubType == opDec || tokSubType == opPlus || tokSubType == opMinus || 
            tokSubType == opLogicalNot || tokSubType == opBitwiseNot || tokSubType == opStar || tokSubType == opAddress) {
           
            preFixValSB* temp = new preFixValSB(tokenReader->next(), nullptr);;
            last->valBlock = temp;
            last = temp;
        } else if (tokSubType == delimLeftPar) {
            token* lahead2 = tokenReader->lookAhead(1);
            if (lahead2->type == typeTok) {
                tokenReader->next();
                // make a parse type function
            } else {
                break;
            }
        } else if (tokSubType == kwNew || tokSubType == kwDelete) {
            // new and delete
        } else break;

    } while (1);
    last->valBlock = parsePostFixVal();
    return hold.valBlock;
}

int64_t parser::getPrecedence(tokenSubType op) {

    switch (op) {


        case opStar:
        case opBinaryDiv:
        case opBinaryMod:
            return 14; // table order 5

        case opPlus:
        case opMinus:
            return 13; // table order 6

        case opShiftLeft:
        case opShiftRight:
            return 12; // table order 7

        case opLessThen:
        case opLessThenEq:
        case opGreaterThen:
        case opGreaterThenEq:
            return 10; // table order 9

        case opEq:
        case opNotEq:
            return 9; // table order 10

        case opBitwiseAnd:
            return 8;

        case opBitwiseXor:
            return 7;

        case opBitwiseOr:
            return 6;

        case opLogicalAnd:
            return 5;

        case opLogicalOr:
            return 4;

        case opAssign:
        case opAssAdd:
        case opAssMinus:
        case opAssTimes:
        case opAssDiv:
        case opAssMod:
        case opAssLeftShift:
        case opAssRightShift:
        case opAssBitAnd:
        case opAssBitXor:
        case opAssBitOr:
            return 2; // table order 17

        case delimComma:
            return 1; // table order 18

        default:
            return -1;
    }
}

valueBlockSB* parser::parseExpression(int64_t minPres, bool skipComma=false) {
    valueBlockSB* left = parsePreFixVal();

    while (1) {
        token* op = tokenReader->lookAhead(0);

        int64_t pres = getPrecedence(op->subType);
        if (pres < minPres || (skipComma && pres == 1)) break;

        tokenReader->next();
        valueBlockSB* right;

        if (pres == 2) {
            right = parseExpression(pres, skipComma);
        } else {
            right = parseExpression(pres + 1, skipComma);
        }

        left = new binaryOpSB(left, op, right);
    }

    return left;
}

valueBlockSB* parser::parseType() {
    token* lahead = tokenReader->lookAhead(0);
    if (lahead->subType != delimRightBrac) throw unexpectedTokException(lahead, typeTok, undefinedSub, "");
}