#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <string>

class Console {
public:
    static void log(const std::string& message);
    static void error(const std::string& message);
};

#endif