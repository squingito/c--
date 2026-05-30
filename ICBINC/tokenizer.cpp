/*
#ifndef TOKENIZER_HEADER_GUARD
#define TOKENIZER_HEADER_GUARD

#include "tokens.hpp"
#include <vector>
#define TOKEN_BUF_SIZE 64

class tokenizer {
    public:
        tokenizer(std::string);
        ~tokenizer();
        token* lookAhead(int64_t);
        token* next();

    private:
        void parseTok();
        void parseWord();
        void parseLit();
        void parseOp();

        std::vector<token*> tokens;
        fileReader fr;
        


};

#endif
*/

#include "tokenizer.hpp"

tokenizer* createTokenizer(std::string name) {
    fileReader* fr = startReader(name);
    
    if (fr) {
        return new tokenizer(fr);
    } else return nullptr;
}

tokenizer::tokenizer(fileReader* fr) : lastHold("", {0,0}, undefinedTok) {
    this->fr = fr;
    this->eot = false;
    th = typeHandler();
    last = nullptr;
    fill(TOKEN_BUF_SIZE);
    
}

tokenizer::~tokenizer() {
    delete fr;
    for (int i = 0; i < tokens.size(); i++) {
        delete tokens.back();
        tokens.pop_back();
    }
}

typeHandler* tokenizer::getTypeHandler() {
    return &th;
}

token* tokenizer::lookAhead(int64_t index) {
    int a = 5;
    if (index > tokens.size() - 1 || tokens.size() == 0) {
        return nullptr; // looking to far ahead
    } 
    token* toRet = tokens.at(index);
    if (toRet->type == identTok && th.searchType(toRet->str, 0)) {
        toRet->type = typeTok;
        toRet->subType = undefinedSub;
    }
    return toRet;
    
}

token* tokenizer::next() {
    if (tokens.size() >= 1) {
        token* toRet = tokens.at(0);
        if (toRet->type == identTok && th.searchType(toRet->str, 0)) {
            toRet->type = typeTok;
            toRet->subType = undefinedSub;
        }
        tokens.pop_front();
        if (!fr->isEof() && tokens.size() < TOKEN_BUF_SIZE) fill(9);
        if (last != nullptr) last = &lastHold;
        lastHold = *toRet;
        return toRet;
    } else return nullptr;
}

token* tokenizer::prev() {
    return last;
}

void tokenizer::fill(int64_t numToFill) {
    for (int i = 0; i < numToFill && !fr->isEof(); i++) {
        parseTok();
    }
    if (fr->isEof() && !eot) {
        eot = true;
        charPos pos = fr->getCharPos();
        pos.col = pos.col + 1;
        token* eotToken = new token("", pos, eofTok);
        

        tokens.push_back(eotToken);
    }
    
}

void tokenizer::parseTok() {
    eatWhitespace();
    char nextChar = fr->lookAhead(0);

    if ((nextChar >= 'a' && nextChar <= 'z') || (nextChar >= 'A' && nextChar <= 'Z') || nextChar == '_') {
        parseWord();
    } else if (nextChar >= '0' && nextChar <= '9') {
        parseLit();
    } else if (nextChar == '.') {
        char nextNextChar = fr->lookAhead(1);
        if (nextChar >= '0' && nextChar <= '9') {
            parseLit();
        } else {
            tryParseOp(nextChar);
        }
    } else if (tryParseOp(nextChar)) {
    } else if (tryParseDelim(nextChar)) {
    } else if (nextChar == '\0') {
        this->eot = true;
        return;
    } else {
        exit(0);
    }

}

void tokenizer::parseWord() {
    std::string word = "";
    charPos start = fr->getCharPos();
    word.push_back(fr->lookAhead(0));
    fr->next();
    while (!fr->isEof()) {
        char nextChar = fr->lookAhead(0);
        if ((nextChar >= 'a' && nextChar <= 'z') || (nextChar >= 'A' && nextChar <= 'Z') || (nextChar >= '0' && nextChar <= '9') || nextChar == '_') {
            word.push_back(nextChar);
            fr->next();
        } else {
            break;
        }
    }
    token* newTok;
    auto lookup = keywords.find(word);
    // check if string is keyword
    if (lookup != keywords.end()) {
        newTok = new token(word, start, keywordTok);
        newTok->subType = lookup->second;
    } else {

        newTok = new token(word, start, identTok);
        newTok->subType = undefinedSub;
        

        
    }
    tokens.push_back(newTok);
}

void tokenizer::parseLit() {
    // needs rewrite for other lits
    token* tok = new token("", fr->getCharPos(), intTok);
    tok->subType = undefinedSub;
    tok->str.push_back(fr->lookAhead(0));
    fr->next();
    while (!fr->isEof()) {
        char nextChar = fr->lookAhead(0);
        if (nextChar >= '0' && nextChar <= '9') {
            tok->str.push_back(nextChar);
            fr->next();
        } else {
            break;
        }
    }
    tokens.push_back(tok);
}


bool tokenizer::tryParseOp(char in) {
    switch (in) {
        
        case '*':
            {
                token* tok = new token("", fr->getCharPos(), operationTok);
                fr->next();
                if (fr->lookAhead(0) == '=') {
                    fr->next();
                    tok->str.append("*=");
                    tok->subType = opAssTimes;
                } else {
                    tok->str.push_back('*');
                    tok->subType = opStar;
                }
                tokens.push_back(tok);
                return true;
            }
        case '/':
            {
                token* tok = new token("", fr->getCharPos(), operationTok);
                fr->next();
                if (fr->lookAhead(0) == '=') {
                    fr->next();
                    tok->str.append("/=");
                    tok->subType = opAssDiv;
                } else {
                    tok->str.push_back('/');
                    tok->subType = opBinaryDiv;
                }
                tokens.push_back(tok);
                return true;
            }
        case '%':
            {
                token* tok = new token("", fr->getCharPos(), operationTok);
                fr->next();
                if (fr->lookAhead(0) == '=') {
                    fr->next();
                    tok->str.append("%=");
                    tok->subType = opAssMod;
                } else {
                    tok->str.push_back('%');
                    tok->subType = opBinaryMod;
                }
                tokens.push_back(tok);
                return true;
            }
        case '+':
            {
                token* tok = new token("", fr->getCharPos(), operationTok);
                fr->next();
                if (fr->lookAhead(0) == '+') {
                    fr->next();
                    tok->str.append("++");
                    tok->subType = opInc;
                } else if (fr->lookAhead(0) == '=') {
                    fr->next();
                    tok->str.append("+=");
                    tok->subType = opAssAdd;
                } else {
                    tok->str.push_back('+');
                    tok->subType = opPlus;
                }
                tokens.push_back(tok);
                return true;
            }

        case '-':
            {
                token* tok = new token("", fr->getCharPos(), operationTok);
                fr->next();
                if (fr->lookAhead(0) == '-') {
                    fr->next();
                    tok->str.append("--");
                    tok->subType = opDec;
                } else if (fr->lookAhead(0) == '=') {
                    fr->next();
                    tok->str.append("-=");
                    tok->subType = opAssMinus;
                } else if (fr->lookAhead(0) == '>') {
                    fr->next();
                    tok->str.append("->");
                    tok->subType = opPointerElementSelect;
                } else {
                    tok->str.push_back('-');
                    tok->subType = opMinus;
                }
                tokens.push_back(tok);
                return true;
            }

        case '=':
            {
                token* tok = new token("", fr->getCharPos(), operationTok);
                fr->next();
                if (fr->lookAhead(0) == '=') {
                    fr->next();
                    tok->str.append("==");
                    tok->subType = opEq;
                } else {
                    tok->str.push_back('=');
                    tok->subType = opAssign;
                }
                tokens.push_back(tok);
                return true;
            }
        case '>':
            {
                token* tok = new token("", fr->getCharPos(), operationTok);
                fr->next();
                if (fr->lookAhead(0) == '=') {
                    fr->next();
                    tok->str.append(">=");
                    tok->subType = opGreaterThenEq;
                } else if (fr->lookAhead(0) == '>') {
                    fr->next();
                    tok->str.append(">>");
                    tok->subType = opShiftRight;
                } else {
                    tok->str.push_back('>');
                    tok->subType = opGreaterThen;
                }
                tokens.push_back(tok);
                return true;
            }
        case '<':
            {
                token* tok = new token("", fr->getCharPos(), operationTok);
                fr->next();
                if (fr->lookAhead(0) == '=') {
                    fr->next();
                    tok->str.append("<=");
                    tok->subType = opLessThenEq;
                } else if (fr->lookAhead(0) == '<') {
                    fr->next();
                    tok->str.append("<<");
                    tok->subType = opShiftLeft;
                } else {
                    tok->str.push_back('<');
                    tok->subType = opLessThen;
                }
                tokens.push_back(tok);
                return true;
            }
        case '!':
            {
                token* tok = new token("", fr->getCharPos(), operationTok);
                fr->next();
                if (fr->lookAhead(0) == '=') {
                    fr->next();
                    tok->str.append("!=");
                    tok->subType = opNotEq;
                } else {
                    tok->str.push_back('!');
                    tok->subType = opLogicalNot;
                }
                tokens.push_back(tok);
                return true;
            }
        case '&':
            {
                token* tok = new token("", fr->getCharPos(), operationTok);
                fr->next();
                if (fr->lookAhead(0) == '&') {
                    fr->next();
                    tok->str.append("&&");
                    tok->subType = opLogicalAnd;
                } else {
                    tok->str.push_back('&');
                    tok->subType = opBitwiseAnd;
                }
                tokens.push_back(tok);
                return true;
            }
        case '|':
            {
                token* tok = new token("", fr->getCharPos(), operationTok);
                fr->next();
                if (fr->lookAhead(0) == '|') {
                    fr->next();
                    tok->str.append("||");
                    tok->subType = opLogicalOr;
                } else {
                    tok->str.push_back('|');
                    tok->subType = opBitwiseOr;
                }
                tokens.push_back(tok);
                return true;
            }
        case '~':
            {
                token* tok = new token("", fr->getCharPos(), operationTok);
                fr->next();
                tok->str.push_back('~');
                tokens.push_back(tok);
                tok->subType = opBitwiseNot;
                return true;
            }
        case '^':
            {
                token* tok = new token("", fr->getCharPos(), operationTok);
                fr->next();
                tok->str.push_back('^');
                tokens.push_back(tok);
                tok->subType = opBitwiseXor;
                return true;
            }
        case '?':
            {
                token* tok = new token("", fr->getCharPos(), operationTok);
                fr->next();
                tok->str.push_back('?');
                tokens.push_back(tok);
                tok->subType = opIf;
                return true;
            }
        case ':':
            if (fr->lookAhead(0) == ':') {
                return false;
            } else {
                token* tok = new token("", fr->getCharPos(), operationTok);
                fr->next();
                tok->str.push_back('~');
                tokens.push_back(tok);
                tok->subType = opElse;
                return true;
            }
        case '.':
            {
                token* tok = new token("", fr->getCharPos(), operationTok);
                fr->next();
                tok->str.push_back('.');
                tokens.push_back(tok);
                tok->subType = opRefElementSelect;
                return true;
            }
        default:
            return false;
    }
}

bool tokenizer::tryParseDelim(char in) {
    switch (in) {
        case '(':
            {
                token* tok = new token("", fr->getCharPos(), delimTok);
                fr->next();
                tok->str.push_back(in);
                tok->subType = delimLeftPar;
                tokens.push_back(tok);
                return true;
            }
        case '{':
            {
                token* tok = new token("", fr->getCharPos(), delimTok);
                fr->next();
                tok->str.push_back(in);
                tok->subType = delimLeftCurly;
                tokens.push_back(tok);
                return true;
            }
        case '[':
            {
                token* tok = new token("", fr->getCharPos(), delimTok);
                fr->next();
                tok->str.push_back(in);
                tok->subType = delimLeftBrac;
                tokens.push_back(tok);
                return true;
            }
        case ')':
            {
                token* tok = new token("", fr->getCharPos(), delimTok);
                fr->next();
                tok->str.push_back(in);
                tok->subType = delimRightPar;
                tokens.push_back(tok);
                return true;
            }
        case '}':
            {
                token* tok = new token("", fr->getCharPos(), delimTok);
                fr->next();
                tok->str.push_back(in);
                tok->subType = delimRightCurly;
                tokens.push_back(tok);
                return true;
            }
        case ']':
            {
                token* tok = new token("", fr->getCharPos(), delimTok);
                fr->next();
                tok->str.push_back(in);
                tok->subType = delimRightBrac;
                tokens.push_back(tok);
                return true;
            }
        case ';':
            {
                token* tok = new token("", fr->getCharPos(), delimTok);
                fr->next();
                tok->str.push_back(in);
                tok->subType = delimSemiCol;
                tokens.push_back(tok);
                return true;
            }
        case ',':
            {
                token* tok = new token("", fr->getCharPos(), delimTok);
                fr->next();
                tok->str.push_back(in);
                tok->subType = delimComma;
                tokens.push_back(tok);
                return true;
            }
        case ':':
            {   
                // we can only get here if :: is next, op parse would grab it otherwise
                token* tok = new token("", fr->getCharPos(), delimTok);
                fr->next();
                fr->next();
                tok->str.append("::");
                tok->subType = opScopeRes;
                tokens.push_back(tok);
                return true;
            }
        default:
            return false;
    }
}

void tokenizer::eatWhitespace() {
    char nextChar; 
    while (!fr->isEof()) {
        nextChar = fr->lookAhead(0);
        if (nextChar == ' ' || nextChar == '\n' || nextChar == '\t') {
            fr->next();
        } else return;
    }

}