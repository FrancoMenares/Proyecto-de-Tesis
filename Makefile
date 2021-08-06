#Aquí se agregan los objetos para compilar
OBJS = main.o 

#Para poner opciones de la versión de C++ a ocupar 
FLAGS = -O3

#Que genere el archivo llamado así
all: Proyecto-de-Tesis

#Que se va a hacer cada vez que se llame al archivo
Proyecto-de-Tesis: $(OBJS)
	g++ -o Proyecto-de-Tesis $(OBJS) $(FLAGS)
  
#Para generar cualquier punto .o necesito cualquier punto .cpp
%.o: %.cpp %.h
	g++ -c $(FLAGS) $< -o $@

#Para hacer ejecuciones
salto:
	.

exe:
	./Proyecto-de-Tesis

clean: 
	rm -rf *.o Proyecto-de-Tesis