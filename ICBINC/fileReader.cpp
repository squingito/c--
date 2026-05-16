#include "fileReader.hpp"


/*
#include <fstream>
#include <fcntl.h>

struct charPos {
    int64_t line;
    int64_t col;
};

class fileReader {
    public:
        fileReader(int64_t fd, std::string fileName);
        ~fileReader();
        int64_t close();
        char lookAhead(int64_t);
        char get();


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
*/

fileReader* startReader(std::string in) {
    int64_t fd = open(in.c_str(), O_RDONLY);
    if (fd > 0) {
        return new fileReader(fd, in);
    } else {
        return nullptr;
    }
}

fileReader::fileReader(int64_t fd, std::string name) {
    this->filename = name;
    this->fd = fd;
    eof = false;
    closed = false;
    numInBuf = 0;
    bufIndex = 0;
    charCount = 0;
    column = 1;
    line = 1;
    buffer = new char[FILE_BUF_SIZE];
    refill();
}

fileReader::~fileReader() {
    if (!closed) {
        close(fd);
    }
    delete buffer;
}

char fileReader::lookAhead(int64_t index) {
    if (bufIndex + index < numInBuf) {
        return buffer[bufIndex + index];
    } 
    return '\0';
    
}

char fileReader::next() {
    char retChar;
    if (bufIndex < numInBuf) {
        retChar = buffer[bufIndex++];
        column++;
        charCount++;
    } else {
        retChar = '\0';
    }
    if (retChar == '\n') {
        line++;
        column = 1;
    }
    if (numInBuf - bufIndex <= /*FILE_BUF_SIZE/32*/ 64 && !closed) {
        refill();
    }
    if (bufIndex == numInBuf) eof = true;
    return retChar;
}

int64_t fileReader::getLine() {
    return line;
}

int64_t fileReader::getCol() {
    return column;
}

charPos fileReader::getCharPos() {
    return {line, column};
}

bool fileReader::isClosed() {
    return closed;
}

bool fileReader::isEof() {
    return eof;
}

void fileReader::refill() {
    if (closed) return;
    memcpy(buffer, buffer + bufIndex, numInBuf-bufIndex);
    numInBuf = numInBuf - bufIndex;
    bufIndex = 0;
    int64_t numRead = read(fd, buffer + numInBuf, FILE_BUF_SIZE - numInBuf);
    if (numRead <= 0) {
        close(fd);
        closed = true;
    }
    numInBuf = numInBuf + numRead;
    return;

    
}