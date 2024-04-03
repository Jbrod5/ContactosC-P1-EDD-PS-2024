#ifndef ARBOL_H
#define ARBOL_H

#include "Nodo.h"
#include <fstream>
#include <iostream>
#include <string>
#include <typeinfo>
#include "Date.h"
#include "Logger.h"
using namespace std; 

template<typename T>
class Arbol{


    private:
        bool vacio;
        int cantidadNodos; 
        Nodo<T>* raiz;
        Logger logger;

        void insertarRecursivo(Nodo<T>* nodo, T dato, int id);

        Nodo<T>* buscarPorIdRecursivo(int id, Nodo<T>* nodo);
        Nodo<T>* buscarPorContenidoRecursivo(T contenido, Nodo<T>* nodo);

        int altura(Nodo<T>* nodo);
        int calcularFactorBalanceo(Nodo<T>* nodo);
        Nodo<T>*  balancearRecursivo(Nodo<T>* nodo);

        Nodo<T>* rotacionIzquierda(Nodo<T>* nodo);
        Nodo<T>* rotacionDerecha(Nodo<T>* nodo);
        Nodo<T>* rotacionIzquierdaDerecha(Nodo<T>* nodo);
        Nodo<T>* rotacionDerechaIzquierda(Nodo<T>* nodo);

        void generarGraficoRecursivo(Nodo<T>* nodo, std::ofstream& archivo);
        void actualizarRaiz(Nodo<T>* nodo);

        string nombreCampo;

        string obtenerGrafoRecursivo(Nodo<T>* nodo);
        string obtenerListaElementosRecursivo(Nodo<T>* nodo);
    public:
        Arbol(string nombre);
        bool estaVacio();
        void insertar(T dato, int id);


        Nodo<T>* buscarPorId(int id);
        Nodo<T>* buscarPorContenido(T contenido);
       
       void balancear();
       void generarGrafico();

       string obtenerGrafo();
       string obtenerNombreCampo();

       string obtenerListaElementos();

       string to_string(Date* date);
       string to_string(int dato);
       string to_string(string dato);
       string to_string(char dato);
};

template<typename T>
Arbol<T>::Arbol(string nombre){
    raiz = nullptr;
    cantidadNodos = 0;
    nombreCampo = nombre; 
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
    balancear();
}

template<typename T>
void Arbol<T>::actualizarRaiz(Nodo<T>* nodo){
    this->raiz = nodo;
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
    cout<<"Id por buscar: " <<id<<endl; 
    return buscarPorIdRecursivo(id, raiz);
}

template<typename T>
Nodo<T>* Arbol<T>::buscarPorIdRecursivo(int id, Nodo<T>* nodo){
    // Verificar que no se quiera acceder a un nodo nulo
    if (nodo == nullptr ) { return nullptr; }

    if(nodo->obtId() == id){
        return nodo;
    }else{
        Nodo<T>* temporal; 
        if(nodo->obtIzquierdo() != nullptr){
            temporal = buscarPorIdRecursivo(id, nodo->obtIzquierdo());
        }
        if(nodo->obtDerecho() != nullptr){
            temporal = buscarPorIdRecursivo(id, nodo->obtDerecho());
        }
        if(temporal != nullptr){
            return temporal; 
        }
    }
    return nullptr;
}



template<typename T>
Nodo<T>* Arbol<T>::buscarPorContenido(T contenido){
    return buscarPorContenidoRecursivo(contenido, raiz);
}
template<typename T>
Nodo<T>* Arbol<T>::buscarPorContenidoRecursivo(T contenido, Nodo<T>* nodo){
    //Verificar que no se quiera acceder a un nodo nulo
    if (nodo == nullptr ) { return nullptr; }

    if(nodo->obtDato() == contenido){
        return nodo;
    }else{
        Nodo<T>* temporal;
        if(nodo->obtIzquierdo() != nullptr){
            temporal = buscarPorContenidoRecursivo(contenido, nodo->obtIzquierdo());
            if(temporal!= nullptr){
                return temporal;
            }
        }
        if(nodo->obtDerecho() != nullptr){
            temporal = buscarPorContenidoRecursivo(contenido,nodo->obtDerecho());
            if(temporal!= nullptr){
                return temporal;
            }
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
    raiz = balancearRecursivo(raiz);
}

template<typename T>
Nodo<T>* Arbol<T>::balancearRecursivo(Nodo<T>* nodo) {
    if (nodo == nullptr) {
        return nullptr;
    }

    int factorBalanceo = calcularFactorBalanceo(nodo);

    if (factorBalanceo > 1) {
        if (calcularFactorBalanceo(nodo->obtIzquierdo()) >= 0) {
            nodo = rotacionDerecha(nodo);
        } else {
            nodo = rotacionIzquierdaDerecha(nodo);
        }
    } else if (factorBalanceo < -1) {
        if (calcularFactorBalanceo(nodo->obtDerecho()) <= 0) {
            nodo = rotacionIzquierda(nodo);
        } else {
            nodo = rotacionDerechaIzquierda(nodo);
        }
    }

    nodo->insertarIzquierdo(balancearRecursivo(nodo->obtIzquierdo())) ;
    nodo->insertarDerecho(balancearRecursivo(nodo->obtDerecho()));

    return nodo; 
}



template<typename T>
Nodo<T>* Arbol<T>::rotacionIzquierda(Nodo<T>* nodo) {
    Nodo<T>* nuevoPadre = nodo->obtDerecho();
    
    nodo->insertarDerecho(nuevoPadre->obtIzquierdo());
    nuevoPadre->insertarIzquierdo(nodo);

    if (nodo == raiz) {
        actualizarRaiz(nuevoPadre);
    }
    return nuevoPadre;
}

template<typename T>
Nodo<T>* Arbol<T>::rotacionDerecha(Nodo<T>* nodo) {
    Nodo<T>* nuevoPadre = nodo->obtIzquierdo();
    nodo->insertarIzquierdo(nuevoPadre->obtDerecho());
    nuevoPadre->insertarDerecho(nodo);

    if (nodo == raiz) {
        actualizarRaiz(nuevoPadre);
    }
    return nuevoPadre;
}

template<typename T>
Nodo<T>* Arbol<T>::rotacionIzquierdaDerecha(Nodo<T>* nodo) {
    nodo->insertarIzquierdo(rotacionIzquierda(nodo->obtIzquierdo()));
    nodo = rotacionDerecha(nodo);
    return nodo; 
}

template<typename T>
Nodo<T>* Arbol<T>::rotacionDerechaIzquierda(Nodo<T>* nodo) {
    nodo->insertarDerecho(rotacionDerecha(nodo->obtDerecho()));
    nodo = rotacionIzquierda(nodo);
    return nodo; 
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


template<typename T>
string Arbol<T>::obtenerListaElementos(){
    string elementos=""; 
    elementos += obtenerListaElementosRecursivo(raiz);
    return elementos;
}


template<typename T>
string Arbol<T>::obtenerListaElementosRecursivo(Nodo<T>* nodo){
    string elementos = "";

    if (nodo == nullptr) {
        return elementos;
    }

    T dato = nodo->obtDato();
    string datoString;
    datoString = to_string(dato);


    elementos += datoString + ",";

    if (nodo->obtIzquierdo() != nullptr) {
        elementos += obtenerListaElementosRecursivo(nodo->obtIzquierdo());
    }

    if (nodo->obtDerecho() != nullptr) {
        elementos += obtenerListaElementosRecursivo(nodo->obtDerecho());
    }
    return elementos; 
}


template<typename T>
string Arbol<T>::obtenerGrafo(){
    string grafo = "     subgraph " + nombreCampo +"{\n";
    grafo+= "     label=" + nombreCampo +"\n";
    grafo += obtenerGrafoRecursivo(raiz);

    grafo += "     }\n";
    cout<<"Digraph de "<< nombreCampo<< " generado correctamente."<<endl;
    return grafo; 
}

template<typename T>
string Arbol<T>::obtenerGrafoRecursivo(Nodo<T>* nodo){
    string grafo = "";

    if (nodo == nullptr) {
        return grafo;
    }

    T dato = nodo->obtDato();
    string datoString;
    datoString = to_string(dato);


    grafo += "          "+ to_string(dato)  + " [label=\"" + datoString  + " |"+to_string(nodo->obtId())+"| \"];\n";

    if (nodo->obtIzquierdo() != nullptr) {
        grafo += "          " + to_string(nodo->obtDato()) + " -> " + to_string(nodo->obtIzquierdo()->obtDato())   + " [label=\"izquierdo\"];\n";
        grafo += obtenerGrafoRecursivo(nodo->obtIzquierdo());
    }

    if (nodo->obtDerecho() != nullptr) {
        grafo += "          " + to_string(nodo->obtDato())   +   " -> " + to_string(nodo->obtDerecho()->obtDato())  + " [label=\"derecho\"];\n";
        grafo += obtenerGrafoRecursivo(nodo->obtDerecho());
    }
    return grafo; 
}

template<typename T>
string Arbol<T>::obtenerNombreCampo(){
    return nombreCampo;
}

template<typename T>
string Arbol<T>::to_string(Date* date){
    return date->obtFecha();
}
template<typename T>
string Arbol<T>::to_string(int dato){
    return std::to_string(dato);
}

template<typename T>
string Arbol<T>::to_string(string dato){
    return dato; 
}

template<typename T>
string Arbol<T>::to_string(char dato){
    string resultado;
    resultado+=dato; 
    return resultado;
}
#endif