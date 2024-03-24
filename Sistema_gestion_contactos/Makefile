CPP = g++
TARGET = contactos

#all
all: .all-post

.all-post: Nodo.o Arbol.o Main.o
		$(CPP) Nodo.o  Arbol.o Main.o -o $(TARGET)

Nodo.o: Nodo.h
Arbol.o: Arbol.h
Main.o: 
		$(CPP) -c Main.cpp

#clean
clean:
	rm -f *.o $(TARGET)