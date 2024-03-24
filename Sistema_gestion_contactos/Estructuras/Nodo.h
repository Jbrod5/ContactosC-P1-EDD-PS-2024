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
};

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

#endif