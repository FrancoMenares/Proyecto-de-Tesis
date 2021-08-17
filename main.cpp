
#include <iostream>
#include <random>
#include <vector>
#include <time.h>

#include "b-Red.h"
#include "c-LecturaRed.h"
#include "e-Instancia.h"
#include "f-LecturaInstancia.h"
#include "i-Preprocesamiento.h"
#include "n-Poblacion.h"

#include "z-EscrituraInstancia.h"
#include "z-EscrituraFrente.h"
#include "z-Trazado.h"

#include "ñ-AjusteHora.h"
#include "o-CambioCliente.h"

using namespace std;


int main(int argc, char **argv){

  //identificacion ARGV
  string archivo_red = argv[1]          ; //nombre archivo red
  string archivo_ins = argv[2]          ; //nombre archivo instancia
  float frec_salidas = atof(argv[3])/60 ; //frecuencia para preprocesamiento de la red
  int semilla = atoi(argv[4])           ; //semilla de ejecucion
  int lambda =  atoi(argv[5])           ; //tamaño de la poblacion
  
  //srand(semilla)                        ; //se fija una semilla 
  srand(985)                              ; //se fija una semilla 

  //Lectura Red de carreteras
  LecturaRed lr(archivo_red)  ; //se crea un objeto de tipo LecturaRed
  Red* red = lr.lectura_red() ; //se lee la red de carreteras
  //red->imprimir_red()         ;
  
  //Lectura Instancia
  LecturaInstancia li(archivo_ins)              ; //se crea un objeto de tipo LecturaInstancia
  Instancia* instancia = li.lectura_instancia() ; //se lee la red de carreteras
  //instancia->imprimir_instancia()               ;

  //preprocesamiento de la red
  Preprocesamiento* preprocesar = new Preprocesamiento()     ; //se crea un objeto de tipo Preprocesamiento
  //preprocesar->preprocesar_red(red, instancia, frec_salidas) ; //se preprocesa la rede de carreteras
  preprocesar->preprocesar_red(red, instancia, 0.5)          ; //se preprocesa la rede de carreteras
  preprocesar->imprimir_tiempo_ejecucion()                   ;



  //Escribir .dat para el modelo
  EscrituraInstancia escribir_i(archivo_ins) ;
  escribir_i.escribir_instancia(instancia)   ;



  //Construccion de la poblacion
  Poblacion* poblacion = new Poblacion(instancia) ; //se crea un objeto de tipo Poblacion
  poblacion->construir_poblacion_inicial(1)       ; //se construye la poblacion inicial
  poblacion->imprimir_poblacion()                 ;

  //Mejoramiento de la hora
  //AjusteHora* ajustar = new AjusteHora()                             ;
  //ajustar->ajustar_hora_ruta(poblacion->get_individuo(0), instancia) ;
  //poblacion->imprimir_poblacion()                                    ;

  //Mutacion
  CambioCliente* cambiar_cliente = new CambioCliente()                               ;

  for (int i=0; i<100; i++){
    cambiar_cliente->cambiar_cliente_aleatorio(poblacion->get_individuo(0), instancia) ;
    poblacion->imprimir_poblacion()                                                    ;

    getchar();
  }



  //Extraer ruta completa
  //Trazado* trazo = new Trazado()            ; //se crea un objeto de tipo Trazado
  //trazo->imprimir_ruta(aux, red, instancia) ; //se imprimir las rutas de una solucion

  //Escribir archivo para el frente
  EscrituraFrente escribir(poblacion) ;
  escribir.escribir_frente();
  
}









