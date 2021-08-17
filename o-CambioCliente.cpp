
#include "o-CambioCliente.h"


//--------------- actualizacion de la ruta ---------------
bool CambioCliente::actualizar_ruta_desde(Instancia* instancia, Ruta* ruta, int desde){
  Segmento* i = ruta->get_segmento(desde) ;
  float h_fin = instancia->get_termino()  ; //termino de horizonte de planificacion
  int cap = instancia->get_cap_camiones() ; //capcidad de los camiones
  float tiempo = i->get_tiempo_i()        ; //tiempo transcurrido
  float costo = i->get_costo_i()          ; //costo acumulado
  float tasa = i->get_tasa_i()            ; //tasa acumulada
  int demanda = i->get_demanda_t()-1      ; //demanda atendida
  int p                                   ; //periodo de tiempo

  for (int j=desde; j<ruta->get_segmentos().size(); j++){
    i = ruta->get_segmento(j) ; //se identifica el segmento a actualizar
    i->set_tiempo_i(tiempo)   ; //se setea tiempo de inicio del segmento
    i->set_costo_i(costo)     ; //se setea costo de inicio del segmento
    i->set_tasa_i(tasa)       ; //se setea tasa al inicio del segmento

    p = tiempo / instancia->get_frec_salidas()                                                      ; //se identifica periodo de tiempo
    tiempo = tiempo + i->get_cliente_i()->get_tiempo_hasta(i->get_cliente_j()->get_id_cliente(), p) ; //se suma el tiempo de viaje
    costo = costo + i->get_cliente_i()->get_costo_hasta(i->get_cliente_j()->get_id_cliente(), p)    ; //se suma el costo de viaje

    if (i->get_cliente_j() != instancia->get_cliente(instancia->get_cant_clientes())){
      p = tiempo / instancia->get_frec_salidas()               ; //se identifica periodo de tiempo
      tiempo = tiempo + i->get_cliente_j()->get_tiempo_aten(p) ; //se suma el tiempo de atencion
      costo = costo + i->get_cliente_j()->get_costo_aten(p)    ; //se suma el costo de atencion
      tasa = tasa + i->get_cliente_j()->get_tasas_fallo(p)     ; //se suma la tasa de fallo
      demanda++                                                ; //se suma la demanda
    }
    if (tiempo > h_fin){ return false ;} //si se supera el horizonte de panificacion de detiene el calculo

    i->set_tiempo_t(tiempo)   ; //se setea el tiempo de termino del segmento
    i->set_costo_t(costo)     ; //se setea el costo de termino del segmento
    i->set_tasa_t(tasa)       ; //se setea la tasa de termino del segmento
    i->set_demanda_t(demanda) ; //se setea la demanda al termino del segmento
  }

  ruta->set_aporte_f1(costo)                  ; //se setea el aporte de la ruta a f1
  ruta->set_aporte_f2(tasa)                   ; //se setea el aporte de la ruta a f2
  ruta->set_tiempo_termino(tiempo)            ; //se setea el tiempo de termino de la ruta
  ruta->set_tiempo_restante(h_fin - tiempo)   ; //se setea el tiempo restante de la ruta
  ruta->set_capacidad_restante(cap - demanda) ; //se setea la capacidad disponible del camion

  return true ;
}


//--------------- actualizacion de la ruta ---------------
bool CambioCliente::evaluar_ruta_desde(Instancia* instancia, Ruta* ruta, int desde){
  Segmento* i = ruta->get_segmento(desde) ;
  float h_fin = instancia->get_termino()  ; //termino de horizonte de planificacion
  float tiempo = i->get_tiempo_i()        ; //tiempo transcurrido
  int p                                   ; //periodo de tiempo

  for (int j=desde; j<ruta->get_segmentos().size(); j++){
    i = ruta->get_segmento(j) ; //se identifica el segmento a actualizar

    p = tiempo / instancia->get_frec_salidas()                                                      ; //se identifica periodo de tiempo
    tiempo = tiempo + i->get_cliente_i()->get_tiempo_hasta(i->get_cliente_j()->get_id_cliente(), p) ; //se suma el tiempo de viaje

    if (i->get_cliente_j() != instancia->get_cliente(instancia->get_cant_clientes())){
      p = tiempo / instancia->get_frec_salidas()               ; //se identifica periodo de tiempo
      tiempo = tiempo + i->get_cliente_j()->get_tiempo_aten(p) ; //se suma el tiempo de atencion
    }
    if (tiempo > h_fin){ return false ;} //si se supera el horizonte de panificacion de detiene el calculo
  }
  return true ;
}


//--------------- agregar nueva ruta a la solucion ---------------
Ruta* CambioCliente::agregar_ruta_nueva(Instancia* instancia, Cliente* cliente, int id){
  Ruta* ruta = new Ruta(id) ; //se crea un nuevo objeto de tipo ruta

  Segmento* aux1 = new Segmento(instancia->get_cliente(instancia->get_cant_clientes()), cliente) ; //segmento deposito-cliente
  Segmento* aux2 = new Segmento(cliente, instancia->get_cliente(instancia->get_cant_clientes())) ; //segmento cliente-deposito

  aux1->set_demanda_t(1)       ; //se setea la demanda del cliente
  ruta->agregar_segmento(aux1) ; //se agrega segmento 1 a la ruta vacia
  ruta->agregar_segmento(aux2) ; //se agrega segmento 2 a la ruta
  return ruta                  ; //se retorna la nueva ruta
} 


//--------------- cambio nodo aleatorio ---------------
void CambioCliente::cambiar_cliente_aleatorio(Individuo* individuo, Instancia* instancia){
  
  // ================================ fase de extraccion del cliente ================================ 
  int elegir_r = rand()%(individuo->get_rutas().size())   ; //se escoge ruta para extraer cliente
  Ruta* ruta = individuo->get_ruta(elegir_r)              ; //se identifica la ruta
  int elegir_s = rand()%(ruta->get_segmentos().size()-1)  ; //se escoge segmento para extraer cliente j
  Segmento* aux = ruta->get_segmento(elegir_s+1)          ; //se identifica el segmento siguiente
  //individuo->imprimir_individuo();
  
  ruta->get_segmento(elegir_s)->set_cliente_j(aux->get_cliente_j()) ; //se actualiza el cliente j en segmento elegido
  ruta->eliminar_segmento(elegir_s+1)                               ; //se elimina de la ruta el segmento siguiente

  if (ruta->get_segmentos().size() == 1){                    //si la ruta queda sin cliente (segmento deposito-deposito)
    delete ruta->get_segmento(0)                           ; //se elimina el segmento
    delete ruta                                            ; //se elimina la ruta
    individuo->eliminar_ruta(elegir_r)                     ;
  } else {
    this->actualizar_ruta_desde(instancia, ruta, elegir_s) ; //se actualizan los parametros del recorrido
  }
  individuo->actualizar_funciones() ; //se actualizan las funciones de evaluacion
  //individuo->imprimir_individuo()   ;

  int elegir_r2 = elegir_r ;
  int elegir_s2 = elegir_s ;


  // ================================ fase de insercion del cliente ================================ 
  int cant_rutas                                                        ; //rutas donde se pueden insertar el cliente
  if (individuo->get_rutas().size() == instancia->get_cant_camiones()){   //si no quedan camiones disponibles
    cant_rutas = individuo->get_rutas().size()                          ; //se escoge entre una ruta existente
  } else {                                                                //si quedan camiones disponibles
    cant_rutas = individuo->get_rutas().size()+1                        ; //se puede agregar una nueva ruta
  }

  bool bandera = false             ; //bandera de insercion factible
  while (bandera == false){
    elegir_r = rand()%(cant_rutas) ; //se escoge ruta para agregar el cliente

    if (elegir_r == individuo->get_rutas().size()){                                //si se elige una agregar una ruta nueva
      ruta = this->agregar_ruta_nueva(instancia, aux->get_cliente_i(), elegir_r) ; //se crea la nueva ruta

      int h_ini = instancia->get_inicio()*100  ; //hora minima a la que puede iniciar la ruta
      int h_fin = instancia->get_termino()*100 ; //hora maxima a la que puede iniciar la ruta
      float hora_inicio                        ; //hora de inicio de la ruta

      while (bandera == false){                                         //mientras no se encuentre una hora factible
        h_fin = h_fin - hora_inicio*100                               ; //se actualiza la hora maxima de termino
        hora_inicio = (float)(rand()%(h_fin - h_ini + 1) + h_ini)/100 ; //se obtiene una hora de inicio aleatoria
        ruta->set_tiempo_inicio(hora_inicio)                          ; //se setea la hora de inicio de la ruta
        ruta->get_segmento(0)->set_tiempo_i(hora_inicio)              ; //se setea la hora de inicio del primer segmento
        bandera = this->actualizar_ruta_desde(instancia, ruta, 0)     ; //se actualizan parametros de la ruta
      }
      individuo->agregar_ruta(ruta)                                   ; //se agrega la ruta a la solucion

    } else {
      ruta = individuo->get_ruta(elegir_r)                 ; //se identifica la ruta
      if (ruta->get_capacidad_restante() > 0){             ; //si la ruta tiene capacidad de atencion
        elegir_s = rand()%(ruta->get_segmentos().size()-1) ; //se escoge segmento para donde insertar al cliente j

        if (elegir_r2 == elegir_r && elegir_s2 == elegir_s){
          continue ;
        }

        ruta->insertar_segmento(elegir_s+1, aux)           ; //se inserta el segmento en la posicion siguiente de la ruta 

        ruta->get_segmento(elegir_s)->set_cliente_j(aux->get_cliente_i())   ; //se ajusta el segmento anterior
        aux->set_cliente_j(ruta->get_segmento(elegir_s+2)->get_cliente_i()) ; //se ajusta el segmento siguiente
        bandera = this->evaluar_ruta_desde(instancia, ruta, elegir_s)       ; //se evalua si el movimiento es factible

        if (bandera == false){                                                                           //si el movimiento no es factible
          ruta->eliminar_segmento(elegir_s+1)                                                          ; //se elimina segmento agregado
          ruta->get_segmento(elegir_s)->set_cliente_j(ruta->get_segmento(elegir_s+1)->get_cliente_i()) ; //se ajusta secmento anterior
        } else {                                                                                         // si el movimiento es factible 
          this->actualizar_ruta_desde(instancia, ruta, elegir_s)                                       ; //se actualizan parametros del recorrido
        }
      }
    }
  }
  individuo->actualizar_funciones() ; //se actualizan las funciones de evaluacion
  //individuo->imprimir_individuo()   ;
}