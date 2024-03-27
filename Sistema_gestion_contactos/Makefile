CPP = g++
TARGET = ../Binario_compilado/contactos
OBJ_DIR = ./obj
ESTR = ./Estructuras
ARB = ./Estructuras/Arboles
HSH = ./Estructuras/Hash

# all
all: $(TARGET)

$(TARGET): $(OBJ_DIR)/Main.o
	$(CPP) $(OBJ_DIR)/Main.o -o $(TARGET)

#Las definiciones que necesita Main para funcionar estan en los archivos Nodo.h y Arbol.h
$(OBJ_DIR)/Main.o: Main.cpp $(ESTR)/Nodo.h $(ESTR)/Arbol.h  $(ESTR)/Date.h $(ESTR)/TiposCamposEnum.h  $(ARB)/ArbolBase.h $(ARB)/ArbolInt.h $(ARB)/ArbolString.h $(ARB)/ArbolChar.h $(ARB)/ArbolDate.h $(HSH)/Campos.h $(HSH)/Grupos.h
	$(CPP) -c Main.cpp -o $(OBJ_DIR)/Main.o

# clean
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
