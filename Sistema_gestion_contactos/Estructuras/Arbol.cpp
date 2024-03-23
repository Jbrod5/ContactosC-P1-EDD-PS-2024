#include "Arbol.h"
#include "Nodo.h"


template<typename T>
Arbol<T>::Arbol(){
    raiz = nullptr;
    cantidadNodos = 0; 
}

template<typename T>
bool Arbol<T>::estaVacio(){
    return raiz == nullptr; 
}

/* Metodos para manejar la estructura */
template<typename T>
void Arbol<T>::insertar(T dato, int id){
    if(estaVacio()){
        raiz = new Nodo(dato, id);
    }else{
        insertarRecursivo(raiz, dato, id);
    }
    cantidadNodos++;
}


template<typename T>
void Arbol<T>::insertarRecursivo(Nodo<T>* nodo, T dato, int id){
    if(dato < nodo->obtDato()){
        if(nodo->obtIzquierdo() == nullptr){
            nodo->insertarIzquierdo( new Nodo<T> (dato, id) );
        }else{
            insertarRecursivo(nodo->obtIzquierdo(), dato, id);
        }
    }   else    {

        if(nodo->obtDerecho() == nullptr){
            nodo->insertarDerecho( new Nodo<T> (dato, id) );
        }else{
            insertarRecursivo(nodo->obtDerecho(), dato, id);
        }

    }
}



template<typename T>
Nodo<T>* Arbol<T>::buscarPorId(int id){
    return buscarPorIdRecursivo(raiz, id);
} 

template<typename T>
Nodo<T>* Arbol<T>::buscarPorIdRecursivo(int id, Nodo<T>* nodo){
    // Verificar que no se quiera acceder a un nodo nulo
    if (nodo == nullptr ) { return nullptr; }

    if(nodo->obtId() == id){
        return nodo;
    }else{
        if(nodo->obtIzquierdo() != nullptr){
            buscarPorIdRecursivo(id, nodo->obtIzquierdo());
        }
        if(nodo->obtDerecho() != nullptr){
            buscarPorIdRecursivo(id, nodo->obtDerecho());
        }
    }
    return nullptr; 
} 



template<typename T>
Nodo<T>* Arbol<T>::buscarPorContenido(T contenido){
    return buscarPorContenidoRecursivo(raiz, contenido);
} 
template<typename T>
Nodo<T>* Arbol<T>::buscarPorContenidoRecursivo(T contenido, Nodo<T>* nodo){
    //Verificar que no se quiera acceder a un nodo nulo
    if (nodo == nullptr ) { return nullptr; }
        
    if(nodo->obtDato() == contenido){
        return nodo;
    }else{
        if(nodo->obtIzquierdo() != nullptr){
            buscarPorContenidoRecursivo(dato, nodo->obtIzquierdo());
        }
        if(nodo->obtDerecho() != nullptr){
            buscarPorContenidoRecursivo(dato, nodo->obtDerecho());
        }
    }
    return nullptr; 
}

/* -- CODIGO POR REVISAR -- */