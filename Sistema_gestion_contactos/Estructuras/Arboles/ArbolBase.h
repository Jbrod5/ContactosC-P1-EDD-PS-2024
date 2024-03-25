#ifndef ARBOL_BASE_H
#define ARBOL_BASE_H

#include <string>
    // Contenedor para Arbol, con tipo de dato definido
    class ArbolBase{
        private: 

        public: 
            std::string nombreCampo;

            ArbolBase();
            bool estaVacio();
            //void insertar(T dato, int id);


            //Nodo<T>* buscarPorId(int id);
            //Nodo<T>* buscarPorContenido(T contenido);
       
            void balancear();
            void generarGrafico();
            
    };

    ArbolBase::ArbolBase(){ }

    bool ArbolBase::estaVacio(){ return true; }

    void ArbolBase::balancear(){ }

    void ArbolBase::generarGrafico(){ }

#endif