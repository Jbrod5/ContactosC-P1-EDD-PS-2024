#ifndef ARBOL_STRING_H
#define ARBOL_STRING_H

#include "ArbolBase.h"
#include "../Arbol.h"
#include "../Nodo.h"
#include <string>

using namespace std; 

    // Contenedor para Arbol, con tipo de dato int definido
    class ArbolString : public ArbolBase{
        private: 
            Arbol<string>* arbol; 

        public: 
            ArbolString(string nombreCampo);
            bool estaVacio();
            void insertar(string dato, int id);


            Nodo<string>* buscarPorId(int id);
            Nodo<string>* buscarPorContenido(string contenido);
       
            void balancear();
            void generarGrafico();
            string obtenerGrafo() override;
            ~ArbolString() override {
            // Código del destructor de la clase ArbolString
            }
            
    };

    ArbolString::ArbolString(string nombreCampo){
            arbol = new Arbol<string>(nombreCampo);
            this->nombreCampo = nombreCampo; 
        }

    bool ArbolString::estaVacio(){ return arbol->estaVacio(); }

    void ArbolString::balancear(){ arbol->balancear(); }

    void ArbolString::generarGrafico(){ arbol->generarGrafico(); }

    /* Metodos especiales */

    void ArbolString::insertar(string dato, int id){
        arbol->insertar(dato, id);
    }

    Nodo<string>* ArbolString::buscarPorId(int id){
        return arbol -> buscarPorId(id);
    }

    Nodo<string>* ArbolString::buscarPorContenido(string contenido){
        return arbol->buscarPorContenido(contenido);
    }

    string ArbolString::obtenerGrafo (){
        return arbol->obtenerGrafo();
    }
#endif