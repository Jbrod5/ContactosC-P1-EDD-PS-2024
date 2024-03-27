#include "./Estructuras/Nodo.h"
#include "./Estructuras/Arbol.h"
#include <iostream>
#include "./Estructuras/Hash/Grupos.h"


using namespace std; 

int main() {
    
    /*
    // Crear un objeto de tipo Arbol<int>
    Arbol<int>* arbol;
    arbol = new Arbol<int>();

    // Insertar nodos en el árbol
    arbol->insertar(50, 1);
    arbol->insertar(30, 2);
    arbol->insertar(70, 3);
    arbol->insertar(20, 4);
    arbol->insertar(40, 5);
    arbol->insertar(60, 6);
    arbol->insertar(80, 7);

    // Generar el gráfico del árbol
    arbol->generarGrafico();

    return 0;
    */
    Grupos* grupos = new Grupos();  
    string comando = "";
    int comandoLong = 0; 
    string comandoSubstr;

    while(comando != "SALIR;"){
        cout<<"Gestion de contactos CLI > "; 
        cin >> comando;
        comandoLong = comando.length();

        // 1. EXIT;
        if(comando == "EXIT;"){
            cout << "Saliendo de Gestion de contactos CLI."<<endl; 
            break;

        // 2. ADD NEW-GROUP -> 13 caracteres 
        }if(comandoLong > 13){
            if(comando.substr(0,13) == "ADD NEW-GROUP"){
                grupos->agregarGrupo(comando);
            }
        
        // 3. ADD CONTACT IN -> 14 caracteres
        }if(comandoLong > 14){
            if(comando.substr(0,14) == "ADD CONTACT IN"){
                grupos->agregarContacto(comando);
            }
        
        
        // 4. FIND CONTACT IN ->
        }if(comandoLong > 15){
            if(comando.substr(0,15) == "FIND CONTACT IN"){
                grupos->obtenerContacto(comando);
            }
        }

        comando = "";

    }

    return 0;  
}
