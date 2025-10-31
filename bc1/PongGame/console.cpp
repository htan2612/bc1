#include "Console.h"

void Console::log(const std::string& message) {
    std::cout << "[LOG] " << message << std::endl;
}

void Console::error(const std::string& message) {
    std::cerr << "[ERROR] " << message << std::endl;
}