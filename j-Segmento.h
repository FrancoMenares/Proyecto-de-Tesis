
#pragma once
#include <iostream>

#include "d-Cliente.h"

using namespace std;


class Segmento{
  private:
    Cliente* cliente_i  ; //origen del segmento
    Cliente* cliente_j  ; //destino del segmento
    float tiempo_i      ; //tiempo al inicio del segmento
    float costo_i       ; //costo al inicio del segmento
    float tasa_i        ; //tasa de fallo al inicio del segmento
    float tiempo_t      ; //tiempo al termino del segmento
    float costo_t       ; //costo al termino del segmento
    float tasa_t        ; //tasa de fallo al termino del segmento
    int   demanda_t     ; //demanda al termino del segmento

  public:
    Segmento(Cliente* cliente_i, Cliente* cliente_j) ; //construcctor 1
    Segmento(const Segmento &s)                      ; //construcctor 2
    ~Segmento(){}                                    ; //destrucctor

    //------------- clientes -------------
    void set_cliente_i(Cliente* cliente_i) ;
    Cliente* get_cliente_i(void)           ;
    
    void set_cliente_j(Cliente* cliente_j) ;
    Cliente* get_cliente_j(void)           ;
    
    //------------- tiempo inicio -------------
    void set_tiempo_i(float tiempo_i)      ;
    float get_tiempo_i(void)               ;
    
    //------------- costo inicio -------------
    void set_costo_i(float costo_i)        ;
    float get_costo_i(void)                ;
    
    //------------- tasa fallo inicio -------------
    void set_tasa_i(float tasa_i)          ;
    float get_tasa_i(void)                 ;

    //------------- tiempo termino -------------
    void set_tiempo_t(float tiempo_t)      ;
    float get_tiempo_t(void)               ;
    
    //------------- costo termino -------------
    void set_costo_t(float costo_t)        ;
    float get_costo_t(void)                ;
    
    //------------- tasa fallo termino -------------
    void set_tasa_t(float tasa_t)          ;
    float get_tasa_t(void)                 ;
    
    //------------- demanda termino -------------
    void set_demanda_t(int demanda_t)      ;
    int get_demanda_t(void)                ;

    //------------- imprimir segmento -------------
    void imprimir_segmento(void)           ;
};