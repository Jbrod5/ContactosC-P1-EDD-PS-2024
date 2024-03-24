#ifndef NODO_H
#define NODO_H

template <typename T>
class Nodo{

    private: 
        Nodo<T>* izquierdo;
        Nodo<T>* derecho;
        T dato;
        int id; 

    public:
        Nodo(T dato, int id);

        Nodo<T>* obtIzquierdo();
        Nodo<T>* obtDerecho();

        void insertarIzquierdo(Nodo<T>* nodo);
        void insertarDerecho(Nodo<T>* nodo);

        T obtDato();
        int obtId(); 

Nodo<T>(T dato, int id){
    this->dato = dato;
    this->id = id; 
    izquierdo = nullptr;
    derecho = nullptr;
}


Nodo<T>* obtIzquierdo(){
    return izquierdo;
}


Nodo<T>* obtDerecho(){
    return derecho;
}



void insertarIzquierdo(Nodo<T>* nodo){
    izquierdo = nodo; 
}


void insertarDerecho(Nodo<T>* nodo){
    derecho = nodo; 
}



T obtDato(){
    return dato;
}

int obtId(){
    return id; 
}
};

//#include "Nodo.cpp"


#endif