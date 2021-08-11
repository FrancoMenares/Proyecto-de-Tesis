
#pragma once
#include <iostream>
#include <vector>
#include <queue>

#include "b-Red.h"
#include "e-Instancia.h"
#include "g-Costos.h"

using namespace std;


class TDDijkstra{
  private:
  
  public:
    TDDijkstra(){}       ; //Constructor
    ~TDDijkstra(){}      ; //Destructor
    
    //--------------- Dijkstra ---------------
    void ruta_mas_corta(Red* red, int nodo_inicio) ;
    
    //--------------- TD_Dijkstra ---------------
    void td_ruta_mas_corta(Red* red, Costos* costos, int nodo_inicio, float hora_inicio) ;

    //--------------- imprimir_ruta ---------------
    void imprimir_ruta(Red* red, int id_inicio, int id_destino, int ruta) ;
};