#Aquí se agregan los objetos para compilar
OBJS = main.o a-Nodo.o b-Red.o c-LecturaRed.o d-Cliente.o e-Instancia.o f-LecturaInstancia.o g-Costos.o h-TDDijkstra.o i-Preprocesamiento.o j-Segmento.o k-Ruta.o l-Individuo.o m-Construccion.o n-Poblacion.o ñ-AjusteHora.o o-CambioCliente.o p-InvertirClientes.o q-OX.o s-Frentes.o z-EscrituraInstancia.o z-Trazado.o

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
#pobabilidad de aceptacion de padre
#probabilidad de cruce
#probabilidad de mutacion
#cantidad de generaciones

exe:
	./Proyecto-de-Tesis Red-Carreteras/Red-Carreteras-3.txt Instancias/a-Instancia7.txt 60.0 123 5 80 100 90 1000

ins:
	python3 y-GenerarInstancias.py

clean: 
	rm -rf *.o Proyecto-de-Tesis