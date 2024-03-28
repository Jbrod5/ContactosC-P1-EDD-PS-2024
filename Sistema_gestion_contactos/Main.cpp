#include <iostream>
#include <fstream>

#include "./Estructuras/Nodo.h"
#include "./Estructuras/Arbol.h"
#include "./Estructuras/Hash/Grupos.h"


using namespace std; 

int main() {
    
    Grupos* grupos = new Grupos();  
    string comando = "";
    int comandoLong = 0; 
    string comandoSubstr;
    bool leerCLI = true; 

    ifstream* archivo;

    while(comando != "SALIR;"){
        cout<<endl<<endl<<endl<<endl<<endl<<"Gestion de contactos CLI >   "; 
        comando = "";

        if(leerCLI){
            //cin >> comando;
            getline(cin, comando);

        }else{

            if (archivo != nullptr  && archivo->is_open()) {
                getline(*archivo, comando);
                cout<<"Comando reconocido desde archivo: |"<<comando<<"|"<<endl;
                if(comando.empty()){
                    archivo->close();
                    leerCLI = true;
                }else{
                    // Borrar salto de linea y retorno de carro
                    if(comando.length()>2){
                        if(comando[comando.length()-1] == '\n'){
                            cout<<"Se borro un salto de linea"<<endl;
                            comando.erase(comando.length()-1, 1);
                        }
                        if(comando[comando.length()-1] == '\r'){
                            cout<<"Se borro un retorno de carro"<<endl;
                            comando.erase(comando.length()-1, 1);
                        }
                    }
                }
            }else{
                comando = "";
                leerCLI = true;
            }
        }


        comandoLong = comando.length();
        if(comando[comandoLong-1] == '\n'){
            comando.erase( comandoLong-2, 1);
        }

        // 1. EXIT;
        if(comando == "EXIT;"){
            cout << "Saliendo de Gestion de contactos CLI."<<endl; 
            break;


        }
        // 2. ADD NEW-GROUP -> 13 caracteres 
        if(comandoLong > 13){
            if(comando.substr(0,13) == "ADD NEW-GROUP"){
                cout<<"Agregar grupo reconocido."<<endl;
                grupos->agregarGrupo(comando);

            }
        
        // 3. ADD CONTACT IN -> 14 caracteres
        }if(comandoLong > 14){
            if(comando.substr(0,14) == "ADD CONTACT IN"){
                cout<<"Agregar contactos reconocido."<<endl;
                grupos->agregarContacto(comando);
            }
        
        
        // 4. FIND CONTACT IN ->
        }if(comandoLong > 15){
            if(comando.substr(0,15) == "FIND CONTACT IN"){
                cout<<"Buscar contacto reconocido."<<endl;
                grupos->obtenerContacto(comando);
            }

        }//5. GENERATE GRAPH GROUP grupo; -> 20 caracteres
        if(comandoLong > 19){
            if(comando.substr(0,20) == "GENERATE GRAPH GROUP"){
                cout<<"Generar grafo de grupo reconocido."<<endl; 
                grupos->generarGrafoGrupo(comando);
            }
        }
        //6. |IMPORT FROM SCRIPT | - 19 caracteres; 
        if(comandoLong > 19){
            if(comando.substr(0,18) == "IMPORT FROM SCRIPT"){
                cout<<"Importar desde script reconocido."<<endl; 
                //Borrar IMPORT FROM SCRIPT 
                comando.erase(0,19);

                //Borrar ;
                if(comando[comando.length()-1] == ';'){
                    comando.erase(comando.length()-1, 1);
                }
                //Crear el archivo
                archivo = new ifstream(comando);
                leerCLI = false; 
            }
        }
        comando = "";

    }

    return 0;  
}
