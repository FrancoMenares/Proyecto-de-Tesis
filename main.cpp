
#include <iostream>
#include <random>
#include <vector>
#include <time.h>

#include "2-Red.h"
#include "3-LecturaRed.h"
#include "5-Instancia.h"
#include "6-LecturaInstancia.h"

#include "7-Costos.h"

using namespace std;


int main(int argc, char **argv){
  
  //Lectura Red de carreteras
  LecturaRed lr(argv[1])             ; //se crea un objeto de depo LecturaRed
  Red* carreteras = lr.lectura_red() ; //se lee la red de carreteras
  
  //carreteras->imprimir_red()               ;
  //carreteras->get_nodo(0)->imprimir_nodo() ;
  
  //Lectura Instancia
  LecturaInstancia li(argv[2])                  ; //se crea un objeto de depo LecturaRed
  Instancia* instancia = li.lectura_instancia() ; //se lee la red de carreteras
  
  //instancia->imprimir_instancia()               ;
  //instancia->get_cliente(0)->imprimir_cliente() ;

  //costos
  Costos* costos = new Costos() ;
  costos->imprimir_detalle_costos() ;

  //costos->imprimir_costos_nodo(0.2) ;
  //costos->imprimir_costos_arco(32.4, 0.15, 0.09) ;

}













