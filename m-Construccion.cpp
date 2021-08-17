
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
  
  Segmento* q                                 ; //puntero a segmento
  int h_inicio = instancia->get_inicio()*100  ; //hora min posible para inicio ruta
  int h_fin2    = inicio_hasta*100            ; //hora max posible para inicio ruta
  float h_fin = instancia->get_termino()      ; //fin horizonte planificacion

  float hora_inicio = (float)(rand()%(h_fin2-h_inicio+1)+h_inicio)/100 ; //hora inicio aleatoria (ruta y segmento)

  int cap = instancia->get_cap_camiones() ; //capcidad de los camiones
  float tiempo = hora_inicio              ; //tiempo transcurrido
  float costo = 0                         ; //costo acumulado
  float tasa = 0                          ; //tasa acumulada
  int demanda = 0                         ; //demanda atendida
  int p                                   ; //periodo de tiempo

  float tiempo_aux ;
  float costo_aux  ;

  ruta->set_aporte_f1(0)                                      ; //se setea aporte de la ruta a f1
  ruta->set_aporte_f2(0)                                      ; //se setea aporte de la ruta a f2
  ruta->set_tiempo_inicio(tiempo)                             ; //se setea tiempo de inicio de la ruta
  ruta->set_tiempo_restante(instancia->get_termino()-tiempo)  ; //se setea el tiempo restante de la ruta
  ruta->set_capacidad_restante(instancia->get_cap_camiones()) ; //se setea la capacidad disponible del camion

  Cliente* deposito = instancia->get_cliente(instancia->get_cant_clientes()) ;
  Cliente* i = deposito                                                      ;
  Cliente* j                                                                 ;

  while (ruta->get_capacidad_restante() > 0 & tiempo < h_fin & secuencia.size() > 0){
    j = instancia->get_cliente(secuencia.at(0)) ;

    q = new Segmento(i, j)  ; //se crea objeto de tipo Segmento
    q->set_tiempo_i(tiempo) ; //se setea tiempo de inicio del segmento
    q->set_costo_i(costo)   ; //se setea costo de inicio del segmento
    q->set_tasa_i(tasa)     ; //se setea tasa al inicio del segmento

    tiempo_aux = tiempo ;
    costo_aux = costo   ;

    p = tiempo / instancia->get_frec_salidas()                    ; //se identifica periodo de tiempo
    tiempo = tiempo + i->get_tiempo_hasta(j->get_id_cliente(), p) ; //se suma el tiempo de viaje
    costo = costo + i->get_costo_hasta(j->get_id_cliente(), p)    ; //se suma el costo de viaje

    p = tiempo / instancia->get_frec_salidas() ; //se identifica periodo de tiempo
    tiempo = tiempo + j->get_tiempo_aten(p)    ; //se suma el tiempo de atencion
    costo = costo + j->get_costo_aten(p)       ; //se suma el costo de atencion

    //si el cliente j no permite llegar al deposito antes del fin del horizonte
    if ((tiempo + j->get_tiempo_hasta(deposito->get_id_cliente(), p)) > h_fin){   
      tiempo = tiempo_aux ;
      costo = costo_aux   ;
      delete q            ; //se elimina el segmento
      break               ; //se deja para la siguiente ruta y se retorna deposito
    }

    tasa = tasa + j->get_tasas_fallo(p) ; //se suma la tasa de fallo
    demanda++                           ; //se suma la demanda

    q->set_tiempo_t(tiempo)   ; //se setea el tiempo al final del segmento
    q->set_costo_t(costo)     ; //se setea el costo al final del segmento
    q->set_tasa_t(tasa)       ; //se setea la tasa de fallo al final del segmento  
    q->set_demanda_t(demanda) ; //se setea la demanda cubierta al final del segmento 

    ruta->agregar_segmento(q)            ; //se agrega el segmento a la ruta
    secuencia.erase(secuencia.begin()+0) ; //se elimina el id del vector de id
    i = j                                ;
  }
  
  j = deposito           ; //cliente j, finalmente el deposito

  if (i == j){
    delete ruta      ;
    return secuencia ;
  }

  q = new Segmento(i, j) ; //se crea segmento de ruta
  
  q->set_tiempo_i(tiempo) ; //se setea tiempo de inicio del segmento
  q->set_costo_i(costo)   ; //se setea costo de inicio del segmento
  q->set_tasa_i(tasa)     ; //se setea tasa al inicio del segmento
  
  p = tiempo / instancia->get_frec_salidas()                    ; //se identifica periodo de tiempo
  tiempo = tiempo + i->get_tiempo_hasta(j->get_id_cliente(), p) ; //se suma el tiempo de viaje
  costo = costo + i->get_costo_hasta(j->get_id_cliente(), p)    ; //se suma el costo de viaje

  q->set_tiempo_t(tiempo)   ; //se setea el tiempo al final del segmento
  q->set_costo_t(costo)     ; //se setea el costo al final del segmento
  q->set_tasa_t(tasa)       ; //se setea la tasa de fallo al final del segmento  
  q->set_demanda_t(demanda) ; //se setea la demanda cubierta al final del segmento 
  
  ruta->set_aporte_f1(costo)                  ; //se setea el aporte de la ruta a f1
  ruta->set_aporte_f2(tasa)                   ; //se setea el aporte de la ruta a f2
  ruta->set_tiempo_termino(tiempo)            ; //se setea el tiempo de termino de la ruta
  ruta->set_tiempo_restante(h_fin - tiempo)   ; //se setea el tiempo restante de la ruta
  ruta->set_capacidad_restante(cap - demanda) ; //se setea la capacidad disponible del camion

  ruta->agregar_segmento(q)            ; //se agrega el segmento a la ruta

  return secuencia                            ;
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
      cola.pop()                                                       ; //se quita la ruta a reemplazar de la cola de prioridad
      secuencia = this->devolver_clientes_a_secuencia(ruta, secuencia) ; //los clientes son devueltos al final de la secuencia TSP
      inicio_hasta = ruta->get_tiempo_termino()                        ; //la nueva ruta debe iniciar tan tarde como la ruta a reemplazar
      k--                                                              ; //se descuenta una ruta al individuo
      id = ruta->get_id()                                              ; //la nueva ruta conserva el id
    }

    while (k<instancia->get_cant_camiones()){   //mientra hayan camiones disponibles
      int tam_secuencia = secuencia.size()    ; //se guarda el tamaño de la secuencia
      if (tam_secuencia == 0){                  //si no quedan clientes por asignar
        break                                 ; //se detiene la construccion
      }

      ruta = new Ruta(id)                                                        ; //se crea una nueva ruta
      secuencia = this->ruta_aleatoria(instancia, ruta, inicio_hasta, secuencia) ; //ruta como fragmento de la secuencia TSP
      
      if (tam_secuencia == secuencia.size()){ //revisa que se haya creado una ruta
        continue;
      }
      
      cola.push(ruta)                        ; //se agrega la ruta a la cola de prioridad
      if (reemplazo){                          //si se esta reemplazando una ruta
        individuo->reemplazar_ruta(id, ruta) ; //se agrega la ruta a la solucion
        k++                                  ;
      } else {
        individuo->agregar_ruta(ruta)        ; //se agrega la ruta a la solucion
        k++                                  ; //se pasa a la siguiente ruta
        id++                                 ; //se actualiza el id de la ruta
      }
    }
  }
  individuo->actualizar_funciones() ; //se calculan la fo de la solucion
}





























/*
//--------------- construir ruta aleatoria ---------------
vector <int> Construccion::ruta_aleatoria(Instancia* instancia, Ruta* ruta, float inicio_hasta, vector <int> secuencia){
  bool debug = true ;
  
  Segmento* segmento                         ; //puntero a segmento
  int h_inicio = instancia->get_inicio()*100 ; //hora min posible para inicio ruta
  int h_fin    = inicio_hasta*100            ; //hora max posible para inicio ruta
  float h_fin2 = instancia->get_termino()    ; //fin horizonte planificacion

  float t_inicio = (float)(rand()%(h_fin-h_inicio+1)+h_inicio)/100           ; //hora inicio aleatoria (ruta y segmento)
  ruta->set_tiempo_inicio(t_inicio)                                          ; //se setea hora inicio de la ruta
  ruta->set_tiempo_restante(h_fin2 - t_inicio)                               ; //se setea tiempo de trabajo disponible
  ruta->set_capacidad_restante(instancia->get_cap_camiones())                ; //se setea capacidad disponible
  Cliente* deposito = instancia->get_cliente(instancia->get_cant_clientes()) ; //se identifica el deposito

  Cliente* i = deposito ; //cliente i, inicialmente el deposito
  Cliente* j            ; //cliente j
  float costo           ; //costo del segmento
  float tiempo          ; //tiempo del segmento
  int p                 ; //periodo de tiempo
  float c_inicio = 0    ; //costo al inicio del segmento
  float ts_inicio = 0   ; //tasa al inicio del segmento
  int d_inicio = 0      ; //demanda al inicio del segmento

  //if (debug) this->imprimir_secuencia(secuencia) ;

  while (ruta->get_capacidad_restante() > 0 & t_inicio < h_fin2 & secuencia.size() > 0){
    j = instancia->get_cliente(secuencia.at(0))             ; //cliente j, siempre el primero en secuencia

    p = t_inicio / instancia->get_frec_salidas()            ; //se obtiene el periodo de tiempo
    tiempo = i->get_tiempo_hasta(j->get_id_cliente(), p)    ; //tiempo hasta el viaje
    costo  = i->get_costo_hasta(j->get_id_cliente(), p)     ; //costo hasta el viaje

    p = (t_inicio + tiempo) / instancia->get_frec_salidas() ; //se obtiene el periodo de tiempo
    tiempo = tiempo + j->get_tiempo_aten(p)                 ; //tiempo hasta la atencion
    costo = costo + j->get_costo_aten(p)                    ; //costo hasta la atencion

    //si al ultimo cliente no permite llegar al deposito antes del fin del horizonte
    if ((t_inicio + tiempo + j->get_tiempo_hasta(deposito->get_id_cliente(), p)) > h_fin2){   
      break ; //se deja para la siguiente ruta y se retorna deposito
    }                                 

    segmento = new Segmento(i, j)    ; //se crea segmento de ruta
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
    segmento->set_demanda_t(d_inicio) ; //se setea la demanda cubierta al final del segmento 
    
    ruta->set_aporte_f1(ruta->get_aporte_f1() + costo)                     ; //se setea el aporte de la ruta a f1
    ruta->set_aporte_f2(ruta->get_aporte_f2() + j->get_tasas_fallo(p))     ; //se setea el aporte de la ruta a f2
    ruta->set_tiempo_restante(h_fin2 - t_inicio)                           ; //se setea el tiempo disponible de la ruta
    ruta->set_capacidad_restante(instancia->get_cap_camiones() - d_inicio) ; //se setea la capacidad disponible del camion
    
    ruta->agregar_segmento(segmento)     ; //se agrega el segmento a la ruta
    secuencia.erase(secuencia.begin()+0) ; //se elimina el id del vector de id
    i = j                                ; //el cliente j es i en el siguiente segmento

    //if (debug) this->imprimir_secuencia(secuencia) ;
  }

  j = deposito                  ; //cliente j, finalmente el deposito
  segmento = new Segmento(i, j) ; //se crea segmento de ruta

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

  //if (debug) cout << endl ;

  return secuencia        ;
}
*/
