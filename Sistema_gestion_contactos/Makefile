CPP = g++
TARGET = contactos

# all
all: $(TARGET)

$(TARGET): Main.o
	$(CPP) Main.o -o $(TARGET)

#Las definiciones que necesita Main para funcionar estan en los archivos Nodo.h y Arbol.h
Main.o: Main.cpp Nodo.h Arbol.h
	$(CPP) -c Main.cpp

# clean
clean:
	rm -f *.o $(TARGET)
