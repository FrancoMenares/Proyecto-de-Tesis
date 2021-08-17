
#include "ñ-AjusteHora.h"


//--------------- recalcula parametros de la ruta ---------------
bool AjusteHora::evaluar_ruta(Instancia* instancia, Ruta* ruta, float hora_inicio){
  float h_fin = instancia->get_termino()  ; //termino de horizonte de planificacion
  int cap = instancia->get_cap_camiones() ; //capcidad de los camiones
  float tiempo = hora_inicio              ; //tiempo transcurrido
  float costo = 0                         ; //costo acumulado
  float tasa = 0                          ; //tasa acumulada
  int demanda = 0                         ; //demanda atendida
  int p                                   ; //periodo de tiempo

  ruta->set_tiempo_inicio(tiempo)                            ; //se setea tiempo de inicio de la ruta
  ruta->set_tiempo_restante(instancia->get_termino()-tiempo) ; //se setea el tiempo restante de la ruta
  ruta->set_aporte_f1(0)                                     ; //se setea aporte de la ruta a f1
  ruta->set_aporte_f2(0)                                     ; //se setea aporte de la ruta a f2

  for (Segmento* i: ruta->get_segmentos()){
    i->set_tiempo_i(tiempo) ; //se setea tiempo de inicio del segmento
    i->set_costo_i(costo)   ; //se setea costo de inicio del segmento
    i->set_tasa_i(tasa)     ; //se setea tasa al inicio del segmento

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

//--------------- cambia la hora de inicio de una ruta ---------------
void AjusteHora::ajustar_hora_ruta(Individuo* individuo, Instancia* instancia){
  int cambio = rand()%(individuo->get_rutas().size())                           ; //se selecciona una ruta aleatoria
  Ruta* ruta = individuo->get_ruta(cambio)                                      ; //se identifica la ruta a modificar
  int h_inicio = instancia->get_inicio()*100                                    ; //limite inferior de la nueva hora
  int h_fin = (ruta->get_tiempo_inicio() + ruta->get_tiempo_restante()*1.1)*100 ; //limite superior de la nueva hora

  bool ajuste = false ; //bandera para detectar un cambio factible

  while (ajuste == false){
    float hora_inicio = (float)(rand()%(h_fin - h_inicio + 1) + h_inicio)/100 ; //hora de inicio aleatoria entre los limites
    ajuste = this->evaluar_ruta(instancia, ruta, hora_inicio)                 ; //se ajusta ruta segun la nueva hora
  }
  individuo->actualizar_funciones() ; //se actualizan las funciones de evaluacion
}










