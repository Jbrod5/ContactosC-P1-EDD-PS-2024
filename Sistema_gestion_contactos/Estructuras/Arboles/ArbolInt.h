#ifndef ARBOL_INT_H
#define ARBOL_INT_H

#include "ArbolBase.h"
#include "../Arbol.h"
#include "../Nodo.h"
#include <string>

    // Contenedor para Arbol, con tipo de dato int definido
    class ArbolInt : public ArbolBase{
        private: 
            Arbol<int>* arbol; 

        public: 
            ArbolInt(std::string nombreCampo);
            bool estaVacio();
            void insertar(int dato, int id);


            Nodo<int>* buscarPorId(int id);
            Nodo<int>* buscarPorContenido(int contenido);
       
            void balancear();
            void generarGrafico();

            string obtenerGrafo() override; 
            
    };

    ArbolInt::ArbolInt(std::string nombreCampo){
        arbol = new Arbol<int>(nombreCampo);
        this->nombreCampo = nombreCampo;
    }

    bool ArbolInt::estaVacio(){ return arbol->estaVacio(); }

    void ArbolInt::balancear(){ arbol->balancear(); }

    void ArbolInt::generarGrafico(){ arbol->generarGrafico(); }


    /* Metodos especiales */

    void ArbolInt::insertar(int dato, int id){
        arbol->insertar(dato, id);
    }

    Nodo<int>* ArbolInt::buscarPorId(int id){
        return arbol->buscarPorId(id);
    }

    Nodo<int>* ArbolInt::buscarPorContenido(int contenido){
        return arbol->buscarPorContenido(contenido);
    }
    
    string ArbolInt::obtenerGrafo (){
        return arbol->obtenerGrafo();
    }

#endif