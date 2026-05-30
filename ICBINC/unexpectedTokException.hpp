
#include <exception>
#include "tokens.hpp"

#ifndef UNEXPECTED_TOK_EXCEPTION_HEADER_GUARD
#define UNEXPECTED_TOK_EXCEPTION_HEADER_GUARD

class unexpectedTokException: public std::exception {
        public:
            std::string message;
            token* tok;
            tokenType expectedTokType;
            tokenSubType expectedTokSubType;

            unexpectedTokException(token* in, tokenType expectedType, tokenSubType expectedSubType, std::string msg) {
                message = "Unexpected Token at line " + std::to_string(in->pos.line) + ", col " + std::to_string(in->pos.col);
                if (expectedType != undefinedTok) {
                    message += ": Expected a token with type: " + tokenTypeToString(expectedType) + " (" + tokenTypeToString(in->type) + " was found)";
                }  else  {
                    message += ": Expected a " + msg + " (" + tokenTypeToString(in->type) + " was found)";
                }
                if (expectedSubType != undefinedSub) message += " with a subType: " + tokenSubTypeToString(expectedSubType) + " (" + tokenSubTypeToString(in->subType) + " was found)\n";
                tok = in;
                expectedTokType = expectedType;
                expectedTokSubType = expectedSubType;

            }
            const char* what() const noexcept override {
                return message.c_str();
            }
};

#endif