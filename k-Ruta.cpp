//
#include "k-Ruta.h"


//------------- constructores -------------
Ruta::Ruta(int id)       { 
  this->id = id         ;
  this->aporte_f1 = 0.0 ; 
  this->aporte_f2 = 0.0 ; 
}


Ruta::Ruta(const Ruta &r){
  this->id = r.id                                 ; 
  this->aporte_f1 = r.aporte_f1                   ; 
  this->aporte_f2 = r.aporte_f2                   ; 
  this->tiempo_inicio = r.tiempo_inicio           ; 
  this->tiempo_termino = r.tiempo_termino         ; 
  this->tiempo_restante = r.tiempo_restante       ; 
  this->capacidad_restante = r.capacidad_restante ; 
  for (Segmento* i: r.segmentos){
    Segmento* j = new Segmento(*i)                ;
    this->segmentos.push_back(j)                  ;
  }
}


//------------- destructor -------------
Ruta::~Ruta(){
  for (Segmento *s: this->segmentos) {
    delete s;
  }
  this->segmentos.clear();
  this->segmentos.shrink_to_fit();
}


//------------- id -------------
void Ruta::set_id(int id)                                 { this->id = id                                 ;}
int Ruta::get_id(void)                                    { return this->id                               ;}


//------------- segmentos -------------
void Ruta::agregar_segmento(Segmento* segmento)           { this->segmentos.push_back(segmento)                           ;}
void Ruta::insertar_segmento(int pos, Segmento* segmento) { this->segmentos.insert(this->segmentos.begin()+pos, segmento) ;}
void Ruta::eliminar_segmento(int pos)                     { this->segmentos.erase(this->segmentos.begin()+pos)            ;}
Segmento* Ruta::get_segmento(int pos)                     { return this->segmentos.at(pos)                                ;}
vector <Segmento*> Ruta::get_segmentos(void)              { return this->segmentos                                        ;}


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
      cout << this->get_segmento(i)->get_cliente_i()->get_id_nodo()+1 << " - " ;
      cout << this->get_segmento(i)->get_cliente_j()->get_id_nodo()+1 << endl  ;
      break                                                                    ;
    } else {
      cout << this->get_segmento(i)->get_cliente_i()->get_id_nodo()+1 << " - " ;
    } 

    if ((i+1)%7 == 0){
      cout << endl << "               \t"                                      ;
    }
  }
}


void Ruta::imprimir_ruta_2(Instancia* instancia){
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
      cout << this->get_segmento(i)->get_cliente_i()->get_id_nodo()+1 << " - " ;
      cout << this->get_segmento(i)->get_cliente_j()->get_id_nodo()+1 << endl  ;
      break                                                                    ;
    } else {
      cout << this->get_segmento(i)->get_cliente_i()->get_id_nodo()+1 << " - " ;
    } 

    if ((i+1)%7 == 0){
      cout << endl << "               \t"                                      ;
    }
  }

  cout << endl ;


  float tiempo = this->get_tiempo_inicio() ;
  int p                                    ;
  float tiempo_viaje                       ;
  float costo_viaje                        ;
  float tiempo_aten                        ;
  float costo_aten                         ;
  float tasa_fallo                         ;

  for (Segmento* s: this->get_segmentos()){
    cout << "Arco          : " << s->get_cliente_i()->get_id_nodo()+1 << " - " << s->get_cliente_j()->get_id_nodo()+1 << endl ;
    cout << "Tiempo inicio : " << tiempo << endl                                                                              ;
    
    p = tiempo / instancia->get_frec_salidas()                                                   ;
    tiempo_viaje = s->get_cliente_i()->get_tiempo_hasta(s->get_cliente_j()->get_id_cliente(), p) ;
    costo_viaje  = s->get_cliente_i()->get_costo_hasta(s->get_cliente_j()->get_id_cliente(), p)  ;

    cout << "Tiempo viaje  : " << tiempo_viaje << endl                                           ;
    cout << "Costo viaje   : " << costo_viaje  << endl                                           ;

    tiempo = tiempo + tiempo_viaje                                                               ;

    if (s->get_cliente_j() != instancia->get_cliente(instancia->get_cant_clientes())){
      p = tiempo / instancia->get_frec_salidas()           ;

      tiempo_aten = s->get_cliente_j()->get_tiempo_aten(p) ;
      costo_aten  = s->get_cliente_j()->get_costo_aten(p)  ;
      tasa_fallo  = s->get_cliente_j()->get_tasas_fallo(p) ;

      tiempo = tiempo + tiempo_aten                        ;
      
      cout << "Tiempo aten   : " << tiempo_aten << endl    ;
      cout << "Costo aten    : " << costo_aten  << endl    ;
      cout << "Tasa fallo    : " << tasa_fallo  << endl    ;
    }

    cout << endl ;
  }
}
