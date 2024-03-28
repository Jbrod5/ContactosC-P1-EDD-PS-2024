#ifndef ARBOL_DATE_H
#define ARBOL_DATE_H

#include "ArbolBase.h"
#include "../Arbol.h"
#include "../Nodo.h"
#include "../Date.h"
#include <string>

    // Contenedor para Arbol, con tipo de dato int definido
    class ArbolDate : public ArbolBase{
        private: 
            Arbol<Date*>* arbol; 

        public: 
            ArbolDate(std::string nombreCampo);
            bool estaVacio();
            void insertar(string fecha, int id);


            Nodo<Date*>* buscarPorId(int id);
            Nodo<Date*>* buscarPorContenido(string fecha);
       
            void balancear();
            void generarGrafico();

            string obtenerGrafo() override;
            
    };

    ArbolDate::ArbolDate(std::string nombreCampo){
            arbol = new Arbol<Date*>(nombreCampo);
            this->nombreCampo = nombreCampo; 
        }

    bool ArbolDate::estaVacio(){ return arbol->estaVacio(); }

    void ArbolDate::balancear(){ arbol->balancear(); }

    void ArbolDate::generarGrafico(){ arbol->generarGrafico(); }


    /* Metodos especiales */

    void ArbolDate::insertar(string fecha, int id){
        Date* date = new Date(fecha);
        arbol->insertar(date, id);
    }

    Nodo<Date*>* ArbolDate::buscarPorId(int id){
        return arbol->buscarPorId(id);
    }

    Nodo<Date*>* ArbolDate::buscarPorContenido(string fecha){
        Date* date = new Date(fecha);
        return arbol->buscarPorContenido(date);
    }

    string ArbolDate::obtenerGrafo (){
        return arbol->obtenerGrafo();
    }
#endif