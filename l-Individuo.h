
#pragma once
#include <iostream>
#include <vector>

#include "k-Ruta.h"

using namespace std;


class Individuo{
  private:
    vector <Ruta*> rutas ; //rutas de la solucion 
    float f1             ; //costo operacional de la solucion
    float f2             ; //tasa de fallo acumulada de la solucion

    int dominado_por             ; //cantidad de individuos que dominan al individuo
    vector <Individuo*> domina_a ; //conjunto de individuos que son dominados por el individuo
    int ranking                  ; //frente en el que se posisiona
    float dist_h                 ; //distancia de hacinamiento

  public:    
    Individuo()                   ; //Constructor    
    Individuo(const Individuo &i) ; //construcctor 2
    ~Individuo()                  ; //Destructor

    //------------- rutas -------------
    void agregar_ruta(Ruta* ruta)             ;
    void reemplazar_ruta(int pos, Ruta* ruta) ;
    void eliminar_ruta(int pos)               ;
    Ruta* get_ruta(int pos)                   ;
    vector <Ruta*> get_rutas(void)            ;

    //------------- f1 / f2 -------------
    void set_f1(float f1)                     ;
    float get_f1(void)                        ;
    void set_f2(float f2)                     ;
    float get_f2(void)                        ;
    void actualizar_funciones(void)           ;

    //------------- dominado_por -------------
    void set_dominado_por(int cant)           ;
    int get_dominado_por(void)                ;

    //------------- dominado_a -------------
    void agregar_individuo_dominado(Individuo* individuo) ;
    Individuo* get_individuo_dominado(int pos)            ;
    vector <Individuo*> get_individuos_dominados(void)    ;
    void eliminar_individuos_dominados(void)              ;

    //------------- dominado_por -------------
    void set_ranking(int ranking) ;
    int get_ranking(void)         ;

    //------------- dominado_por -------------
    void set_hacinamiento(float dist) ;
    float get_hacinamiento(void)      ;

    //------------- imprimir individuo -------------
    void imprimir_individuo(void)                   ;
    void imprimir_individuo_2(Instancia* instancia) ;
};
 