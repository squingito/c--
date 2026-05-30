#include "syntaxBlocks.hpp"

int64_t parType = 0;

std::string printManager(std::string in) {
    std::string ret;
    switch (parType) {
        case 0:
            {
                ret = "(" + in + ")";
                break;
            }
        case 1:
            {
                ret = "[" + in + "]";
                break;
            }
        default:
            {
                ret = "{" + in + "}";
                break;
            }
    }
    parType = (parType + 1) % 3;
    return ret;
}

std::string printManager(std::string in, std::string in2) {
    std::string ret;
    switch (parType) {
        case 0:
            {
                ret = "(" + in  + ", " + in2 + ")";
                break;
            }
        case 1:
            {
                ret = "[" + in + ", " + in2 + "]";
                break;
            }
        default:
            { 
                ret = "{" + in + ", " + in2 + "}";
                break;
            }
    }
    parType = (parType + 1) % 3;
    return ret;
}
