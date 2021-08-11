
#include "m-Construccion.h"


//--------------- ordenar clientes aleatoriamente ---------------
vector <int> Construccion::ordenar_clientes(int cant_clientes){
  vector <int> ids                       ; //se crea vector para guardar los id de cliente
  for (int i=0; i<cant_clientes; i++){
    ids.push_back(i)                     ; //se insertan los id de clientes al vector
  }

  vector <int> secuencia                 ; //se crea vector para guardar secuencia aleatoria
  for (int i=0; i<cant_clientes; i++){
    int elegido = rand()%(ids.size())    ; //se elige un id aleatorio que no este en la secuencia
    secuencia.push_back(ids.at(elegido)) ; //se agrega el id a la secuencia
    ids.erase(ids.begin()+elegido)       ; //se elimina el id del vector de id
  }
  return secuencia                       ; //se retorna la secuencia
}

//--------------- impresiones ---------------
void Construccion::imprimir_secuencia(vector <int> secuencia){
  for (int i: secuencia){
    cout << i << " "      ;
  }
  cout << endl            ;
}

//--------------- construir ruta aleatoria ---------------
vector <int> Construccion::ruta_aleatoria(Instancia* instancia, Ruta* ruta, float inicio_hasta, vector <int> secuencia){
  bool debug = false ;
  
  Segmento* segmento                         ; //puntero a segmento
  int h_inicio = instancia->get_inicio()*10  ; //hora min posible para inicio ruta
  int h_fin    = inicio_hasta*10             ; //hora max posible para inicio ruta
  float h_fin2 = instancia->get_termino()    ; //fin horizonte planificacion

  float t_inicio = (float)(rand()%(h_fin-h_inicio+1)+h_inicio)/10 ; //hora inicio aleatoria (ruta y segmento)
  ruta->set_tiempo_inicio(t_inicio)                               ; //se setea hora inicio de la ruta
  ruta->set_tiempo_restante(h_fin2 - t_inicio)                    ; //se setea tiempo de trabajo disponible
  ruta->set_capacidad_restante(instancia->get_cap_camiones())     ; //se setea capacidad disponible

  Cliente* i = instancia->get_cliente(instancia->get_cant_clientes()) ; //cliente i, inicialmente el deposito
  Cliente* j                                                          ; //cliente j
  float costo                                                         ; //costo del segmento
  float tiempo                                                        ; //tiempo del segmento
  int p                                                               ; //periodo de tiempo
  float c_inicio = 0                                                  ; //costo al inicio del segmento
  float ts_inicio = 0                                                 ; //tasa al inicio del segmento
  int d_inicio = 0                                                    ; //demanda al inicio del segmento

  if (debug) this->imprimir_secuencia(secuencia) ;

  while (ruta->get_capacidad_restante() > 0 & t_inicio < h_fin2 & secuencia.size() > 0){
    j = instancia->get_cliente(secuencia.at(0))             ; //cliente j, siempre el primero en secuencia
    segmento = new Segmento(i, j)                           ; //se crea segmento de ruta

    p = t_inicio / instancia->get_frec_salidas()            ; //se obtiene el periodo de tiempo
    tiempo = i->get_tiempo_hasta(j->get_id_cliente(), p)    ; //tiempo hasta el viaje
    costo  = i->get_costo_hasta(j->get_id_cliente(), p)     ; //costo hasta el viaje

    p = (t_inicio + tiempo) / instancia->get_frec_salidas() ; //se obtiene el periodo de tiempo
    tiempo = tiempo + j->get_tiempo_aten(p)                 ; //tiempo hasta la atencion
    costo = costo + j->get_costo_aten(p)                    ; //costo hasta la atencion

    if ((t_inicio + tiempo) > h_fin2){   //si al ultimo cliente no se llega antes del fin de horizonte
      break                            ; //se deja para la siguiente ruta y se retorna deposito
    }                                 

    segmento->set_tiempo_i(t_inicio) ; //se setea el tiempo al inicio del segmento
    segmento->set_costo_i(c_inicio)  ; //se setea el costo al inicio del segmento
    segmento->set_tasa_i(ts_inicio)  ; //se setea la tasa de fallo al inicio del segmento  

    t_inicio = t_inicio + tiempo                  ; //se obtiene tiempo al final del segmento
    c_inicio = c_inicio + costo                   ; //se obtiene costo al final del segmento
    ts_inicio = ts_inicio + j->get_tasas_fallo(p) ; //se obtiene tasa fallo al final del segmento
    d_inicio = d_inicio + 1                       ; //se obtiene demanda al final del segmento

    segmento->set_tiempo_t(t_inicio)  ; //se setea el tiempo al final del segmento
    segmento->set_costo_t(c_inicio)   ; //se setea el costo al final del segmento
    segmento->set_tasa_t(ts_inicio)   ; //se setea la tasa de fallo al final del segmento  
    segmento->set_demanda_t(d_inicio) ; //se setea la tasa de fallo al final del segmento 
    
    ruta->set_aporte_f1(ruta->get_aporte_f1() + costo)                     ; //se setea el aporte de la ruta a f1
    ruta->set_aporte_f2(ruta->get_aporte_f2() + j->get_tasas_fallo(p))     ; //se setea el aporte de la ruta a f2
    ruta->set_tiempo_restante(h_fin2 - t_inicio)                           ; //se setea el tiempo disponible de la ruta
    ruta->set_capacidad_restante(instancia->get_cap_camiones() - d_inicio) ; //se setea la capacidad disponible del camion
    
    ruta->agregar_segmento(segmento)     ; //se agrega el segmento a la ruta
    secuencia.erase(secuencia.begin()+0) ; //se elimina el id del vector de id
    i = j                                ; //el cliente j es i en el siguiente segmento

    if (debug) this->imprimir_secuencia(secuencia) ;
  }

  j = instancia->get_cliente(instancia->get_cant_clientes()) ; //cliente j, finalmente el deposito
  segmento = new Segmento(i, j)                              ; //se crea segmento de ruta

  p = t_inicio / instancia->get_frec_salidas()         ; //se obtiene el periodo de tiempo
  tiempo = i->get_tiempo_hasta(j->get_id_cliente(), p) ; //tiempo hasta el viaje
  costo  = i->get_costo_hasta(j->get_id_cliente(), p)  ; //costo hasta el viaje

  segmento->set_tiempo_i(t_inicio) ; //se setea el tiempo al inicio del segmento
  segmento->set_costo_i(c_inicio)  ; //se setea el costo al inicio del segmento
  segmento->set_tasa_i(ts_inicio)  ; //se setea la tasa de fallo al inicio del segmento  

  t_inicio = t_inicio + tiempo     ; //se obtiene tiempo al final del segmento
  c_inicio = c_inicio + costo      ; //se obtiene costo al final del segmento

  segmento->set_tiempo_t(t_inicio) ; //se setea el tiempo al final del segmento
  segmento->set_costo_t(c_inicio)  ; //se setea el costo al final del segmento
  
  ruta->set_aporte_f1(ruta->get_aporte_f1() + costo) ; //se setea el aporte de la ruta a f1
  ruta->set_tiempo_termino(t_inicio)                 ; //se setea el aporte de la ruta a f2
  ruta->set_tiempo_restante(h_fin2 - t_inicio)       ; //se seteal el tiempo disponible de la ruta
  ruta->agregar_segmento(segmento)                   ; //se agrega el segmento a la ruta

  if (debug) cout << endl ;

  return secuencia ;
}

//--------------- devolver clientes a la secuencia ---------------
vector <int> Construccion::devolver_clientes_a_secuencia(Ruta* ruta, vector <int> secuencia){
  for (int i=0; i<ruta->get_segmentos().size()-1; i++){
    secuencia.push_back(ruta->get_segmento(i)->get_cliente_j()->get_id_cliente()) ;
    //secuencia.insert(secuencia.begin(), ruta->get_segmento(i)->get_cliente_j()->get_id_cliente()) ;
  }
  return secuencia ;
}

//--------------- construir individuo aleatorio ---------------
void Construccion::individuo_aleatorio(Instancia* instancia, Individuo* individuo){
  struct comparar_tiempos_inicio{                                      //se crea estructura para ordenar la cola de prioridad
    bool operator()(Ruta* ruta1, Ruta* ruta2){                         //se compara ruta-ruta
      return ruta1->get_tiempo_inicio() < ruta2->get_tiempo_inicio() ; //criterio de ordenamiento (de mayor a menor)
    }
  }                                                                  ;

  priority_queue<Ruta, vector<Ruta*>, comparar_tiempos_inicio> cola               ; //cola de prioridad para rutas segun hora de inicio
  vector <int> secuencia = this->ordenar_clientes(instancia->get_cant_clientes()) ; //se crea una seciencia TSP
  Ruta* ruta                                                                      ; //puntero a ruta
  float inicio_hasta = instancia->get_termino()                                   ; //hora mas tarde a la que puede comenzar una ruta
  int k=0                                                                         ; //contador de rutas
  int id = 0                                                                      ; //id de las rutas
  bool reemplazo = false                                                          ; //bandera de reemplazo ruta, inicalmente falsa

  while (secuencia.size() != 0){                                         //mientras hayan clientes sin asignar
    if (!cola.empty()){
      reemplazo = true                                                 ; //se activa bandera de reemplazo
      ruta = cola.top()                                                ; //se saca de la cola la ruta a reemplazar
      secuencia = this->devolver_clientes_a_secuencia(ruta, secuencia) ; //los clientes son devueltos al final de la secuencia TSP
      inicio_hasta = ruta->get_tiempo_termino()                        ; //la nueva ruta debe iniciar tan tarde como la ruta a reemplazar
      k--                                                              ; //se descuenta una ruta al individuo
      id = ruta->get_id()                                              ; //la nueva ruta conserva el id
      cola.pop()                                                       ; //se quita la ruta a reemplazar de la cola de prioridad
    }

    while (k<instancia->get_cant_camiones()){   //mientra hayan camiones disponibles
      if (secuencia.size() == 0){               //si no quedan clientes por asignar
        break                                 ; //se detiene la construccion
      }

      ruta = new Ruta(id)                                                        ; //se crea una nueva ruta
      secuencia = this->ruta_aleatoria(instancia, ruta, inicio_hasta, secuencia) ; //ruta como fragmento de la secuencia TSP
      if (ruta->get_segmento(0)->get_cliente_i() == ruta->get_segmento(0)->get_cliente_j()){ //si se crea ruta sin clientes
        continue                                                                 ; //no se considera en la solucion
      }
      
      cola.push(ruta)                        ; //se agrega la ruta a la cola de prioridad
      if (reemplazo){                          //si se esta reemplazando una ruta
        individuo->reemplazar_ruta(id, ruta) ; //se agrega la ruta a la solucion
      } else {
        individuo->agregar_ruta(ruta)        ; //se agrega la ruta a la solucion
        k++                                  ; //se pasa a la siguiente ruta
        id++                                 ; //se actualiza el id de la ruta
      }
    }
    //cout << "----------------------------------" << endl ;
    //cout << "Quedaron " << secuencia.size() << " clientes sin asignar" << endl ;
    //cout << "----------------------------------" << endl ;
  }
  individuo->actualizar_funciones() ; //se calculan la fo de la solucion
}
