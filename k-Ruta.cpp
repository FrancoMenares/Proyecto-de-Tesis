
#include "k-Ruta.h"


//------------- constructor -------------
Ruta::Ruta(int id)                                        { this->id = id                                 ;}

//------------- id -------------
void Ruta::set_id(int id)                                 { this->id = id                                 ;}
int Ruta::get_id(void)                                    { return this->id                               ;}

//------------- segmentos -------------
void Ruta::agregar_segmento(Segmento* segmento)           { this->segmentos.push_back(segmento)           ;}
Segmento* Ruta::get_segmento(int pos)                     { return this->segmentos.at(pos)                ;}
vector <Segmento*> Ruta::get_segmentos(void)              { return this->segmentos                        ;}

//------------- aporte f1 -------------
void Ruta::set_aporte_f1(float aporte_f1)                 { this->aporte_f1 = aporte_f1                   ;}
float Ruta::get_aporte_f1(void)                           { return this->aporte_f1                        ;}

//------------- aporte f2 -------------
void Ruta::set_aporte_f2(float aporte_f2)                 { this->aporte_f2 = aporte_f2                   ;}
float Ruta::get_aporte_f2(void)                           { return this->aporte_f2                        ;}

//------------- tiempo inicio -------------
void Ruta::set_tiempo_inicio(float tiempo_inicio)         { this->tiempo_inicio = tiempo_inicio           ;}
float Ruta::get_tiempo_inicio(void)                       { return this->tiempo_inicio                    ;}

//------------- tiempo termino -------------
void Ruta::set_tiempo_termino(float tiempo_termino)       { this->tiempo_termino = tiempo_termino         ;}
float Ruta::get_tiempo_termino(void)                      { return this->tiempo_termino                   ;}

//------------- tiempo restante -------------
void Ruta::set_tiempo_restante(float tiempo_restante)     { this->tiempo_restante = tiempo_restante       ;}
float Ruta::get_tiempo_restante(void)                     { return this->tiempo_restante                  ;}

//------------- capacidad restante -------------
void Ruta::set_capacidad_restante(int capacidad_restante) { this->capacidad_restante = capacidad_restante ;}
int Ruta::get_capacidad_restante(void)                    { return this->capacidad_restante               ;}

//------------- imprimir ruta -------------
void Ruta::imprimir_ruta(void){
  cout << "Id            :\t" << this->id                 << endl ;
  cout << "Aporte f1     :\t" << this->aporte_f1          << endl ;
  cout << "Aporte f2     :\t" << this->aporte_f2          << endl ;
  cout << "T. Inicio     :\t" << this->tiempo_inicio      << endl ;
  cout << "T. Termino    :\t" << this->tiempo_termino     << endl ;
  cout << "T. Restante   :\t" << this->tiempo_restante    << endl ;
  cout << "Cap. Restante :\t" << this->capacidad_restante << endl ;
  cout << "Ruta          :\t" ;  

  for (int i=0; i<this->segmentos.size(); i++){
    if (i == this->segmentos.size()-1){
      cout << this->get_segmento(i)->get_cliente_i()->get_id_nodo() << " - " ;
      cout << this->get_segmento(i)->get_cliente_j()->get_id_nodo() << endl ;
    } else {
      cout << this->get_segmento(i)->get_cliente_i()->get_id_nodo() << " - " ;
      //cout << this->get_segmento(i)->get_cliente_j()->get_id_nodo() << endl ;
    } 
  }
  cout << endl ;
}
