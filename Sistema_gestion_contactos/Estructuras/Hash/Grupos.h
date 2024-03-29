/* Contiene la logica para manejar la tabla hash DE GRUPOS */
#ifndef GRUPOS_H
#define GRUPOS_H

#include "../Arbol.h"
//#include "../Logger.h"
#include <fstream>
#include <iostream>
//#include "../TiposCamposEnum.h"
#include "Campos.h"
using namespace std; 

class Grupos{

    private: 
        int uso;     //cantidad de elementos insertados
        int tamanio; //tamanio del array
        Campos** grupos;  
        //Logger logger; 
        
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
        void generarGrafoGrupo(string instrGenerarGrafoGrupo); //Genera un grafo de un grupo con graphviz, cadena esperada: GENERATE GRPH GROUP grupo;
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
                //logger.log(nombreGrupoActual+" fue movido de la posicion " +  to_string(i) + " a la posicion" + to_string(nuevaPosicion) + " por la funcion reHash en Grupos.h.");
                cout<<nombreGrupoActual<<" fue movido de la posicion "<< to_string(i) <<" a la posicion"<<to_string(nuevaPosicion)<< " por la funcion reHash en Grupos.h."<<endl; 
            }else{
                //logger.log("Hubo una colision en Grupos.h: en la funcion reHash.\nSe intento asignar el grupo: "+ nombreGrupoActual + " en la posicion: " + to_string(nuevaPosicion) + " otorgada por la funcion hash, pero " +  gruposTemporal[nuevaPosicion]->obtenerGrupo() + " ya se encontraba en esa posicion.");
                //std::cout << endl << endl << endl << "Hubo una colision en Grupos.h: en la funcion reHash." << endl; 
                //std::cout << "Se intento asignar el grupo: " << nombreGrupoActual << " en la posicion: " << to_string(nuevaPosicion) << " otorgada por la funcion hash, pero " <<  gruposTemporal[nuevaPosicion]->obtenerGrupo() << " ya se encontraba en esa posicion." << endl << endl<< endl<< endl;
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
    if (campos[campos.length()-1] == ';' ){ campos.erase(campos.length()-1 , 1 ); }
    if (campos[campos.length()-1] == ')' ){ campos.erase(campos.length()-1 , 1 ); }
    // Agregar el grupo
    int posicionGrupo = hash(nombreGrupo);
    if(grupos[posicionGrupo] == nullptr){
        // Si la posicion no esta ocupada, crear el grupo
        int cantidadTipos = contarTipos(campos);  
        grupos[posicionGrupo] = new Campos(cantidadTipos, nombreGrupo);
        uso++;
        //logger.log("Grupos.h: se ha creado un grupo nuevo usando agregarGrupo().\nNombre del grupo que agregado: "+nombreGrupo+"\nPosicion en la tabla retornada por hash: "+to_string(posicionGrupo));
        cout<<"Grupos.h: se ha creado un grupo nuevo usando agregarGrupo()."<<endl;
        cout<<"Nombre del grupo que agregado: "<<nombreGrupo<<endl;
        cout<<"Posicion en la tabla retornada por hash: "<<to_string(posicionGrupo)<<endl;

        if(uso > (tamanio*.6)){
            reHash();
            cout<<endl<<endl<<"Grupos.h: se ha superado el 60 por ciento de uso por lo que se realizo el rehash."<<endl<<endl;
            //logger.log("Grupos.h: se ha superado el 60 por ciento de uso por lo que se realizo el rehash.");
        }


        // Separar los " " y operar
        string acumulador; 
        string campo = ""; 
        string tipo = ""; 
        for (int i = 0; i < campos.length(); i++)
        {
            while(campo == "" | tipo == ""){
                if(i < campos.length() && campos[i] != ' '){
                    acumulador += campos[i];
                    if(acumulador.length() > 0){
                        if(acumulador[acumulador.length()-1] == ','){
                            acumulador.erase(acumulador.length()-1, 1);
                        }
                    }
                }else{
                    // Establecer par clave valor
                    if(campo.empty()){
                        campo = acumulador;
                        acumulador = "";
                    }else if(tipo.empty()){
                        tipo = acumulador;
                        acumulador = "";
                    }
                }
                i++;
            }
            
            // Verificar que haya par clave valor para agregar el tipo 
            if(campo.length() > 0 && tipo.length() > 0){
                if(tipo == "INTEGER"){
                    grupos[posicionGrupo]->agregarCampo(campo, 1);
                }else if(tipo == "STRING"){
                    grupos[posicionGrupo]->agregarCampo(campo, 2);
                }else if(tipo == "CHAR"){
                    grupos[posicionGrupo]->agregarCampo(campo, 3);
                }else if(tipo == "DATE"){
                    grupos[posicionGrupo]->agregarCampo(campo, 4);
                }else{
                    //logger.log("Error en Grupos.h en funcion AgregarGrupo. \nSe intento agregar un grupo pero no se reconocio el tipo deseado. \nTipo que se quiso agregar: " + tipo);
                    cout<<"Error en Grupos.h en funcion AgregarGrupo: " << endl; 
                    cout<<"Se intento agregar un grupo pero no se reconocio el tipo deseado."<<endl;
                    cout<<"Tipo que se quiso agregar: " <<tipo<<endl; 
                }
                campo = "";
                tipo = "";
                i--;
            }
            
        }
    }else{
        //Si la posicion ya esta ocupada, hubo una colision, informar del problema
        //logger.log("Se quiso crear un grupo en Grupos.h - agregarGrupo() pero ocurrio una colision.\nNombre del grupo que se quiso agregar: "+nombreGrupo+"Posicion en la tabla retornada por hash: "+to_string(posicionGrupo));
        cout<<"Se quiso crear un grupo en Grupos.h - agregarGrupo() pero ocurrio una colision."<<endl;
        cout<<"Nombre del grupo que se quiso agregar: "<<nombreGrupo<<endl;
        cout<<"Posicion en la tabla retornada por hash: "<<to_string(posicionGrupo)<<endl;
    }    
}


int Grupos::contarTipos(string cadena){
    int cantidadTipos = 0;
    string acumulador = "";
    for (int i = 0; i < cadena.length(); i++){
        if(cadena[i] != ' '){
            acumulador += cadena[i];
        }else{
            acumulador = "";
        }
        if(acumulador.compare("STRING") == 0 || acumulador.compare("INTEGER") == 0 || acumulador.compare("CHAR") == 0 || acumulador.compare("DATE") == 0){
            cantidadTipos++;
            acumulador = "";
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
    for (contadorString = 0; contadorString < instrContactoAAgregar.length() && instrContactoAAgregar[contadorString] != ' '; contadorString++){
        grupo += instrContactoAAgregar[contadorString];
    }

    // Eliminar |grupo FIELDS | de la cadena -> grupo.length + 8
    contadorString = grupo.length() + 8;
    instrContactoAAgregar.erase(0, contadorString);
    
    //logger.log("Grupos.h: Grupo donde agregar: "+ grupo+"\nInstruccion por procesar: " + instrContactoAAgregar);
    cout<<"Grupos.h: Grupo donde agregar: " <<grupo<<endl;
    cout<<"Instruccion por procesar: "<<instrContactoAAgregar<<endl;
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
        instrContactoABuscar.erase(instrContactoABuscar.length()-1, 1); 
        valor = instrContactoABuscar;
    }

    // Retornar la tupla
    return(grupos[hash(grupo)]->obtenerPorContenido(nombreCampo, valor));
} 

void Grupos::generarGrafoGrupo(string instrGenerarGrafoGrupo){
    //1. Remover |GENERATE GRPH GROUP | (21 caracteres)
    if(instrGenerarGrafoGrupo.length()>21){
        instrGenerarGrafoGrupo.erase(0,21);
    }
    //2. Remover ;
    if(instrGenerarGrafoGrupo.length()>2){
        if(instrGenerarGrafoGrupo[instrGenerarGrafoGrupo.length()-1] == ';'){

            instrGenerarGrafoGrupo.erase(instrGenerarGrafoGrupo.length()-1,1);
        }
    }
    //3. Lo que queda es el grupo
    Campos* grupo = grupos[hash(instrGenerarGrafoGrupo)];
    cout<<"|"<<instrGenerarGrafoGrupo<<"|"<<endl;
    if(grupo != nullptr){
        // Generar el grafo
        string grafo = grupo->obtenerGrafo();
        ofstream archivo("./Grafos/"+instrGenerarGrafoGrupo+".dot");
        archivo<<grafo;
        archivo.close();
        string comando = "dot -Tpng ./Grafos/" + instrGenerarGrafoGrupo + ".dot -o ./Grafos/" + instrGenerarGrafoGrupo + ".png";
        system(comando.c_str());
        //logger.log("Grupos.h: Grafo "+instrGenerarGrafoGrupo+" generado correctamente!");
        cout<<"Grupos.h: Grafo "+instrGenerarGrafoGrupo+" generado correctamente!"<<endl;

    }else{
        //logger.log("Grupos.h: generarGrafoGrupo. Hubo un error al generar el grafo del grupo: " + instrGenerarGrafoGrupo + "\nEl grupo obtenido por la funcion hash (posicion " + to_string(hash(instrGenerarGrafoGrupo)) +" ) es nulo.");
        cout<<"Grupos.h: generarGrafoGrupo. Hubo un error al generar el grafo del grupo: "<<instrGenerarGrafoGrupo<<endl;
        cout<<"El grupo obtenido por la funcion hash (posicion "<< hash(instrGenerarGrafoGrupo)<<" ) es nulo."<<endl; 
    }
}