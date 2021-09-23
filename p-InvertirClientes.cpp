
#include "p-InvertirClientes.h"


//--------------- actualizacion de la ruta ---------------
bool InvertirClientes::actualizar_ruta_desde(Instancia* instancia, Ruta* ruta, int desde){
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


//--------------- evaluacion de la ruta ---------------
bool InvertirClientes::evaluar_ruta_desde(Instancia* instancia, Ruta* ruta, int desde){
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
  return true ; //retorna verdadero si el cambio es factible
}


//--------------- invertir los clientes de un segmento ---------------
void InvertirClientes::invertir_clientes_segmento(Individuo* individuo, Instancia* instancia){
  bool bandera = false ;

  for (int i=0; i<5; i++){
    int elegir_r = rand()%(individuo->get_rutas().size()) ; //se escoge ruta para extraer cliente
    Ruta* ruta = individuo->get_ruta(elegir_r)            ; //se identifica la ruta

    if (ruta->get_segmentos().size()>2){
      int elegir_s = rand()%(ruta->get_segmentos().size()-2) + 1 ; //se elige segmento que no incluye el deposito
      Segmento* aux = ruta->get_segmento(elegir_s)               ; //se identifica el segmento siguiente

      individuo->set_f1(individuo->get_f1() - ruta->get_aporte_f1()) ; //se actualiza f1
      individuo->set_f2(individuo->get_f2() - ruta->get_aporte_f2()) ; //se actualiza f2

      ruta->get_segmento(elegir_s-1)->set_cliente_j(aux->get_cliente_j()) ; //se actualiza en cliente j del segmento anterior
      ruta->get_segmento(elegir_s+1)->set_cliente_i(aux->get_cliente_i()) ; //se actualiza en cliente i del segmento siguiente
      aux->set_cliente_i(ruta->get_segmento(elegir_s-1)->get_cliente_j()) ; //se actualiza en cliente i del segmento elegido
      aux->set_cliente_j(ruta->get_segmento(elegir_s+1)->get_cliente_i()) ; //se actualiza en cliente j del segmento elegido

      bandera = this->evaluar_ruta_desde(instancia, ruta, elegir_s-1) ; //se evalua si el movimiento es factible

      if (!bandera){
        ruta->get_segmento(elegir_s-1)->set_cliente_j(aux->get_cliente_j()) ; //se actualiza en cliente j del segmento anterior 
        ruta->get_segmento(elegir_s+1)->set_cliente_i(aux->get_cliente_i()) ; //se actualiza en cliente i del segmento siguiente 
        aux->set_cliente_i(ruta->get_segmento(elegir_s-1)->get_cliente_j()) ; //se actualiza en cliente i del segmento elegido
        aux->set_cliente_j(ruta->get_segmento(elegir_s+1)->get_cliente_i()) ; //se actualiza en cliente j del segmento elegido
        
        individuo->set_f1(individuo->get_f1() + ruta->get_aporte_f1()) ; //se actualiza f1
        individuo->set_f2(individuo->get_f2() + ruta->get_aporte_f2()) ; //se actualiza f2

        continue ;
      }
      this->actualizar_ruta_desde(instancia, ruta, elegir_s-1) ; //si efectua el movimiento
        
      individuo->set_f1(individuo->get_f1() + ruta->get_aporte_f1()) ; //se actualiza f1
      individuo->set_f2(individuo->get_f2() + ruta->get_aporte_f2()) ; //se actualiza f2

      break ;
    }
  }
}

