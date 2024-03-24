#include "Nodo.h"

template<typename T>
Nodo<T>::Nodo(T dato, int id){
    this->dato = dato;
    this->id = id; 
    izquierdo = nullptr;
    derecho = nullptr;
}

template<typename T>
Nodo<T>* Nodo<T>::obtIzquierdo(){
    return izquierdo;
}

template<typename T>
Nodo<T>* Nodo<T>::obtDerecho(){
    return derecho;
}


template<typename T>
void Nodo<T>::insertarIzquierdo(Nodo<T>* nodo){
    izquierdo = nodo; 
}


template<typename T>
void Nodo<T>::insertarDerecho(Nodo<T>* nodo){
    derecho = nodo; 
}



template<typename T>
T Nodo<T>::obtDato(){
    return dato;
}

template<typename T>
int Nodo<T>::obtId(){
    return id; 
}