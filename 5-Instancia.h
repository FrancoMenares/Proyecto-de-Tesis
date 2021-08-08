
#pragma once
#include <iostream>
#include <vector>

#include "4-Cliente.h"

using namespace std;


class Instancia{
  private:
    int cant_clientes           ; //cantidad de clientes
    vector <Cliente*> clientes  ; //lista de clientes
    int cant_camiones           ; //cantidad de camiones
    int cap_camiones            ; //capacidad de los camiones
    float inicio_horizonte      ; //tiempo de inicio del horizonte de planificacion
    float termino_horizonte     ; //tiempo de termino del horizonte de planificacion
    int cant_salidas            ; //cantidad de intervalos luego del preprocesar
  
  public:
    Instancia(){}               ; //Constructor
    ~Instancia(){}              ; //Destructor

    //--------------- cant_clientes ---------------
    void set_cant_clientes(int cant_clientes)     ;
    int get_cant_clientes(void)                   ;

    //--------------- Clientes ---------------
    void agregar_cliente(Cliente* cliente)        ;
    Cliente* get_cliente(int pos)                 ;
    vector <Cliente*> get_clientes(void)          ;

    //--------------- cant_camiones ---------------
    void set_cant_camiones(int cant_camiones)     ;
    int get_cant_camiones(void)                   ;

    //--------------- cap_camiones ---------------
    void set_cap_camiones(int cap_camiones)       ;
    int get_cap_camiones(void)                    ;

    //--------------- inicio_horizonte ---------------
    void set_inicio(float inicio)                 ;
    float get_inicio(void)                        ;

    //--------------- termino_horizonte ---------------
    void set_termino(float termino)               ;
    float get_termino(void)                       ;
    
    //------------ cant_salidas -------------
    void set_cant_salidas(int cant_salidas)       ;
    int get_cant_salidas(void)                    ;

    //------------ Impresiones -----------
    void imprimir_instancia(void)                 ;    
};