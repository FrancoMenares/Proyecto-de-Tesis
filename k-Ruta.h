
#pragma once
#include <iostream>
#include <vector>

#include "j-Segmento.h"

using namespace std;


class Ruta{
  private:
    int id                       ; //id de la ruta
    vector <Segmento*> segmentos ; //segmentos de la ruta
    float aporte_f1              ; //f1 de la ruta
    float aporte_f2              ; //f2 de la ruta
    float tiempo_inicio          ; //hora de inicio de la ruta
    float tiempo_termino         ; //hora de termino de la ruta
    float tiempo_restante        ; //tiempo de trabajo disponible
    int capacidad_restante       ; //capacidad de atencion disponible

  public:
    Ruta(int id)        ; //construcctor 1
    Ruta(const Ruta &r) ; //construcctor 2
    ~Ruta(){}           ; //destrucctor

    //------------- id -------------
    void set_id(int id)                                 ;
    int get_id(void)                                    ;

    //------------- segmentos -------------
    void agregar_segmento(Segmento* segmento)           ;
    void insertar_segmento(int pos, Segmento* segmento) ;
    void eliminar_segmento(int pos)                     ;
    Segmento* get_segmento(int pos)                     ;
    vector <Segmento*> get_segmentos(void)              ;

    //------------- aporte f1 -------------
    void set_aporte_f1(float aporte_f1)                 ;
    float get_aporte_f1(void)                           ;

    //------------- aporte f2 -------------
    void set_aporte_f2(float aporte_f2)                 ;
    float get_aporte_f2(void)                           ;

    //------------- tiempo inicio -------------
    void set_tiempo_inicio(float tiempo_inicio)         ;
    float get_tiempo_inicio(void)                       ;

    //------------- tiempo termino -------------
    void set_tiempo_termino(float tiempo_termino)       ;
    float get_tiempo_termino(void)                      ;

    //------------- tiempo restante -------------
    void set_tiempo_restante(float tiempo_restante)     ;
    float get_tiempo_restante(void)                     ;

    //------------- capacidad restante -------------
    void set_capacidad_restante(int capacidad_restante) ;
    int get_capacidad_restante(void)                    ;

    //------------- imprimir ruta -------------
    void imprimir_ruta(void)                            ;
};