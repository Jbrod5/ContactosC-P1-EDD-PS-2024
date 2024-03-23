#ifndef ARBOL_H
#define ARBOL_H

#include "Nodo.h"
template<typename T>
class Arbol{


    private:
        bool vacio;
        int cantidadNodos; 
        Nodo<T>* raiz;


        void insertarRecursivo(Nodo<T>* nodo, T dato, int id);

        Nodo<T>* buscarPorIdRecursivo(int id, Nodo<T>* nodo);
        Nodo<T>* buscarPorContenidoRecursivo(T contenido, Nodo<T>* nodo);

        int altura(Nodo<T>* nodo);
        int calcularFactorBalanceo(Nodo<T>* nodo);
        void balancearRecursivo(Nodo<T>* nodo);

        void rotacionIzquierda(Nodo<T>* nodo);
        void rotacionDerecha(Nodo<T>* nodo);
        void rotacionIzquierdaDerecha(Nodo<T>* nodo);
        void rotacionDerechaIzquierda(Nodo<T>* nodo);


     
    public:
        Arbol();
        bool estaVacio();
        void insertar(T dato, int id);


        Nodo<T>* buscarPorId(int id);
        Nodo<T>* buscarPorContenido(T contenido);
       
       void balancear();

};      

#endif