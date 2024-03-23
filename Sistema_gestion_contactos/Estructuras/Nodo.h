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

#endif