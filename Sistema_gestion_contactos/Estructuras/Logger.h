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

    void crearCarpeta(string nombre){
        string SH_CMD = "mkdir " + nombre;
        string POWERSHELL = "New-Item -ItemType Directory -Name " + nombre;
        //Ejecutar las instrucciones 
        system(SH_CMD.c_str());
        system(POWERSHELL.c_str());
    }

    void persistir(const std::string& nombreArchivo, const std::string& contenido) {
        std::ofstream archivo(nombreArchivo + ".ct");
        if (archivo.is_open()) {
            archivo << contenido;
            archivo.close();
            std::cout << "Archivo creado y contenido guardado exitosamente." << std::endl;
        } else {
            std::cout << "No se pudo abrir el archivo." << std::endl;
    }
}
};

#endif
