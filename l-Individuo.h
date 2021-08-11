
#pragma once
#include <iostream>
#include <vector>

#include "k-Ruta.h"

using namespace std;


class Individuo{
  private:
    int id               ; //id de la solucion
    vector <Ruta*> rutas ; //rutas de la solucion 
    float f1             ; //costo operacional de la solucion
    float f2             ; //tasa de fallo acumulada de la solucion

  public:
    Individuo(int id)    ; //Constructor    
    ~Individuo(){}       ; //Destructor

    //------------- id -------------
    void set_id(int id)                       ;
    int get_id(void)                          ;

    //------------- rutas -------------
    void agregar_ruta(Ruta* ruta)             ;
    void reemplazar_ruta(int pos, Ruta* ruta) ;
    Ruta* get_ruta(int pos)                   ;
    vector <Ruta*> get_rutas(void)            ;

    //------------- f1 / f2 -------------
    void set_f1(float f1)                     ;
    float get_f1(void)                        ;

    void set_f2(float f2)                     ;
    float get_f2(void)                        ;

    void actualizar_funciones(void)           ;

    //------------- imprimir individuo -------------
    void imprimir_individuo(void)             ;
    void imprimir_individuo_2(void)           ;
};
