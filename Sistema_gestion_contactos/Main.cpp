#include "./Estructuras/Nodo.h"
#include "./Estructuras/Arbol.h"
#include <iostream>

using namespace std; 

int main() {
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
}
