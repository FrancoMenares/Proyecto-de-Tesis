
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


//--------------- evaluacion de la ruta ---------------
bool CambioCliente::evaluar_ruta_desde(Instancia* instancia, Ruta* ruta, int desde){
  Segmento* i = ruta->get_segmento(desde) ;
  float h_fin = instancia->get_termino()  ; //termino de horizonte de planificacion
  float tiempo = i->get_tiempo_i()        ; //tiempo transcurrido

  int demanda = i->get_demanda_t()-1 ;

  int p                                   ; //periodo de tiempo

  for (int j=desde; j<ruta->get_segmentos().size(); j++){
    i = ruta->get_segmento(j) ; //se identifica el segmento a actualizar

    p = tiempo / instancia->get_frec_salidas()                                                      ; //se identifica periodo de tiempo
    tiempo = tiempo + i->get_cliente_i()->get_tiempo_hasta(i->get_cliente_j()->get_id_cliente(), p) ; //se suma el tiempo de viaje

    if (i->get_cliente_j() != instancia->get_cliente(instancia->get_cant_clientes())){
      p = tiempo / instancia->get_frec_salidas()               ; //se identifica periodo de tiempo
      tiempo = tiempo + i->get_cliente_j()->get_tiempo_aten(p) ; //se suma el tiempo de atencion

      demanda++ ;
    }

    if (tiempo > h_fin){ return false ;} //si se supera el horizonte de panificacion de detiene el calculo

    if (demanda > instancia->get_cap_camiones() ){ return false ;}
  }
  return true ; //retorna verdadero si el cambio es factible
}


//---------------crearcion de una nueva ruta ---------------
Ruta* CambioCliente::crear_nueva_ruta(Instancia* instancia, Segmento* aux1, Segmento* aux2, int id){
  Ruta* ruta = new Ruta(id) ; //se crea una nueva ruta

  aux1->set_cliente_i(instancia->get_cliente(instancia->get_cant_clientes())) ; //se identifica el deposito
  aux1->set_cliente_j(aux2->get_cliente_i())                                  ; //se identifica el cliente j
  aux2->set_cliente_j(instancia->get_cliente(instancia->get_cant_clientes())) ; //se identifica el deposito

  ruta->agregar_segmento(aux1) ; //se agrega segmento 1 a la nueva ruta
  ruta->agregar_segmento(aux2) ; //se agrega segmento 2 a la nueva ruta

  int h_inicio = instancia->get_inicio()*100 ; //limite inferior de la nueva hora
  int h_fin = instancia->get_termino()*100   ; //limite superior de la nueva hora
  
  aux1->set_costo_i(0)   ; //se setea el costo de inicio en el primer segmento
  aux1->set_tasa_i(0)    ; //se setea la tasa de inicio en el primer segmento
  aux1->set_demanda_t(1) ; //de setea la demananda de termino en el primer segmento

  bool bandera = false   ; //bandera de ruta factible
  while (!bandera){
    float hora_inicio = (float)(rand()%(h_fin - h_inicio + 1) + h_inicio)/100 ; //hora de salida aleatoria 
    aux1->set_tiempo_i(hora_inicio)                                           ; //se setea la hora de inicio en el segmento 1
    ruta->set_tiempo_inicio(hora_inicio)                                      ; //se setea la hora de inicio en la ruta

    bandera = this->actualizar_ruta_desde(instancia, ruta, 0)                 ; //se actualizan los costos de la ruta

    h_fin = hora_inicio*100                                                   ; //se limita la nueva hora de salida
  }
  
  return ruta ; //se retorna la nueva ruta
}


//--------------- cambio nodo aleatorio ---------------
void CambioCliente::cambiar_cliente_aleatorio(Individuo* individuo, Instancia* instancia){

  // ================================ fase de extración del cliente ================================ 
  int elegir_r = rand()%(individuo->get_rutas().size())  ; //se escoge ruta para extraer cliente
  Ruta* ruta = individuo->get_ruta(elegir_r)             ; //se identifica la ruta
  int elegir_s = rand()%(ruta->get_segmentos().size()-1) ; //se escoge segmento para extraer cliente j

  Segmento* aux1 = ruta->get_segmento(elegir_s+1) ; //se identifica el segmento siguiente
  Segmento* aux2 = new Segmento(*aux1)            ; //se respalda el segmento siguiente
  int aux3 = elegir_r                             ; //se respalda la ruta del segmento elegido
  int aux4 = elegir_s                             ; //se respalda la posicion del segmento elegido
  int aux5 = individuo->get_rutas().size()        ; //se respalda cuantas rutas existian

  ruta->eliminar_segmento(elegir_s+1)                                ; //se elimina el segmento siguiente de la ruta
  ruta->get_segmento(elegir_s)->set_cliente_j(aux1->get_cliente_j()) ; //se actualiza j en el segmento elegido
  
  individuo->set_f1(individuo->get_f1() - ruta->get_aporte_f1()) ; //se actualiza f1 del individuo
  individuo->set_f2(individuo->get_f2() - ruta->get_aporte_f2()) ; //se actualiza f2 del individuo
  
  bool bandera = false                       ; //bandera para detectar un cambio factible
  int h_inicio = instancia->get_inicio()*100 ; //limite inferior de la nueva hora
  int h_fin                                  ; //limite superior de la nueva hora
  float hora_inicio                          ; //hora de inicio aleatoria entre los limites

  if (ruta->get_segmentos().size() == 1){   //si la ruta solo le queda un segmento (no hay clientes)
    int id = ruta->get_id()               ; //se guarda el id de la ruta
    delete ruta                           ; //se destruye la ruta
    individuo->eliminar_ruta(elegir_r)    ; //se elimina la ruta del individuo

    for(int i=id; i<individuo->get_rutas().size(); i++){
      individuo->get_ruta(i)->set_id(i)   ; //se actualiza el id de las rutas siguientes
    }

  } else {
    for (int i=0; i<10; i++){
      bandera = this->actualizar_ruta_desde(instancia, ruta, elegir_s)      ; //se actualiza la ruta
      
      if (bandera){                                                           //si se encuentra rura factible
        break                                                               ;
      } else {                                                                //si la actualizacion no es factible
        elegir_s = 0                                                        ; //se reevalua desde el inicio a otra hora
        h_fin = ruta->get_tiempo_inicio()*100                               ; //limite superior de la nueva hora
        hora_inicio = (float)(rand()%(h_fin - h_inicio + 1) + h_inicio)/100 ; //se escoge una hora previa a la anterior
        ruta->set_tiempo_inicio(hora_inicio)                                ; //se setea en el primer segmento
        ruta->get_segmento(elegir_s)->set_tiempo_i(hora_inicio)             ; //se setea en la ruta
      }
    }

    if (!bandera){                            //si no se encuentra ruta factible se restaura la original
      ruta = individuo->get_ruta(aux3)      ; //se identifica la ruta a resturar
      ruta->insertar_segmento(aux4+1, aux2) ; //se inserta el segmento antes eliminado

      ruta->get_segmento(aux4)->set_cliente_j(aux2->get_cliente_i()) ; //se restaura secuencia

      if (aux2->get_cliente_j() == instancia->get_cliente(instancia->get_cant_clientes())){
        ruta->get_segmento(aux4)->set_demanda_t(aux2->get_demanda_t()) ; //se ajusta demanda acumulada
      }
      
      this->actualizar_ruta_desde(instancia, ruta, aux4)             ; //se realiza el cambio

      individuo->set_f1(individuo->get_f1() + ruta->get_aporte_f1()) ; //se actualiza f1 del individuo
      individuo->set_f2(individuo->get_f2() + ruta->get_aporte_f2()) ; //se actualiza f2 del individuo

      return ;
    }

    individuo->set_f1(individuo->get_f1() + ruta->get_aporte_f1()) ; //se actualiza f1 del individuo
    individuo->set_f2(individuo->get_f2() + ruta->get_aporte_f2()) ; //se actualiza f2 del individuo
  }
  
  // ================================ fase de insercion del cliente ================================ 
  
  int cant_rutas                                                        ; //rutas donde se pueden insertar el cliente
  if (individuo->get_rutas().size() == instancia->get_cant_camiones()){   //si no quedan camiones disponibles
    cant_rutas = individuo->get_rutas().size()                          ; //se escoge entre una ruta existente
  } else {                                                                //si quedan camiones disponibles
    cant_rutas = individuo->get_rutas().size()+1                        ; //se puede agregar una nueva ruta
  }
  bandera = false                                                       ; //bandera de insercion factible 

  for (int i=0; i<5; i++){
    elegir_r = rand()%(cant_rutas)                                   ; //se escoge ruta para agregar el cliente

    if (elegir_r == individuo->get_rutas().size()){                    //si se elige agregar una ruta nueva
      ruta = this->crear_nueva_ruta(instancia, aux1, aux2, elegir_r) ; //se crea una ruta factible
      individuo->agregar_ruta(ruta)                                  ; //se agrega la ruta a la solucion

      individuo->set_f1(individuo->get_f1() + ruta->get_aporte_f1()) ; //se actualiza f1 del individuo
      individuo->set_f2(individuo->get_f2() + ruta->get_aporte_f2()) ; //se actualiza f2 del individuo

      bandera = true ; //se creo una ruta factible
      break          ;


    } else {
      ruta = individuo->get_ruta(elegir_r)               ; //se identifica la ruta
      elegir_s = rand()%(ruta->get_segmentos().size()-1) ; //se escoge segmento para insertar cliente j

      ruta->insertar_segmento(elegir_s+1, aux1)          ; //se agrega segmento a la ruta

      aux1->set_cliente_j(ruta->get_segmento(elegir_s)->get_cliente_j()) ; //se identifica cliente j
      ruta->get_segmento(elegir_s)->set_cliente_j(aux1->get_cliente_i()) ; //se identifica cliente j anterior
      
      bandera = this->evaluar_ruta_desde(instancia, ruta, elegir_s)      ; //se evalua factibilidad del cambio

      if (bandera){                                                      //si el cambio es factible
        individuo->set_f1(individuo->get_f1() - ruta->get_aporte_f1()) ; //se actualiza f1 del individuo
        individuo->set_f2(individuo->get_f2() - ruta->get_aporte_f2()) ; //se actualiza f2 del individuo

        this->actualizar_ruta_desde(instancia, ruta, elegir_s)         ; //se realiza el cambio

        individuo->set_f1(individuo->get_f1() + ruta->get_aporte_f1()) ; //se actualiza f1 del individuo
        individuo->set_f2(individuo->get_f2() + ruta->get_aporte_f2()) ; //se actualiza f2 del individuo

        delete aux2 ; //se elimina el segmento respaldado
        break       ;
      }

      ruta->eliminar_segmento(elegir_s+1)                                ; //se elimina segmento insertado
      ruta->get_segmento(elegir_s)->set_cliente_j(aux1->get_cliente_j()) ; //se restaura la condicion de la ruta
    }
  }


  if (!bandera){
    if (individuo->get_rutas().size() < aux5){ 
      ruta = this->crear_nueva_ruta(instancia, aux1, aux2, aux5-1) ; //se crea una ruta factible
      individuo->agregar_ruta(ruta)                                ; //se agrega la ruta a la solucion

      individuo->set_f1(individuo->get_f1() + ruta->get_aporte_f1()) ; //se actualiza f1 del individuo
      individuo->set_f2(individuo->get_f2() + ruta->get_aporte_f2()) ; //se actualiza f2 del individuo


    } else {
      ruta = individuo->get_ruta(aux3)      ; //se identifica la ruta a resturar
      ruta->insertar_segmento(aux4+1, aux2) ; //se inserta el segmento antes eliminado

      ruta->get_segmento(aux4)->set_cliente_j(aux2->get_cliente_i()) ; //se restaura secuencia

      if (aux2->get_cliente_j() == instancia->get_cliente(instancia->get_cant_clientes())){
        ruta->get_segmento(aux4)->set_demanda_t(aux2->get_demanda_t()) ; //se ajusta demanda acumulada
      }

      individuo->set_f1(individuo->get_f1() - ruta->get_aporte_f1()) ; //se actualiza f1 del individuo
      individuo->set_f2(individuo->get_f2() - ruta->get_aporte_f2()) ; //se actualiza f2 del individuo

      this->actualizar_ruta_desde(instancia, ruta, aux4)             ; //se realiza el cambio

      individuo->set_f1(individuo->get_f1() + ruta->get_aporte_f1()) ; //se actualiza f1 del individuo
      individuo->set_f2(individuo->get_f2() + ruta->get_aporte_f2()) ; //se actualiza f2 del individuo
    }
  }
}

