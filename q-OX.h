
#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <queue>

#include "e-Instancia.h"
#include "l-Individuo.h"

using namespace std;


class OX{
  private:
  
  public:
    OX(){}       ; //Constructor
    ~OX(){}      ; //Destructor
    
    //--------------- cruza dos padres generando dos hijos ---------------
    vector <Individuo*> cruzar_individuos(Individuo* individuo1, Individuo* individuo2, Instancia* instancia, int cant_hijos) ;

    //--------------- extrae la secuencia de las rutas de un individuo ---------------
    vector <int> extraer_secuencia(Individuo* individuo)                                              ;

    //--------------- extraer herencia x ---------------
    vector <int> extraer_herencia_x(vector <int> padre_x, int corte, int tam_corte)                   ;

    //--------------- extraer herencia y ---------------
    vector <int> extraer_herencia_y(vector <int> padre_y, vector <int> herencia_x, int corte2)        ;

    //--------------- crear hijo a partir de la herencia de los padres ---------------
    vector <int> crear_hijo(vector <int> herencia_x, vector <int> herencia_y, int corte1, int corte2) ;

    //--------------- evalua si la secuencia permite crear rutas factibles ---------------
    bool evaluar_secuencia(Instancia* instancia, vector <int> secuencia, float hora_inicio, int desde, int hasta) ;

    //--------------- arma ruta a partir de una secuencia factble ---------------
    Ruta* armar_ruta(Instancia* instancia, vector <int> secuencia, float hora_inicio, int id, int desde, int hasta) ;
    
    //--------------- evaluacion de la ruta ---------------
    bool evaluar_ruta_desde(Instancia* instancia, Ruta* ruta, int desde) ;

    //--------------- actualizacion de la ruta ---------------
    bool actualizar_ruta_desde(Instancia* instancia, Ruta* ruta, int desde) ;

    //--------------- se genera el hijo como un individuo ---------------
    Individuo* generar_individuo(Individuo* padre, vector <int> secuencia, Instancia* instancia)      ;
};