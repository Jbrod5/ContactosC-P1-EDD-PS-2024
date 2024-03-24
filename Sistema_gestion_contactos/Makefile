CPP = g++
TARGET = ../Binario_compilado/contactos
OBJ_DIR = ./obj
ESTRUCTURAS = ./Estructuras

# all
all: $(TARGET)

$(TARGET): $(OBJ_DIR)/Main.o
	$(CPP) $(OBJ_DIR)/Main.o -o $(TARGET)

#Las definiciones que necesita Main para funcionar estan en los archivos Nodo.h y Arbol.h
$(OBJ_DIR)/Main.o: Main.cpp $(ESTRUCTURAS)/Nodo.h $(ESTRUCTURAS)/Arbol.h
	$(CPP) -c Main.cpp -o $(OBJ_DIR)/Main.o

# clean
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
