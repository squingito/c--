#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <string>
#include <cstring>

#ifndef FILE_READER_HEADER_GUARD
#define FILE_READER_HEADER_GUARD


#define FILE_BUF_SIZE 4096

struct charPos {
    int64_t line;
    int64_t col;
};

class fileReader {
    public:
        fileReader(int64_t fd, std::string fileName);
        ~fileReader();
        int64_t closeFileReader();
        char lookAhead(int64_t);
        char next();
        int64_t getLine();
        int64_t getCol();
        charPos getCharPos();
        bool isClosed();
        bool isEof();


    private:

        std::string filename;
        int64_t fd;
        int64_t line;
        int64_t column;
        int64_t charCount;
        char* buffer;
        int64_t bufIndex;
        int64_t numInBuf;
        bool eof;
        bool closed;

        void refill();

};

fileReader* startReader(std::string);

#endif