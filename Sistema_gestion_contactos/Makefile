CPP = g++
TARGET = Sistema_gestion_contactos

#all
all: $(TARGET)

$(TARGET):  Nodo.o  Arbol.o Main.o
		$(CPP) Nodo.o Arbol.o  Main.o -o $(TARGET)

Nodo.o: ./Estructuras/Nodo.cpp ./Estructuras/Nodo.h
		$(CPP) -c Nodo.cpp

Arbol.o: ./Estructuras/Arbol.cpp ./Estructuras/Arbol.h
		$(CPP) -c Arbol.cpp

Main.o: 
		$(CPP) -c Main.cpp

#clean
clean:
	rm -f *.o $(TARGET)