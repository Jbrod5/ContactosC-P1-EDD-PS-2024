#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <ctime>

class Logger {
public:
    void log(const std::string& message) {
        std::cout << message << std::endl;
        std::ofstream file("./Reportes/Contactos.log", std::ios::app);
        if (file.is_open()) {
            std::time_t now = std::time(nullptr);
            char timestamp[20];
            std::strftime(timestamp, sizeof(timestamp), "%d-%m-%H:%M:%S", std::localtime(&now));
            file << timestamp << std::endl;
            file << message << std::endl;
            file << std::endl;
            file.close();
        }
    }
};

#endif
