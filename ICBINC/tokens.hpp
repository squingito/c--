#include "fileReader.hpp";

#ifndef TOKENS_HEADER_GUARD
#define TOKENS_HEADER_GUARD


struct token {
    charPos pos;
    std::string str;
};

struct identTok: public token {


    identTok(std::string in, charPos inPos) {
        pos = inPos;
        str = in;
    }


};

struct keywordTok: public token {


    keywordTok(std::string in, charPos inPos) {
        pos = inPos;
        str = in;
    }
};

struct operationTok: public token {
    operationTok(std::string in, charPos inPos) {
        pos = inPos;
        str = in;
    }

};

struct litTok: public token {
    litTok(std::string in, charPos inPos) {
        pos = inPos;
        str = in;
    }


    int64_t val;
};

#endif