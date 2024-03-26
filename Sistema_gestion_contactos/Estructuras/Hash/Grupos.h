/* Contiene la logica para manejar la tabla hash DE GRUPOS */
#ifndef GRUPOS_H
#define GRUPOS_H

#include "Arbol.h"
#include "Campos.h"
#include "../TiposCamposEnum.h"
using namespace std; 

class Grupos{

    private: 
        int uso;     //cantidad de elementos insertados
        int tamanio; //tamanio del array
        Campos** grupos;  
        
        int hash(string nombreGrupo); 
         
        void reHash(); //Amplia el array y actualiza el factor tamanio para cambiar el redireccionamiento por la funcion hash

    public: 
        Grupos();

        //Campos sera la instruccion con todos los campos, por ejemplo:  FIELDS (nombre STRING, apellido STRING, celular INTEGER)
        void agregarGrupo(string nombreGrupo, string campos); //Agrega un nuevo grupo "campo", campos: (nombre STRING, apellido STRING, celular INTEGER)
        void agregarContacto(string nombreGrupo, string valoresContacto);

        string obtenerContacto(string nombreGrupo, string campoABuscar, string valorABuscar); //Retorna la tupla de un contacto en base a un nombre de grupo(para hacer hash y obtener la posicion en el array), y usa internamente la funcion obtenerTupla
        string obtenerTupla(string campo, string valorABuscar); //Retorna la tupla de un contacto en base a un campo y un valor, asi: [campo]=[DatoQueBusca]
};
#endif



Grupos::Grupos(){
    tamanio = 5; //Inicialmente las tablas deben ser de tamanio 5
    uso = 0; 
    grupos = new Campos*[tamanio];
}

int Grupos::hash(string nombreGrupo){
        int sumaCaracteres = 0; 
        int caracter = 0; 
        int resultado = 0;

        if(!nombreGrupo.empty()){
            //Sumar los valores ascii del nombre del campo y desplazazar esa cantidad de veces dentro del tamanio 
            for(char caracter : nombreGrupo){
                caracter = static_cast<int>(caracter);
                sumaCaracteres += caracter;  
            }
            resultado = sumaCaracteres % tamanio;

        }
        return resultado;
}

void Grupos::reHash(){
    // Decidi aumentar un 60% el tamaño del array
    int tamanioTemporal = tamanio; 
    tamanio *= 1.6;
    Campos** gruposTemporal = new Campos*[tamanio];
    Campos* grupoActual; 
    string nombreGrupoActual;
    int nuevaPosicion; 

    // Copiar la informacion del array en orden segun la funcion hash
    for (int i = 0; i < tamanioTemporal; i++)
    {
        grupoActual = grupos[i];
        if(grupoActual != nullptr){
            nombreGrupoActual = grupoActual->obtenerGrupo();
            nuevaPosicion = hash(nombreGrupoActual);
            if(gruposTemporal[nuevaPosicion] == nullptr){
                gruposTemporal[nuevaPosicion] = grupoActual;
            }else{
                std::cout << endl << endl << endl << "Hubo una colision en Grupos.h: en la funcion reHash." << endl; 
                std::cout << "Se intento asignar el grupo: " << nombreGrupoActual << " en la posicion: " << to_string(nuevaPosicion) << " otorgada por la funcion hash, pero " <<  gruposTemporal[nuevaPosicion]->obtenerGrupo() << " ya se encontraba en esa posicion." << endl << endl<< endl<< endl;
            }
        }
    }
    grupos = gruposTemporal;
}

// Ejemplo de paso de parametro "campos": (nombre STRING, apellido STRING, celular INTEGER);
void Grupos::agregarGrupo(string nombreGrupo, string campos){
    // Quitar ( y  );
    if (campos[0]                 == '(' ){ campos.erase(0                 , 1 ); }
    if (campos[campos.length()-1] == ';' ){ campos.erase(campos.length()-1 , 1 ); }
    if (campos[campos.length()-1] == ')' ){ campos.erase(campos.length()-1 , 1 ); }
    // Agregar el grupo
    int posicionGrupo = hash(nombreGrupo);
    grupos[posicionGrupo] = new Campos(10, nombreGrupo);

    // Separar los " " y operar
    string acumulador; 
    string campo; 
    string tipo; 
    for (int i = 0; i < campos.length(); i++)
    {
        if(campos[i] != ' '){
            acumulador += campos[i];
        }else{
            // Establecer par clave valor
            if(campo.empty()){
                campo = acumulador;
            }else if(tipo.empty()){
                tipo = acumulador;
            }

            // Verificar que haya par clave valor para agregar el tipo 
            if(campo.length() > 0 && tipo.length() > 0){
                
                if(tipo == "INTEGER"){
                    grupos[posicionGrupo]->agregarCampo(campo, INTEGER);
                }else if(tipo == "STRING"){
                    grupos[posicionGrupo]->agregarCampo(campo, STRING);
                }else if(tipo == "CHAR"){
                    grupos[posicionGrupo]->agregarCampo(campo, CHAR);
                }else if(tipo == "DATE"){
                    grupos[posicionGrupo]->agregarCampo(campo, DATE);
                }else{
                    cout<<endl<<endl<<endl<<"Error en Grupos.h en funcion AgregarGrupo: " << endl; 
                    cout<<"Se intento agregar un grupo pero no se reconocio el tipo deseado."<<endl;
                    cout<<"Tipo que se quiso agregar: " <<tipo<<endl<<endl<<endl; 
                }
            }
        }
    }
    
}
