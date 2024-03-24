#ifndef ARBOL_H
#define ARBOL_H

#include "Nodo.h"
#include <fstream>
#include <iostream>
using namespace std; 

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

        void generarGraficoRecursivo(Nodo<T>* nodo, std::ofstream& archivo);

     
    public:
        Arbol();
        bool estaVacio();
        void insertar(T dato, int id);


        Nodo<T>* buscarPorId(int id);
        Nodo<T>* buscarPorContenido(T contenido);
       
       void balancear();
       void generarGrafico();

};      

//#include "Arbol.cpp"
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
        raiz = new Nodo<T>(dato, id);
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
            buscarPorContenidoRecursivo(contenido, nodo->obtIzquierdo());
        }
        if(nodo->obtDerecho() != nullptr){
            buscarPorContenidoRecursivo(contenido,nodo->obtDerecho());
        }
    }
    return nullptr; 
}









/* -- CODIGO POR REVISAR -- */

template<typename T>
int Arbol<T>::calcularFactorBalanceo(Nodo<T>* nodo) {
    return altura(nodo->obtIzquierdo()) - altura(nodo->obtDerecho());
}

template<typename T>
int Arbol<T>::altura(Nodo<T>* nodo) {
    if (nodo == nullptr) {
        return 0;
    }

    int alturaIzquierdo = altura(nodo->obtIzquierdo());
    int alturaDerecho = altura(nodo->obtDerecho());

    if (alturaIzquierdo > alturaDerecho) {
        return 1 + alturaIzquierdo;
    } else {
        return 1 + alturaDerecho;
    }
}





template<typename T>
void Arbol<T>::balancear() {
    balancearRecursivo(raiz);
}

template<typename T>
void Arbol<T>::balancearRecursivo(Nodo<T>* nodo) {
    if (nodo == nullptr) {
        return;
    }

    int factorBalanceo = calcularFactorBalanceo(nodo);

    if (factorBalanceo > 1) {
        if (calcularFactorBalanceo(nodo->obtIzquierdo()) >= 0) {
            rotacionDerecha(nodo);
        } else {
            rotacionIzquierdaDerecha(nodo);
        }
    } else if (factorBalanceo < -1) {
        if (calcularFactorBalanceo(nodo->obtDerecho()) <= 0) {
            rotacionIzquierda(nodo);
        } else {
            rotacionDerechaIzquierda(nodo);
        }
    }

    balancearRecursivo(nodo->obtIzquierdo());
    balancearRecursivo(nodo->obtDerecho());
}



template<typename T>
void Arbol<T>::rotacionIzquierda(Nodo<T>* nodo) {
    Nodo<T>* nuevoPadre = nodo->obtDerecho();
    nodo->insertarDerecho(nuevoPadre->obtIzquierdo());
    nuevoPadre->insertarIzquierdo(nodo);

    if (nodo == raiz) {
        raiz = nuevoPadre;
    }
}

template<typename T>
void Arbol<T>::rotacionDerecha(Nodo<T>* nodo) {
    Nodo<T>* nuevoPadre = nodo->obtIzquierdo();
    nodo->insertarIzquierdo(nuevoPadre->obtDerecho());
    nuevoPadre->insertarDerecho(nodo);

    if (nodo == raiz) {
        raiz = nuevoPadre;
    }
}

template<typename T>
void Arbol<T>::rotacionIzquierdaDerecha(Nodo<T>* nodo) {
    rotacionIzquierda(nodo->obtIzquierdo());
    rotacionDerecha(nodo);
}

template<typename T>
void Arbol<T>::rotacionDerechaIzquierda(Nodo<T>* nodo) {
    rotacionDerecha(nodo->obtDerecho());
    rotacionIzquierda(nodo);
}












template<typename T>
void Arbol<T>::generarGrafico() {
    std::ofstream archivo("arbol.dot");
    archivo << "digraph ArbolBinario {\n";
    generarGraficoRecursivo(raiz, archivo);
    archivo << "}\n";
    archivo.close();
    system("dot -Tpng arbol.dot -o arbol.png");
    cout<<"Grafo generado correctamente!"<<endl;
}

template<typename T>
void Arbol<T>::generarGraficoRecursivo(Nodo<T>* nodo, std::ofstream& archivo) {
    if (nodo == nullptr) {
        return;
    }

    archivo << nodo->obtId() << " [label=\"" << nodo->obtDato() << "\"];\n";

    if (nodo->obtIzquierdo() != nullptr) {
        archivo << nodo->obtId() << " -> " << nodo->obtIzquierdo()->obtId() << " [label=\"izquierdo\"];\n";
        generarGraficoRecursivo(nodo->obtIzquierdo(), archivo);
    }

    if (nodo->obtDerecho() != nullptr) {
        archivo << nodo->obtId() << " -> " << nodo->obtDerecho()->obtId() << " [label=\"derecho\"];\n";
        generarGraficoRecursivo(nodo->obtDerecho(), archivo);
    }
}


#endif