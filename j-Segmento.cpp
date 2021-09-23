
#include "j-Segmento.h"


//------------- constructores -------------
Segmento::Segmento(Cliente* cliente_i, Cliente* cliente_j){
  this->cliente_i = cliente_i ;
  this->cliente_j = cliente_j ;
}


Segmento::Segmento(const Segmento &s){
    this->cliente_i = s.cliente_i ;
    this->cliente_j = s.cliente_j ;
    this->tiempo_i = s.tiempo_i   ;
    this->costo_i = s.costo_i     ;
    this->tasa_i = s.tasa_i       ;
    this->tiempo_t = s.tiempo_t   ;
    this->costo_t = s.costo_t     ;
    this->tasa_t = s.tasa_t       ;
    this->demanda_t = s.demanda_t ;
}


//------------- clientes -------------
void Segmento::set_cliente_i(Cliente* cliente_i) { this->cliente_i = cliente_i ;}
Cliente* Segmento::get_cliente_i(void)           { return this->cliente_i      ;}
void Segmento::set_cliente_j(Cliente* cliente_j) { this->cliente_j = cliente_j ;}
Cliente* Segmento::get_cliente_j(void)           { return this->cliente_j      ;}


//------------- tiempo inicio -------------
void Segmento::set_tiempo_i(float tiempo_i)      { this->tiempo_i = tiempo_i   ;}
float Segmento::get_tiempo_i(void)               { return this->tiempo_i       ;}


//------------- costo inicio -------------
void Segmento::set_costo_i(float costo_i)        { this->costo_i = costo_i     ;}
float Segmento::get_costo_i(void)                { return this->costo_i        ;}


//------------- tasa fallo inicio -------------
void Segmento::set_tasa_i(float tasa_i)          { this->tasa_i = tasa_i       ;}
float Segmento::get_tasa_i(void)                 { return this->tasa_i         ;}


//------------- tiempo termino -------------
void Segmento::set_tiempo_t(float tiempo_t)      { this->tiempo_t = tiempo_t   ;}
float Segmento::get_tiempo_t(void)               { return this->tiempo_t       ;}


//------------- costo termino -------------
void Segmento::set_costo_t(float costo_t)        { this->costo_t = costo_t     ;}
float Segmento::get_costo_t(void)                { return this->costo_t        ;}


//------------- tasa fallo termino -------------
void Segmento::set_tasa_t(float tasa_t)          { this->tasa_t = tasa_t       ;}
float Segmento::get_tasa_t(void)                 { return this->tasa_t         ;}


//------------- demanda termino -------------
void Segmento::set_demanda_t(int demanda_t)      { this->demanda_t = demanda_t ;}
int Segmento::get_demanda_t(void)                { return this->demanda_t      ;}


//------------- imprimir segmento -------------
void Segmento::imprimir_segmento(void){
  cout << "Segmento :\t" << this->cliente_i->get_id_nodo()+1 << " - " << this->cliente_j->get_id_nodo()+1 << endl ;
  cout << "Tiempo   :\t" << this->tiempo_i                   << " - " << this->tiempo_t                   << endl ;
  cout << "Costo    :\t" << this->costo_i                    << " - " << this->costo_t                    << endl ;
  cout << "Tasa     :\t" << this->tasa_i                     << " - " << this->tasa_t                     << endl ;
  cout << "Demanda  :\t" << this->demanda_t                                                               << endl ;
  cout << endl ;
}


















