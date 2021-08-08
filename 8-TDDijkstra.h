
#pragma once
#include <iostream>
#include <vector>
#include <queue>

#include "2-Red.h"
#include "5-Instancia.h"
#include "7-Costos.h"

using namespace std;


class TDDijkstra{
  private:
  
  public:
    TDDijkstra(){}       ; //Constructor
    ~TDDijkstra(){}      ; //Destructor
    
    //--------------- TD_Dijkstra ---------------
    void ruta_mas_corta(Red* red, Instancia* instancia, Costos* costos, int nodo_inicio, float hora_inicio) ;

    //--------------- imprimir_ruta ---------------
    void imprimir_ruta(Red* red, int id_inicio, int id_destino) ;
};



