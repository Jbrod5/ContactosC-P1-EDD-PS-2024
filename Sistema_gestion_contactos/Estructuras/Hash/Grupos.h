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
        int contarTipos(string cadena);
    public: 
        Grupos();

        //Campos sera la instruccion con todos los campos, por ejemplo:  FIELDS (nombre STRING, apellido STRING, celular INTEGER)
        void agregarGrupo(string instrGrupoAAgregar); //Agrega un nuevo grupo con la instruccion completa: ADD NEW-GROUP clientes FIELDS (nombre STRING, apellido STRING, celular INTEGER);
        void agregarGrupo(string nombreGrupo, string campos); //Agrega un nuevo grupo "campo", campos: (nombre STRING, apellido STRING, celular INTEGER)
        void agregarContacto(string instrContactoAAgregar); //Agrega una nueva tupla de la siguiente manera: ADD CONTACT IN amigos FIELDS (Pedro, Alvarez, 12345678, 02-05-1998);

        string obtenerContacto(string instrContactoABuscar);
        //string obtenerContacto(string nombreGrupo, string campoABuscar, string valorABuscar); //Retorna la tupla de un contacto en base a un nombre de grupo(para hacer hash y obtener la posicion en el array), y usa internamente la funcion obtenerTupla
        //string obtenerTupla(string campo, string valorABuscar); //Retorna la tupla de un contacto en base a un campo y un valor, asi: [campo]=[DatoQueBusca]
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
                cout<<nombreGrupoActual<<" fue movido de la posicion "<< to_string(i) <<" a la posicion"<<to_string(nuevaPosicion)<< " por la funcion reHash en Grupos.h."<<endl; 
            }else{
                std::cout << endl << endl << endl << "Hubo una colision en Grupos.h: en la funcion reHash." << endl; 
                std::cout << "Se intento asignar el grupo: " << nombreGrupoActual << " en la posicion: " << to_string(nuevaPosicion) << " otorgada por la funcion hash, pero " <<  gruposTemporal[nuevaPosicion]->obtenerGrupo() << " ya se encontraba en esa posicion." << endl << endl<< endl<< endl;
            }
        }
    }
    grupos = gruposTemporal;
}

// Ejemplo de cadena esperada: ADD NEW-GROUP clientes FIELDS (nombre STRING, apellido STRING, celular INTEGER);
void Grupos::agregarGrupo(string instrGrupoAAgregar){
    // Eliminar |ADD NEW-GROUP | -> 14 caracteres
    instrGrupoAAgregar.erase(0, 14);

    // Obtener el nombre del grupo
    string grupo = "";
    for (int i = 0; instrGrupoAAgregar[i] != ' '; i++){
        grupo += instrGrupoAAgregar[i];
    }

    // Eliminar grupo + | FIELDS |  -> grupo.length +  8 
    instrGrupoAAgregar.erase(0, grupo.length() + 8);

    // Agregar el grupo
    agregarGrupo(grupo, instrGrupoAAgregar);
}


// Ejemplo de paso de parametro "campos": (nombre STRING, apellido STRING, celular INTEGER);
void Grupos::agregarGrupo(string nombreGrupo, string campos){
    // Quitar ( y  );
    if (campos[0]                 == ' ' ){ campos.erase(0                 , 1 ); }
    if (campos[0]                 == '(' ){ campos.erase(0                 , 1 ); }
    if (campos[campos.length()-1] == ';' ){ campos.erase(campos.length()-2 , 1 ); }
    if (campos[campos.length()-1] == ')' ){ campos.erase(campos.length()-2 , 1 ); }
    // Agregar el grupo
    int posicionGrupo = hash(nombreGrupo);
    if(grupos[posicionGrupo] == nullptr){
        // Si la posicion no esta ocupada, crear el grupo
        int cantidadTipos = contarTipos(campos);  
        grupos[posicionGrupo] = new Campos(cantidadTipos, nombreGrupo);
        uso++;
        cout<<endl<<endl<<"Grupos.h: se ha creado un grupo nuevo usando agregarGrupo()."<<endl;
        cout<<"Nombre del grupo que agregado: "<<nombreGrupo<<endl;
        cout<<"Posicion en la tabla retornada por hash: "<<to_string(posicionGrupo)<<endl<<endl;

        if(uso > (tamanio*.6)){
            reHash();
            cout<<endl<<endl<<"Grupos.h: se ha superado el 60 por ciento de uso por lo que se realizo el rehash."<<endl<<endl;
        }


        // Separar los " " y operar
        string acumulador; 
        string campo; 
        string tipo; 
        for (int i = 0; i < campos.length(); i++)
        {
            if(campos[i] != ' '){
                acumulador += campos[i];
                if(acumulador.length() > 2){
                    if(acumulador[acumulador.length()-1] == ','){
                        acumulador.erase(acumulador.length()-2, 1);
                    }
                }
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
    }else{
        //Si la posicion ya esta ocupada, hubo una colision, informar del problema
        cout<<endl<<endl<<"Se quiso crear un grupo en Grupos.h - agregarGrupo() pero ocurrio una colision."<<endl;
        cout<<"Nombre del grupo que se quiso agregar: "<<nombreGrupo<<endl;
        cout<<"Posicion en la tabla retornada por hash: "<<to_string(posicionGrupo)<<endl<<endl;
    }    
}


int Grupos::contarTipos(string cadena){
    int cantidadTipos = 0; 
    string acumulador; 
    for (int i = 0; i < cadena.length()-1; i++)
    {
        acumulador += cadena[i];
        if(acumulador == " "){
            acumulador = "";
        }else if(acumulador == "STRING" | acumulador == "INTEGER" | acumulador == "CHAR" | acumulador == "DATE"    ){
            
            cantidadTipos++;

        }
    }

    return cantidadTipos; 
}

// Estructura de string esperada: ADD CONTACT IN amigos FIELDS (Pedro, Alvarez, 12345678, 02-05-1998);
void Grupos::agregarContacto(string instrContactoAAgregar){

    // Eliminar ADD CONTACT IN -> Son 15 caracteres 
    instrContactoAAgregar.erase(0, 15);

    // Obtener el grupo (desde 0 hasta " ")
    string grupo = "";
    int contadorString; 
    for (contadorString = 0; instrContactoAAgregar[contadorString] != ' '; contadorString++){
        grupo += instrContactoAAgregar[contadorString];
    }

    // Eliminar |ADD CONTACT IN grupo FIELDS | de la cadena -> Son 15 + grupo.length + 8
    contadorString = 15 + grupo.length() + 8;
    instrContactoAAgregar.erase(0, contadorString);
    
    // Insertar tupla en el grupo
    grupos[hash(grupo)]->insertarTuplaOrdenada(instrContactoAAgregar);
}


// Estructura de string esperada: FIND CONTACT IN clientes CONTACT-FIELD apellido=alvarez;
string Grupos::obtenerContacto(string instrContactoABuscar){

    // Quitar |FIND CONTACT IN | de la cadena -> 16 espacios
    instrContactoABuscar.erase(0,16);

    // Obtener el grupo donde buscar
    string grupo = "";
    for (int i = 0; instrContactoABuscar[i] != ' '; i++){
        grupo +=  instrContactoABuscar[i];
    }

    // quitar |grupo CONTACT-FIELD | de la cadena -> grupo.length + 15
    instrContactoABuscar.erase(0, grupo.length()+15);

    // obtener el nombre del campo
    string nombreCampo = "";
    for (int i = 0; instrContactoABuscar[i] != '='; i++){
        nombreCampo += instrContactoABuscar[i];
    }

    //eliminar |campo=| de la cadena -> nombreCampo.length + 1
    instrContactoABuscar.erase(0, nombreCampo.length()+1);

    //Eliminar ; al final
    string valor = instrContactoABuscar; 
    if(instrContactoABuscar[instrContactoABuscar.length()-1] == ';'){    
        instrContactoABuscar.erase(instrContactoABuscar.length()-2, 1); 
        valor = instrContactoABuscar;
    }

    // Retornar la tupla
    return(grupos[hash(grupo)]->obtenerPorContenido(nombreCampo, valor));
} 