#ifndef DATE_H
#define DATE_H

#include <string>

using namespace std; 

class Date{

    private:
        int ano; 
        int dia; 
        int mes; 
    public: 
        void stringAFecha(string fecha);
        Date(string fecha);
        string obtFecha();

}; 

Date::Date(string fecha){
    stringAFecha(fecha);
}

void Date::stringAFecha(string fecha){
    
        if(fecha[0] == ' '){
            fecha.erase(0,1);
        }
        //Converir las partes del string a fecha
        // 01-10-2024 
        // dia = 0-1 recorrido 2
        // mes = 3-4 recorrido 2
        // ano = 7-9 recorrido 4
        try{
            dia = stoi(fecha.substr(0, 2));
        }catch(const exception& e){
            dia = 0; 
        }
        try{
            mes = stoi(fecha.substr(3, 2));
        }catch(const exception& e){
            mes = 0; 
        }
        try{
            ano = stoi(fecha.substr(6, 4));
        }catch(const exception& e){
            ano = 0; 
        }
    
    
}

string Date::obtFecha(){
    string resultado = "";

    if(dia < 10){
        resultado += "0";
    }
    resultado += to_string(dia);
    resultado += "-";    

    if(mes<10){
        resultado += "0";
    }
    resultado +=to_string(mes);
    resultado += "-";

    resultado += to_string(ano);
    //resultado = to_string(dia) + "/"+to_string(mes)+"/"+to_string(ano);

    return resultado; 
}

#endif