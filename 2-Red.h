
#pragma once
#include <iostream>
#include <vector>

#include "1-Nodo.h"

using namespace std;


class Red{
  private:
    int cant_nodos          ; //cantidad de nodos
    int cant_arcos          ; //cantidad de arcos
    int cant_periodos       ; //cantidad de periodos de tiempo
    float **matriz_ady      ; //matriz de adyacencia, distancia y velocidad
    vector <Nodo*> Nodos    ; //lista de nodos de la red
    float **tasas_fallo     ; //matriz de tasas de fallos
    float **limites_periodo ; //limite inferior y superior de cada periodo

  public:
    Red(){}                 ; //Constructor
    ~Red(){}                ; //Destructor
    
    //--------------- cant_nodos ---------------
    void set_cant_nodos(int cant_nodos)             ;
    int get_cant_nodos(void)                        ; 
    
    //--------------- cant_arcos ---------------
    void set_cant_arcos(int cant_arcos)             ; 
    int get_cant_arcos(void)                        ; 

    //-------------- cant_periodos -------------
    void set_cant_periodos(int cant_periodos)       ;
    int get_cant_periodos(void)                     ;

    //--------- Matriz Adyacencia ---------
    void agregar_fils(int fils)                     ;
    void agregar_cols(int fil, int cols)            ;
    void set_matriz_ady(int i, int j, float val)    ;
    float get_matriz_ady(int i, int j)              ;

    //--------------- Nodos ---------------
    void agregar_nodo(Nodo* nodo)                   ;
    Nodo* get_nodo(int pos)                         ;
    vector <Nodo*> get_nodos(void)                  ;
    void reiniciar_nodos(void)                      ;

    //------------ Tasas Fallo ------------
    void set_tam_tasas_fallo(int fils, int cols)    ;
    void set_tasa_fallo(int i, int p, float val)    ;
    float get_tasa_fallo(int i, int p)              ;

    //------------ periodos ------------
    void set_tam_periodos(int cant_periodos)        ;
    void set_periodo(int p, int t, float val)       ;
    float get_ini_periodo(int p)                    ;
    float get_fin_periodo(int p)                    ;

    //------------ Impresiones -----------
    void imprimir_red(void)                         ;
    void imprimir_ady_nodo(int id)                  ;
    void imprimir_tasas_nodo(int id)                ;
    void imprimir_limites_periodos(void)            ;
};

