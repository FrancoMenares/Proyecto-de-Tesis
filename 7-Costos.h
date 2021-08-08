
#pragma once
#include <iostream>
#include <math.h>

using namespace std;


class Costos{
  private:
    float valorC  ; //precio por litro decombustible
    float rend    ; //comsumo de combustible en ralenti
    float sueldoC ; //sueldo mensual por conductor
    float diasC   ; //dias de trabajo mensual 
    float horasC  ; //horas de trabajo diario
    float valorN  ; //precio de un neumatico
    float vidaUN  ; //vida util un neumatico 
    float cantN   ; //cantidad de neumaticos del vehiculo
    float valorCA ; //precio por cambio de aceite
    float distCA  ; //distancia entre cambio de aceite

  public:
    Costos()    ; //Constructor    
    ~Costos(){} ; //Destructor

    float get_valorC(void)  ; 
    float get_rend(void)    ; 
    float get_sueldoC(void) ; 
    float get_diasC(void)   ;  
    float get_horasC(void)  ; 
    float get_valorN(void)  ; 
    float get_vidaUN(void)  ;  
    float get_cantN(void)   ; 
    float get_valorCA(void) ; 
    float get_distCA(void)  ; 
    
    //------------- costos nodo -------------
    float costo_combustible_nodo(float tiemp)                     ;
    float costo_conductor_nodo(float tiemp)                       ;
    float costo_total_nodo(float tiemp)                           ;

    //------------- costos arco -------------
    float costo_combustible_arco(float vel, float dist)           ;
    float costo_conductor_arco(float tiemp)                       ;
    float costo_desgaste_neumatico(float dist)                    ;  
    float costo_cambio_aceite(float dist)                         ;
    float costo_total_arco(float vel, float dist, float tiemp)    ;

    //------------- impresiones -------------
    void imprimir_detalle_costos(void)                            ;
    void imprimir_costos_nodo(float tiemp)                        ;
    void imprimir_costos_arco(float vel, float dist, float tiemp) ;
};
