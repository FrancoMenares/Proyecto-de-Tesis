
#pragma once
#include <iostream>
#include <vector>

using namespace std;


class Cliente{
  private:
    int id_cliente             ; //id de cliente
    int id_nodo                ; //id de nodo
    float **costo_hasta        ; //costo de viaje hasta todos los clientes
    float **tiempo_hasta       ; //tiempo de viaje hasta todos los clientes
    vector <float> costo_aten  ; //costo de atencion del cliente
    vector <float> tiempo_aten ; //tiempo de atencion del cliente
    vector <float> tasas_fallo ; //tasas de fallo del cliente

  public:
    Cliente(){}                ; //Constructor
    ~Cliente(){}               ; //Destructor

    //--------------- id_cliente ---------------
    void set_id_cliente(int id_cliente)              ;
    int get_id_cliente(void)                         ;
    
    //------------ id_nodo -------------
    void set_id_nodo(int id_nodo)                    ;
    int get_id_nodo(void)                            ;

    //---------- costo_hasta -----------
    void set_tam_costo_hasta(int fils, int cols)     ;
    void set_costo_hasta(int i, int p, float val)    ;
    float get_costo_hasta(int i, int p)              ;

    //---------- tiempo_hasta -----------
    void set_tam_tiempo_hasta(int fils, int cols)    ;
    void set_tiempo_hasta(int i, int p, float val)   ;
    float get_tiempo_hasta(int i, int p)             ;

    //--------------- costos atencion ---------------
    void agregar_costo_aten(float val)               ;
    float get_costo_aten(int pos)                    ;

    //--------------- tiempo atencion ---------------
    void agregar_tiempo_aten(float val)              ;
    float get_tiempo_aten(int pos)                   ;

    //--------------- tasas_fallo ---------------
    void agregar_tasas_fallo(float val)              ;
    float get_tasas_fallo(int pos)                   ;

    //---------- impresiones -----------
    void imprimir_cliente(void)                      ;
};