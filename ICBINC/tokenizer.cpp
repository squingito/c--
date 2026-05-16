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

tokenizer::tokenizer(fileReader* fr) {
    this->fr = fr;
    this->eot = false;
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

token* tokenizer::lookAhead(int64_t index) {
    if (index > tokens.size() - 1) {
        return nullptr; // looking to far ahead
    } else {
        return tokens.at(index);
    }
}

token* tokenizer::next() {
    if (tokens.size() >= 1) {
        token* toRet = tokens.at(0);
        tokens.pop_front();
        if (!fr->isEof() && tokens.size() < TOKEN_BUF_SIZE) fill(9);
        if (last != nullptr) delete last;
        last = toRet;
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
    if (fr->isEof()) eot = true;
}

void tokenizer::parseTok() {
    eatWhitespace();
    char nextChar = fr->lookAhead(0);

    if ((nextChar >= 'a' && nextChar <= 'z') || (nextChar >= 'A' && nextChar <= 'Z') || nextChar == '_') {
        parseWord();
    } else if (nextChar >= '0' && nextChar <= '9') {
        parseLit();
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
    // check if string is keyword
    if (false /* is keyword*/) {
        newTok = new keywordTok(word, start);
    } else {
        newTok = new identTok(word, start);
    }
    tokens.push_back(newTok);
}

void tokenizer::parseLit() {
    litTok* tok = new litTok("", fr->getCharPos());
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
    tok->val = std::stoi(tok->str);
    tokens.push_back(tok);
}


bool tokenizer::tryParseOp(char in) {
    switch (in) {
        
        case '*':
            {
                operationTok* tok = new operationTok("", fr->getCharPos());
                fr->next();
                if (fr->lookAhead(0) == '=') {
                    fr->next();
                    tok->str.append("*=");
                } else {
                    tok->str.push_back('*');
                }
                tokens.push_back(tok);
                return true;
            }
        case '/':
            {
                operationTok* tok = new operationTok("", fr->getCharPos());
                fr->next();
                if (fr->lookAhead(0) == '=') {
                    fr->next();
                    tok->str.append("/=");
                } else {
                    tok->str.push_back('/');
                }
                tokens.push_back(tok);
                return true;
            }
        case '%':
            {
                operationTok* tok = new operationTok("", fr->getCharPos());
                fr->next();
                if (fr->lookAhead(0) == '=') {
                    fr->next();
                    tok->str.append("%=");
                } else {
                    tok->str.push_back('%');
                }
                tokens.push_back(tok);
                return true;
            }
        case '+':
            {
                operationTok* tok = new operationTok("", fr->getCharPos());
                fr->next();
                if (fr->lookAhead(0) == '+') {
                    fr->next();
                    tok->str.append("++");
                } else if (fr->lookAhead(0) == '=') {
                    fr->next();
                    tok->str.append("+=");
                } else {
                    tok->str.push_back('+');
                }
                tokens.push_back(tok);
                return true;
            }

        case '-':
            {
                operationTok* tok = new operationTok("", fr->getCharPos());
                fr->next();
                if (fr->lookAhead(0) == '-') {
                    fr->next();
                    tok->str.append("--");
                } else if (fr->lookAhead(0) == '=') {
                    fr->next();
                    tok->str.append("-=");
                } else if (fr->lookAhead(0) == '>') {
                    fr->next();
                    tok->str.append("->");
                } else {
                    tok->str.push_back('-');
                }
                tokens.push_back(tok);
                return true;
            }

        case '=':
            {
                operationTok* tok = new operationTok("", fr->getCharPos());
                fr->next();
                if (fr->lookAhead(0) == '=') {
                    fr->next();
                    tok->str.append("==");
                } else {
                    tok->str.push_back('=');
                }
                tokens.push_back(tok);
                return true;
            }
        case '>':
            {
                operationTok* tok = new operationTok("", fr->getCharPos());
                fr->next();
                if (fr->lookAhead(0) == '=') {
                    fr->next();
                    tok->str.append(">=");
                } else if (fr->lookAhead(0) == '>') {
                    fr->next();
                    tok->str.append(">>");
                } else {
                    tok->str.push_back('>');
                }
                tokens.push_back(tok);
                return true;
            }
        case '<':
            {
                operationTok* tok = new operationTok("", fr->getCharPos());
                fr->next();
                if (fr->lookAhead(0) == '=') {
                    fr->next();
                    tok->str.append("<=");
                } else if (fr->lookAhead(0) == '<') {
                    fr->next();
                    tok->str.append("<<");
                } else {
                    tok->str.push_back('<');
                }
                tokens.push_back(tok);
                return true;
            }
        case '!':
            {
                operationTok* tok = new operationTok("", fr->getCharPos());
                fr->next();
                if (fr->lookAhead(0) == '=') {
                    fr->next();
                    tok->str.append("!=");
                } else {
                    tok->str.push_back('!');
                }
                tokens.push_back(tok);
                return true;
            }
        case '&':
            {
                operationTok* tok = new operationTok("", fr->getCharPos());
                fr->next();
                if (fr->lookAhead(0) == '&') {
                    fr->next();
                    tok->str.append("&&");
                } else {
                    tok->str.push_back('&');
                }
                tokens.push_back(tok);
                return true;
            }
        case '|':
            {
                operationTok* tok = new operationTok("", fr->getCharPos());
                fr->next();
                if (fr->lookAhead(0) == '|') {
                    fr->next();
                    tok->str.append("||");
                } else {
                    tok->str.push_back('|');
                }
                tokens.push_back(tok);
                return true;
            }
        case '~':
            {
                operationTok* tok = new operationTok("", fr->getCharPos());
                fr->next();
                tok->str.push_back('~');
                tokens.push_back(tok);
                return true;
            }
        case '^':
            {
                operationTok* tok = new operationTok("", fr->getCharPos());
                fr->next();
                tok->str.push_back('^');
                tokens.push_back(tok);
                return true;
            }
        case '?':
            {
                operationTok* tok = new operationTok("", fr->getCharPos());
                fr->next();
                tok->str.push_back('?');
                tokens.push_back(tok);
                return true;
            }
        case ':':
            if (fr->lookAhead(0) == ':') {
                return false;
            } else {
                operationTok* tok = new operationTok("", fr->getCharPos());
                fr->next();
                tok->str.push_back('~');
                tokens.push_back(tok);
                return true;
            }
        case '.':
            {
                operationTok* tok = new operationTok("", fr->getCharPos());
                fr->next();
                tok->str.push_back('.');
                tokens.push_back(tok);
                return true;
            }
        default:
            return false;
    }
}

bool tokenizer::tryParseDelim(char in) {
    switch (in) {
        case '(':
        case '{':
        case '[':
        case ')':
        case '}':
        case ']':
        case ';':
        case ',':
            {
                operationTok* tok = new operationTok("", fr->getCharPos());
                fr->next();
                tok->str.push_back(in);
                tokens.push_back(tok);
                return true;
            }
        case ':':
            {   
                // we can only get here if :: is next, op parse would grab it otherwise
                operationTok* tok = new operationTok("", fr->getCharPos());
                fr->next();
                fr->next();
                tok->str.append("::");
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