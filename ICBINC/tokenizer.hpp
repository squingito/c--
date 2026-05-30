
#ifndef TOKENIZER_HEADER_GUARD
#define TOKENIZER_HEADER_GUARD

#include "tokens.hpp"
#include "typeHandler.hpp"
#include <deque>
#define TOKEN_BUF_SIZE 4


class tokenizer {
    public:
        tokenizer(fileReader* fr);
        ~tokenizer();
        token* lookAhead(int64_t);
        token* next();
        token* prev();
        typeHandler* getTypeHandler();

    private:
        void parseTok();
        void parseWord();
        void parseLit();
        bool tryParseOp(char);
        bool tryParseDelim(char);
        void eatWhitespace();
  
        void fill(int64_t);

        std::deque<token*> tokens;
        fileReader* fr;
        bool eot;
        token* last;
        token lastHold;
        typeHandler th;



};

tokenizer* createTokenizer(std::string);

#endif