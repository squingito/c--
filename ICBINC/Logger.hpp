#include <iostream>
#include <string>
#include <fstream>

#ifndef LOGGER_HEADER_GUARD
#define LOGGER_HEADER_GUARD

#define LOGGER_CLOSED -1

class logger {

    public:
        logger(std::string, std::ofstream&);
        int64_t write(std::string);
        int64_t writeln(std::string);
        int64_t close();
        ~logger();

    private:
        std::string name;
        int64_t index;
        bool closed;
        std::ofstream stream;



};

logger* loggerStarter(std::string);

#endif