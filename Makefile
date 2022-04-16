#Aquí se agregan los objetos para compilar
OBJS = main.o a-Nodo.o b-Red.o c-LecturaRed.o d-Cliente.o e-Instancia.o f-LecturaInstancia.o g-Costos.o h-TDDijkstra.o i-Preprocesamiento.o j-Segmento.o k-Ruta.o l-Individuo.o m-Construccion.o n-Poblacion.o ñ-AjusteHora.o o-CambioCliente.o p-InvertirClientes.o q-OX.o s-Frentes.o t-ReRuteo.o z-EscrituraInstancia.o z-Trazado.o

#Para poner opciones de la versión de C++ a ocupar 
FLAGS = -O3

#Que genere el archivo llamado así
all: ProyectoTesis

#Que se va a hacer cada vez que se llame al archivo
ProyectoTesis: $(OBJS)
	g++ -o ProyectoTesis $(OBJS) $(FLAGS)
  
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
	./ProyectoTesis Red-Carreteras/Red-Carreteras-3.txt Instancias/InstanciasChicas/b-Instancia12.txt 60.0 137 100 50 60 90 100000 30

exe1:
	./ProyectoTesis Red-Carreteras/Red-Carreteras-3.txt Instancias/InstanciasGrandes/e-Instancia47.txt 15.0 137 100 50 60 90 100000 30
  
graf:
	python3 y-GraficarFrentes.py b-Instancia17.txt

clean: 
	rm -rf *.o ProyectoTesis

