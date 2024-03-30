#ifndef ARBOL_CHAR_H
#define ARBOL_CHAR_H

#include "ArbolBase.h"
#include "../Arbol.h"
#include "../Nodo.h"

    // Contenedor para Arbol, con tipo de dato int definido
    class ArbolChar : public ArbolBase{
        private: 
            Arbol<char>* arbol; 

        public: 
            ArbolChar(string nombreCampo);
            bool estaVacio();
            void insertar(char dato, int id);


            Nodo<char>* buscarPorId(int id);
            Nodo<char>* buscarPorContenido(char contenido);
       
            void balancear();
            void generarGrafico();
            string obtenerGrafo() override;
            string obtenerListaElementos() override{
                return arbol->obtenerListaElementos();
            }
            ~ArbolChar() override {
            // Código del destructor de la clase ArbolChar
            }
            
    };

    ArbolChar::ArbolChar(string nombreCampo){
            arbol = new Arbol<char>(nombreCampo);
            this->nombreCampo = nombreCampo;
        }

    bool ArbolChar::estaVacio(){ return arbol->estaVacio(); }

    void ArbolChar::balancear(){ arbol->balancear(); }

    void ArbolChar::generarGrafico(){ arbol->generarGrafico(); }


    /* Metodos especiales */

    void ArbolChar::insertar(char dato, int id){
        arbol->insertar(dato, id);
    }

    Nodo<char>* ArbolChar::buscarPorId(int id){
        return arbol->buscarPorId(id);
    }

    Nodo<char>* ArbolChar::buscarPorContenido(char contenido){
        return arbol->buscarPorContenido(contenido);
    }

    string ArbolChar::obtenerGrafo (){
        return arbol->obtenerGrafo();
    }

#endif