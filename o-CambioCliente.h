
#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <random>

#include "e-Instancia.h"
#include "l-Individuo.h"

using namespace std;


class CambioCliente{
  private:
  
  public:
    CambioCliente(){}       ; //Constructor
    ~CambioCliente(){}      ; //Destructor
    
    //--------------- cambio nodo aleatorio ---------------
    void cambiar_cliente_aleatorio(Individuo* individuo, Instancia* instancia) ; 

    //--------------- actualizacion de la ruta ---------------
    bool actualizar_ruta_desde(Instancia* instancia, Ruta* ruta, int desde) ;

    //--------------- actualizacion de la ruta ---------------
    bool evaluar_ruta_desde(Instancia* instancia, Ruta* ruta, int desde) ;

    //--------------- agregar nueva ruta a la solucion ---------------
    Ruta* agregar_ruta_nueva(Instancia* instancia, Cliente* cliente, int id) ;
};