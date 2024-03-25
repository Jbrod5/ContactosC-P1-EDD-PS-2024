/* Contiene la loica para manejar la tabla hash de CAMPOS */

#ifndef CAMPOS_H
#define CAMPOS_H

#include <string>
#include "../Date.h"
#include "../Nodo.h"
#include "../TiposCamposEnum.h"
#include "../Arboles/ArbolBase.h"

#include "../Arboles/ArbolDate.h"
#include "../Arboles/ArbolChar.h"
#include "../Arboles/ArbolInt.h"
#include "../Arboles/ArbolString.h"

using namespace std; 


class Campos{

    private: 
        int uso;    
        int tamanio; 
        ArbolBase** arboles; // Cada espacio de arboles tendra un tipo de arbol distinto 
        
        int hash(string nombreCampo);

    public: 
        void agregarCampo(string nombreCampo, int tipo); // el nombre es el hash, el tipo es un enum: STRING, INT, DATE, ETC 
        Campos(int cantidadCampos);

        void insertar(string nombreCampo, string dato);

        string obtenerPorContenido(string nombreCampo, string dato);
        string obtenerPorId(int id);
};

#endif


/* Definiciones */
Campos::Campos(int  cantidadCampos){
    uso = 0; 
    arboles = new ArbolBase*[cantidadCampos];
    tamanio = cantidadCampos;
}

int Campos::hash(string nombreCampo){
    int sumaCaracteres = 0; 
    int caracter = 0; 
    int resultado = 0;

    if(!nombreCampo.empty()){
        //Sumar los valores ascii del nombre del campo y desplazazar esa cantidad de veces dentro del tamanio 

        for(char caracter : nombreCampo){
            caracter = static_cast<int>(caracter);
            sumaCaracteres += caracter;  
        }

        resultado = sumaCaracteres % tamanio;
        
    }
    return resultado;
}

void Campos::agregarCampo(string nombreCampo, int tipo){
    int posicion = hash(nombreCampo);
    // 1. Verificar que no haya colision:
    if(arboles[posicion] != nullptr){
        
        //2. Crear la instancia del arbol
        switch (tipo)
        {
        case INTEGER:
            arboles[posicion] = new ArbolInt(nombreCampo);
            break;
        case CHAR:
            arboles[posicion] = new ArbolChar(nombreCampo);
            break; 
        case CADENA:
            arboles[posicion] = new ArbolString(nombreCampo);
            break; 
        case DATE:
            arboles[posicion] = new ArbolDate(nombreCampo);
            break;
        }
    }
}

void Campos::insertar(string nombreCampo, string dato){
    uso++; 
    int posicion = hash(nombreCampo);
    ArbolBase* dondeInsertar = arboles[posicion];
    string tipo = "a"; 

    if(dondeInsertar == nullptr){
        cout << endl << endl << "Error producido en la clase Campos (Campos.h) al insertar un dato." << endl;
        cout << "Se quiso insertar un dato en un arbol nulo."<< endl ;
        cout << "Nombre del campo donde se queria insertar: " << nombreCampo << endl;
        cout << "Posicion en la tabla proporcionada por la funcion hash: " << std::to_string(posicion) << endl << endl << endl;
        return; 
    }

    // Evaluar el tipo de arbol e insertar especializado
    try{
        if (typeid(*dondeInsertar) == typeid(ArbolChar)) {
            tipo = "Arbol Char";
            char caracter = dato[0];
            (static_cast<ArbolChar*>(dondeInsertar))->insertar(caracter, uso);

        } else if(typeid(*dondeInsertar) == typeid(ArbolDate)){

            tipo = "ArbolDate";
            (static_cast<ArbolDate*>(dondeInsertar))->insertar(dato, uso);

        }else if (typeid(*dondeInsertar) == typeid(ArbolString)){

            tipo = "ArbolString";
            (static_cast<ArbolString*>(dondeInsertar))-> insertar(dato, uso);

        }else if (typeid(*dondeInsertar) == typeid(ArbolInt)){

            tipo = "ArbolInt";
            int datoCastToInt = std::stoi(dato);
            (static_cast<ArbolInt*>(dondeInsertar))-> insertar(datoCastToInt, uso);

        }
    }catch(const std::exception& e){
        cout << endl << endl << "Error producido en la clase Campos (Campos.h) al insertar un dato." << endl;
        cout << "Nombre del campo donde se queria insertar: " << nombreCampo << endl;
        cout << "Posicion en la tabla proporcionada por la funcion hash: " << std::to_string(posicion) << endl;
        cout << "Dato que se intento insertar: " << dato << endl;
        cout << "Tipo de arbol donde se queria insertar: " << tipo << endl << endl<< endl<< endl<< endl;
    }
}

// Esta funcion debe retornar todos los datos guardados en los demas arboles 
// Inicia obteniendo un nodo en base al contenido
// De el se extrae el id para seguir buscando en los demas nodos
string Campos::obtenerPorContenido(string nombreCampo, string dato){

    //1. Obtener el arbol en base al campo
    int posicionArbol = hash(nombreCampo);
    string tipo; 
    int id = 0; 
    string resultado; 

    ArbolBase* dondeBuscarPorDato = arboles[posicionArbol];

    //2. Obtener el nodo con la informacion que buscamos
    if (typeid(*dondeBuscarPorDato) == typeid(ArbolChar)) {
            tipo = "Arbol Char";
            char caracter = dato[0];
            Nodo<char>* encontrado;  
            encontrado = (static_cast<ArbolChar*>(dondeBuscarPorDato))->buscarPorContenido(caracter);
            if(encontrado != nullptr){
                id = encontrado->obtId();
                resultado += dondeBuscarPorDato->nombreCampo + ": " + encontrado->obtDato();
            } else{
                resultado = "Hubo un error en Campos.h al buscar " + dato + " en " + nombreCampo + " ya que no se encontro un nodo con el dato solicitado. Tipo de arbol: " + tipo;
            }



        } else if(typeid(*dondeBuscarPorDato) == typeid(ArbolDate)){
            tipo = "ArbolDate";
            Nodo<Date*>* encontrado; 
            encontrado = (static_cast<ArbolDate*>(dondeBuscarPorDato))->buscarPorContenido(dato);
            if(encontrado != nullptr){
                id = encontrado->obtId();
                Date* fecha = encontrado->obtDato();
                resultado += dondeBuscarPorDato->nombreCampo + ": " + fecha->obtFecha();
            } else{
                resultado = "Hubo un error en Campos.h al buscar " + dato + " en " + nombreCampo + " ya que no se encontro un nodo con el dato solicitado. Tipo de arbol: " + tipo;
            }


        }else if (typeid(*dondeBuscarPorDato) == typeid(ArbolString)){
            tipo = "ArbolString";
            Nodo<string>* encontrado; 
            encontrado = (static_cast<ArbolString*>(dondeBuscarPorDato))-> buscarPorContenido(dato);
            if(encontrado != nullptr){
                id = encontrado->obtId();
                resultado += dondeBuscarPorDato->nombreCampo + ": " + encontrado->obtDato();
            } else{
                resultado = "Hubo un error en Campos.h al buscar " + dato + " en " + nombreCampo + " ya que no se encontro un nodo con el dato solicitado. Tipo de arbol: " + tipo;
            }


        }else if (typeid(*dondeBuscarPorDato) == typeid(ArbolInt)){
            tipo = "ArbolInt";
            int datoCastToInt = std::stoi(dato);
            Nodo<int>* encontrado;
            encontrado = (static_cast<ArbolInt*>(dondeBuscarPorDato))-> buscarPorContenido(datoCastToInt);
            if(encontrado != nullptr){
                id = encontrado->obtId();
                resultado += dondeBuscarPorDato->nombreCampo + ": " + to_string(encontrado->obtDato());
            } else{
                resultado = "Hubo un error en Campos.h al buscar " + dato + " en " + nombreCampo + " ya que no se encontro un nodo con el dato solicitado. Tipo de arbol: " + tipo;
            }
            
        }

}