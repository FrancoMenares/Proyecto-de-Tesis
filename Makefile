#Aquí se agregan los objetos para compilar
OBJS = main.o a-Nodo.o b-Red.o c-LecturaRed.o d-Cliente.o e-Instancia.o f-LecturaInstancia.o g-Costos.o h-TDDijkstra.o i-Preprocesamiento.o j-Segmento.o k-Ruta.o l-Individuo.o m-Construccion.o n-Poblacion.o ñ-AjusteHora.o o-CambioCliente.o z-EscrituraFrente.o z-EscrituraInstancia.o z-Trazado.o

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

#------------------------- ARGV -------------------------
#archivo Red
#archivo Instancia
#frecuencia de Preprocesamiento
#semilla
#tamaño de la poblacion

salto:
	.

exe:
	./Proyecto-de-Tesis Red-Carreteras/Red-Carreteras.txt Instancias/prueba10.txt 30.0 123 5

exe1:
	./Proyecto-de-Tesis Red-Carreteras/Red-Carreteras.txt Instancias/prueba50.txt 30.0 123 5

clean: 
	rm -rf *.o Proyecto-de-Tesis