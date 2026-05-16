#include "Logger.hpp"

/*
#include <iostream>
#include <string>
#include <fstream>



class logger {

    public:
        logger(std::string, std::ofstream);
        int64_t write(std::string*);
        int64_t writeln(std::string*);
        int64_t close();
        ~logger();

    private:
        std::string name;
        int64_t index;
        bool closed;
        std::ofstream stream;



};

logger* loggerStarter(std::string);

*/

logger::logger(std::string name, std::ofstream& stream) {
    this->name = name;
    this->stream = std::move(stream);
    index = 0;
    closed = false;
}

logger::~logger() {
    if (!closed) {
        stream.close();
    }
}

int64_t logger::write(std::string toWrite) {
    if (closed) return LOGGER_CLOSED;
    stream << toWrite;
    return 0;
}

int64_t logger::writeln(std::string toWrite) {
    if (closed) return LOGGER_CLOSED;
    stream << "[" << index << "]- " << toWrite << "\n";
    index++;
    return 0;
}

int64_t logger::close() {
    if (closed) return LOGGER_CLOSED;
    stream.close();
    closed = true;
}

logger* loggerStarter(std::string name) {
    std::ofstream stream(name);
    if (stream.is_open()) {
        return new logger(name, stream);
    }
    return nullptr;

}