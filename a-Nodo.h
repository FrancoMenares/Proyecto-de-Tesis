
#pragma once
#include <iostream>
//#include <vector>

using namespace std;


class Nodo{
  private:
    int id        ; //identificador
    float costo   ; //costo de viaje
    float tiempo  ; //tiempo de viaje
    Nodo* padre   ; //nodo antecesor

  public:
    Nodo(){}      ; //construcctor
    ~Nodo(){}     ; //destrucctor
    
    //------------- id -------------
    void set_id(int id)            ;
    int  get_id(void)              ;
    
    //------------- costo -------------
    void set_costo(float costo)    ;
    float get_costo(void)          ;
    
    //------------- tiempo -------------
    void set_tiempo(float tiempo)  ;
    float get_tiempo(void)         ;
    
    //------------- padre -------------
    void set_padre(Nodo* padre)    ;
    Nodo* get_padre(void)          ;
    
    //------------- imprimir -------------
    void imprimir_nodo(void)       ;
};