
#include <iostream>
#include <random>
#include <vector>
#include <time.h>

#include "2-Red.h"
#include "3-LecturaRed.h"
#include "5-Instancia.h"
#include "6-LecturaInstancia.h"
#include "9-Preprocesamiento.h"

using namespace std;


int main(int argc, char **argv){
  
  //Lectura Red de carreteras
  LecturaRed lr(argv[1])      ; //se crea un objeto de tipo LecturaRed
  Red* red = lr.lectura_red() ; //se lee la red de carreteras
  red->imprimir_red()         ;
  
  //Lectura Instancia
  LecturaInstancia li(argv[2])                  ; //se crea un objeto de tipo LecturaInstancia
  Instancia* instancia = li.lectura_instancia() ; //se lee la red de carreteras
  instancia->imprimir_instancia()               ;

  //preprocesamiento de la red
  clock_t t_inicial = clock()                                      ; 

  Preprocesamiento* preprocesar = new Preprocesamiento()           ; //se crea un objeto de tipo Preprocesamiento
  float frecuencia_salidas = 30.0/60                               ; //salidas cada 30 minutos
  preprocesar->preprocesar_red(red, instancia, frecuencia_salidas) ; //se preprocesa la rede de carreteras
  
  float t_final = difftime(clock(), t_inicial)/CLOCKS_PER_SEC      ;
  cout << "Tiempo: " << t_final << " seg" << endl                  ;

}













