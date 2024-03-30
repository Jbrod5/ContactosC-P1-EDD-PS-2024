#ifndef ARBOL_BASE_H
#define ARBOL_BASE_H

#include <string>
    // Contenedor para Arbol, con tipo de dato definido
    class ArbolBase{
        private: 

        public: 
            std::string nombreCampo;

            ArbolBase();
            virtual ~ArbolBase() {
                // Código del destructor de la clase base
            }

            virtual bool estaVacio();
            //void insertar(T dato, int id);


            //Nodo<T>* buscarPorId(int id);
            //Nodo<T>* buscarPorContenido(T contenido);
       
            virtual void balancear();
            virtual void generarGrafico();
            virtual string obtenerGrafo();
            virtual string obtenerListaElementos(){
                return "";
            };
            
    };

    ArbolBase::ArbolBase(){ }

    bool ArbolBase::estaVacio(){ return true; }

    void ArbolBase::balancear(){ }

    void ArbolBase::generarGrafico(){ }

    string ArbolBase::obtenerGrafo(){
        return "";
    }

#endif