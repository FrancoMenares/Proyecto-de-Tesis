
#include "q-OX.h"



//--------------- extrae la secuencia de las rutas de un individuo ---------------
vector <int> OX::extraer_secuencia(Individuo* individuo){
  vector <int> secuencia ;
  for (Ruta* i: individuo->get_rutas()){
    for (Segmento* j: i->get_segmentos()){
      if (j->get_cliente_j() != individuo->get_ruta(0)->get_segmento(0)->get_cliente_i()){
        secuencia.push_back(j->get_cliente_j()->get_id_cliente()) ;
      }
    }
  }
  return secuencia ;
}


//--------------- extraer herencia x ---------------
vector <int> OX::extraer_herencia_x(vector <int> padre_x, int corte1, int corte2){
  vector <int> herencia_x               ; //se crea un vector para guardar la herencia del primer padre
  
  for (int i=corte1; i<=corte2; i++){
    herencia_x.push_back(padre_x.at(i)) ; //se guarda la herencia en el vector
  }
  
  return herencia_x                     ; //se retorna el vector con la herencia
}


//--------------- extraer herencia y ---------------
vector <int> OX::extraer_herencia_y(vector <int> padre_y, vector <int> herencia_x, int corte2){
  vector <int> herencia_y ; //se crea un vector para guardar la herencia del segundo padre
  bool bandera            ; //bandera alerta de un cliente que no se encuentra en herencia_x
  int i = corte2 + 1      ; //se recorre el padre_y desde despues del segundo corte
  
  while (true){          
    bandera = true             ; //iniciamente el cliente no se encuentra en herencia_x
    for (int j: herencia_x){    
      if (padre_y.at(i) == j){   //si el cliente de padre_y esta en herencia_x
        bandera = false        ; //se activa la bandera
        break                  ;
      }
    }
    if (bandera){                           //si la bandera aun es true
      herencia_y.push_back(padre_y.at(i)) ; //se agrega el cliente a la herencia_y
    }

    if (i == corte2){   //si se llega al segundo corte
      break           ; //se detiene el ciclo
    }

    i++                       ; //se declara la proxima iteracion
    if (i == padre_y.size()){   //si de llega al final del vector 
      i = 0                   ; //se va al inicio del vector
    }
  }
  return herencia_y ; //se retorna el vector con la herencia
}


//--------------- crear hijo a partir de la herencia de los padres ---------------
vector <int> OX::crear_hijo(vector <int> herencia_x, vector <int> herencia_y, int corte1, int corte2){
  vector <int> hijo                                         ; //vector para guardar la secuencia del hijo
  int cant_clientes = herencia_x.size() + herencia_y.size() ; //cantidad de clientes
  int x = 0                                                 ; //contador para los genes x
  int y1 = 0                                                ; //contador para los genes y despues del corte
  int y2 = herencia_y.size() - 1                            ; //contador para los genes y antes del corte
  
  for (int i=0; i<cant_clientes; i++){
    if (i>=corte1 && i<=corte2){         //si el gen pertenece a x
      hijo.push_back(herencia_x.at(x)) ; //se agrega el gen a la secuencia del hijo
      x++                              ; //se aumenta el contador
    } else {
      if (i<corte1){                                   //si el gen pertenece a y, pero antes del corte
        hijo.insert(hijo.begin() ,herencia_y.at(y2)) ; //se agrega el gen a la secuencia del hijo 
        y2--                                         ; //se decrementa el contador
      } else if (i>corte2){                            //si el gen pertenece a y, pero despues del corte
        hijo.push_back(herencia_y.at(y1))            ; //se agrega el gen a la secuencia del hijo
        y1++                                         ; //se incrementa el contador
      }
    }
  }
  return hijo ; //se retorna la secuencia del hijo
}


//--------------- evalua si la secuencia permite crear rutas factibles ---------------
bool OX::evaluar_secuencia(Instancia* instancia, vector <int> secuencia, float hora_inicio, int desde, int hasta){
  float h_fin = instancia->get_termino()  ; //termino de horizonte de planificacion
  float tiempo = hora_inicio              ; //tiempo transcurrido
  int p                                   ; //periodo de tiempo

  Cliente* i = instancia->get_cliente(instancia->get_cant_clientes()) ; //cliente i del segmento, inicialmente el deposito
  Cliente* j                                                          ; //cliente j del segmento

  for (int h=desde; h<hasta; h++){
    j = instancia->get_cliente(secuencia.at(h)) ; //se identifica cliente j
    
    p = tiempo / instancia->get_frec_salidas()                    ; //se identifica periodo de tiempo
    tiempo = tiempo + i->get_tiempo_hasta(j->get_id_cliente(), p) ; //se suma tiempo de viaje

    if (j != instancia->get_cliente(instancia->get_cant_clientes())){
      p = tiempo / instancia->get_frec_salidas() ; //se identifica periodo de tiempo
      tiempo = tiempo + j->get_tiempo_aten(p)    ; //se suma el tiempo de atencion
    }
    
    if (tiempo > h_fin){ return false ;} //si se supera el horizonte de panificacion la ruta es infactible

    i = j ; //se actualiza el cliente i
  }

  j = instancia->get_cliente(instancia->get_cant_clientes())    ; //se retorna al deposito

  p = tiempo / instancia->get_frec_salidas()                    ; //se identifica periodo de tiempo
  tiempo = tiempo + i->get_tiempo_hasta(j->get_id_cliente(), p) ; //se suma tiempo de viaje

  if (tiempo > h_fin){ return false ;} //si se supera el horizonte de panificacion la ruta es infactible

  return true ; //la ruta es factible
}


//--------------- arma ruta a partir de una secuencia factble ---------------
Ruta* OX::armar_ruta(Instancia* instancia, vector <int> secuencia, float hora_inicio, int id, int desde, int hasta){
  float h_fin = instancia->get_termino()  ; //termino de horizonte de planificacion
  int cap = instancia->get_cap_camiones() ; //capcidad de los camiones
  float tiempo = hora_inicio              ; //tiempo transcurrido
  float costo = 0                         ; //costo acumulado
  float tasa = 0                          ; //tasa acumulada
  int demanda = 0                         ; //demanda acumulada 
  int p                                   ; //periodo de tiempo

  Ruta* ruta = new Ruta(id)       ; // se crea una nueva ruta 
  ruta->set_tiempo_inicio(tiempo) ; //se setea tiempo de inicio de la ruta

  Cliente* i = instancia->get_cliente(instancia->get_cant_clientes()) ; //cliente i del segmento, inicialmente el deposito
  Cliente* j                                                          ; //cliente j del segmento

  for (int h=desde; h<hasta; h++){
    j = instancia->get_cliente(secuencia.at(h)) ; //se identifica cliente j
    Segmento* s = new Segmento(i, j)            ; //se crea el nuevo segmento
    
    s->set_tiempo_i(tiempo) ; //se setea tiempo de inicio del segmento
    s->set_costo_i(costo)   ; //se setea costo de inicio del segmento
    s->set_tasa_i(tasa)     ; //se setea tasa al inicio del segmento

    p = tiempo / instancia->get_frec_salidas()                    ; //se identifica el periodo
    tiempo = tiempo + i->get_tiempo_hasta(j->get_id_cliente(), p) ; //se suma tiempo de viaje
    costo = costo + i->get_costo_hasta(j->get_id_cliente(), p)    ; //se suma costo de viaje

    if (j != instancia->get_cliente(instancia->get_cant_clientes())){
      p = tiempo / instancia->get_frec_salidas() ; //se identifica periodo de tiempo
      tiempo = tiempo + j->get_tiempo_aten(p)    ; //se suma el tiempo de atencion
      costo = costo + j->get_costo_aten(p)       ; //se suma el costo de atencion
      tasa = tasa + j->get_tasas_fallo(p)        ; //se suma la sa de fallo
      demanda++                                  ; //se suma la demanda
    }
    
    s->set_tiempo_t(tiempo)   ; //se setea el tiempo al final del segmento
    s->set_costo_t(costo)     ; //se setea el costo al final del segmento
    s->set_tasa_t(tasa)       ; //se setea la tasa de fallo al final del segmento  
    s->set_demanda_t(demanda) ; //se setea la demanda cubierta al final del segmento 

    ruta->agregar_segmento(s) ; //se agrega el segmento a la ruta

    i = j ; //se actualiza el cliente i
  }

  j = instancia->get_cliente(instancia->get_cant_clientes()) ; //se retorna al deposito
  Segmento* s = new Segmento(i, j)                           ; //se crea nuevo segmento
    
  s->set_tiempo_i(tiempo) ; //se setea tiempo de inicio del segmento
  s->set_costo_i(costo)   ; //se setea costo de inicio del segmento
  s->set_tasa_i(tasa)     ; //se setea tasa al inicio del segmento

  p = tiempo / instancia->get_frec_salidas()                    ; //se identifica periodo de tiempo
  tiempo = tiempo + i->get_tiempo_hasta(j->get_id_cliente(), p) ; //se suma tiempo de viaje
  costo = costo + i->get_costo_hasta(j->get_id_cliente(), p)    ; //se suma costo de viaje
    
  s->set_tiempo_t(tiempo)   ; //se setea el tiempo al final del segmento
  s->set_costo_t(costo)     ; //se setea el costo al final del segmento
  s->set_tasa_t(tasa)       ; //se setea la tasa de fallo al final del segmento  
  s->set_demanda_t(demanda) ; //se setea la demanda cubierta al final del segmento 
  
  ruta->set_aporte_f1(costo)                  ; //se setea el aporte de la ruta a f1
  ruta->set_aporte_f2(tasa)                   ; //se setea el aporte de la ruta a f2
  ruta->set_tiempo_termino(tiempo)            ; //se setea el tiempo de termino de la ruta
  ruta->set_tiempo_restante(h_fin - tiempo)   ; //se setea el tiempo restante de la ruta
  ruta->set_capacidad_restante(cap - demanda) ; //se setea la capacidad disponible del camion

  ruta->agregar_segmento(s) ; //se agrega el segmento a la ruta

  return ruta ; //se retorna la ruta
}


//--------------- evaluacion de la ruta ---------------
bool OX::evaluar_ruta_desde(Instancia* instancia, Ruta* ruta, int desde){
  Segmento* i = ruta->get_segmento(desde) ;
  float h_fin = instancia->get_termino()  ; //termino de horizonte de planificacion
  float tiempo = i->get_tiempo_i()        ; //tiempo transcurrido
  int p                                   ; //periodo de tiempo

  for (int j=desde; j<ruta->get_segmentos().size(); j++){
    i = ruta->get_segmento(j) ; //se identifica el segmento a actualizar

    p = tiempo / instancia->get_frec_salidas()                                                      ; //periodo de tiempo
    tiempo = tiempo + i->get_cliente_i()->get_tiempo_hasta(i->get_cliente_j()->get_id_cliente(), p) ; //tiempo de viaje

    if (i->get_cliente_j() != instancia->get_cliente(instancia->get_cant_clientes())){
      p = tiempo / instancia->get_frec_salidas()               ; //se identifica periodo de tiempo
      tiempo = tiempo + i->get_cliente_j()->get_tiempo_aten(p) ; //se suma el tiempo de atencion
    }

    if (tiempo > h_fin){ return false ;} //si se supera el horizonte de panificacion de detiene el calculo
  }
  return true ; //retorna verdadero si el cambio es factible
}


//--------------- actualizacion de la ruta ---------------
bool OX::actualizar_ruta_desde(Instancia* instancia, Ruta* ruta, int desde){
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

    p = tiempo / instancia->get_frec_salidas()                                                      ; //periodo de tiempo
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


//--------------- se genera el hijo como un individuo ---------------
Individuo* OX::generar_individuo(Individuo* padre, vector <int> secuencia, Instancia* instancia){
  struct comparar_tiempos{                     //se crea estructura para ordenamiento
    bool operator()(Ruta* ruta1, Ruta* ruta2){ //se compara ruta-ruta
      //criterio de ordenamiento (de mayor a menor)
      return (ruta1->get_tiempo_inicio() + ruta1->get_tiempo_restante()) < (ruta2->get_tiempo_inicio() + ruta2->get_tiempo_restante()) ; 
    }
  } ;
  
  priority_queue<Ruta, vector<Ruta*>, comparar_tiempos> cola ; //cola de prioridad para rutas 
  Individuo* hijo = new Individuo()                          ; //se crea una nueva solucion
  Ruta* ruta                                                 ;

  bool bandera                               ; //bandera para detectar un cambio factible
  int h_inicio = instancia->get_inicio()*100 ; //limite inferior de la nueva hora
  int h_fin                                  ; //limite superior de la nueva hora
  float hora_inicio                          ; //hora de inicio aleatoria entre los limites
  int desde = 0                              ; //inicio de una ruta en la secuencia
  int hasta = 0                              ; //termino de una ruta en la secuencia
  int contar                                 ; //contador de intentos de ruta factible
  int q = 0                                  ; //ruta

  while (q < padre->get_rutas().size()){
    Ruta* k = padre->get_ruta(q)                 ; //se identifica ruta q
    hasta = hasta + k->get_segmentos().size() -1 ; //se identifica donde termina la ruta en la secuencia
    bandera = false                              ; //ruta factible inicialmente falsa
    hora_inicio = k->get_tiempo_inicio()         ; //hora de inicio igual a la hora de inicio original
    contar = 1                                   ; //primer intento de ruta factible

    bandera = this->evaluar_secuencia(instancia, secuencia, hora_inicio, desde, hasta)   ; //se evalua si la ruta es factible

    while (!bandera){                                                                      //mientras la ruta no sea factible
      contar++                                                                           ; //se pasa al siguiente intento
      h_fin = hora_inicio*100                                                            ; //se actualiza limite superior
      hora_inicio = (float)(rand()%(h_fin - h_inicio + 1) + h_inicio)/100                ; //se calcula nueva hora de inicio
      bandera = this->evaluar_secuencia(instancia, secuencia, hora_inicio, desde, hasta) ; //se evalua si la ruta es factible

      if (hora_inicio*100 == h_inicio && !bandera){   //si se llega al inicio del horizonte
        break                                       ; //se deja de ajusta la hora
      } else if (contar == 5){                        //si se realizan 5 intentos
        break                                       ; //se deja de ajusta la hora
      }
    }

    if (!bandera){                                //si aun no se encuentra una ruta factible
      hasta = hasta - k->get_segmentos().size() ; //se le quita un nodo a la ruta
      continue                                  ; //se reiniciar proceso de evaluacion de la ruta
    }

    ruta = this->armar_ruta(instancia, secuencia, hora_inicio, q, desde, hasta) ; //para una ruta factible se contruye la ruta

    hijo->set_f1(hijo->get_f1() + ruta->get_aporte_f1()) ; //se suma el aporte de la ruta a f1
    hijo->set_f2(hijo->get_f2() + ruta->get_aporte_f2()) ; //se suma el aporte de la ruta a f2
    hijo->agregar_ruta(ruta)                             ; //se agrega la ruta a la solucion

    cola.push(ruta) ; //se agrega la ruta a la cola de prioridad
    desde = hasta   ; //la siguiente ruta comienza donde termina la actual
    q++             ; //se pasa a la siguiente ruta
  }
  
  if (desde < secuencia.size()){ //si no se asignado todos los clientes a una ruta
    for (int h=desde; h<secuencia.size(); h++){
      ruta = cola.top() ; //se toma ruta potencial para insertar un cliente faltante
      cola.pop()        ; //se elimina la ruta de la cola de prioridad
      bandera = false   ; //inicialmente la ruta es infactible

      Cliente* i = instancia->get_cliente(secuencia.at(h))                ; //se identifica cliente i del nuevo segmento
      Cliente* j = instancia->get_cliente(instancia->get_cant_clientes()) ; //se identifica cliente j del nuevo segmento

      Segmento* s = ruta->get_segmento(ruta->get_segmentos().size()-1) ; //se identifica el ultimo segmento de la ruta
      s->set_cliente_j(i)                                              ; //se ajusta el cliente j
      s->set_demanda_t(s->get_demanda_t() +1)                          ; //se ajusta la demanda

      s = new Segmento(i, j)    ; //se crea un nuevo segmento
      ruta->agregar_segmento(s) ; //se agrega el segmento a la ruta

      bandera = this->evaluar_ruta_desde(instancia, ruta, ruta->get_segmentos().size() -2) ; //se evalua si la ruta es factible
      contar = 1                                                                           ; //primer intento de ruta factible 

      while (!bandera){ 
        contar++                                                            ; //se pasa al siguiente intento
        h_fin = ruta->get_tiempo_inicio()*100                               ; //se actualiza limite superior
        hora_inicio = (float)(rand()%(h_fin - h_inicio + 1) + h_inicio)/100 ; //se calcula nueva hora de inicio
        ruta->set_tiempo_inicio(hora_inicio)                                ; //se setea la hora de inicio a la ruta
        ruta->get_segmento(0)->set_tiempo_i(hora_inicio)                    ; //se setea la hora de inicio al primer segmento
        bandera = this->evaluar_ruta_desde(instancia, ruta, 0)              ; //se evalua si la ruta es factible desde el deposito

        if (contar == 5){                     //si se realizan 5 intentos
          delete hijo                       ; //se elimina el hijo
          return NULL                       ; //no se retorna una solucion (hijo)
        }
      }

      hijo->set_f1(hijo->get_f1() - ruta->get_aporte_f1()) ; //para una ruta factible se resta el aporte a f1
      hijo->set_f2(hijo->get_f2() - ruta->get_aporte_f2()) ; //para una ruta factible se resta el aporte a f2

      if (contar == 1){                                                                 //si se uso un intento
        this->actualizar_ruta_desde(instancia, ruta, ruta->get_segmentos().size() -2) ; //se actualiza desde la modificacion
      } else {                                                                          //si se cambio la hora
        this->actualizar_ruta_desde(instancia, ruta, 0)                               ; //se actualiza desde el inicio
      }

      hijo->set_f1(hijo->get_f1() + ruta->get_aporte_f1()) ; //para una ruta factible se suma el nuevo aporte a f1
      hijo->set_f2(hijo->get_f2() + ruta->get_aporte_f2()) ; //para una ruta factible se suma el nuevo aporte a f2

      cola.push(ruta) ; //se reinserta la ruta a la cola de prioridad
    }
  }
  
  return hijo ; //se retorna el hijo
}


//--------------- cruza dos padres generando dos hijos ---------------
vector <Individuo*>  OX::cruzar_individuos(Individuo* individuo1, Individuo* individuo2, Instancia* instancia, int cant_hijos){
  
  vector <int> padre1 = this->extraer_secuencia(individuo1) ; // se extrae la secuencia de cliente en un unico vector
  vector <int> padre2 = this->extraer_secuencia(individuo2) ; // se extrae la secuencia de cliente en un unico vector

  int corte2_p1 = rand()%(int(instancia->get_cant_clientes()*0.5) +1) ; //se identifica distancia entre cortes
  int corte2_p2 = rand()%(int(instancia->get_cant_clientes()*0.5) +1) ; //se identifica distancia entre cortes

  int corte1_p1 = rand()%(instancia->get_cant_clientes() - corte2_p1 -1) ; //se idetifica donde se hara el primer corte
  int corte1_p2 = rand()%(instancia->get_cant_clientes() - corte2_p2 -1) ; //se idetifica donde se hara el primer corte

  corte2_p1 = corte2_p1 + corte1_p1 ; //se idetifica donde se hara el segundo corte
  corte2_p2 = corte2_p2 + corte1_p2 ; //se idetifica donde se hara el segundo corte

  vector <Individuo*> hijos ; //vector para guardar los hijos creados

  if (hijos.size() < cant_hijos){
    vector <int> herencia_x1 = this->extraer_herencia_x(padre1, corte1_p1, corte2_p1)     ; //se extrae herencia de un padre
    vector <int> herencia_y1 = this->extraer_herencia_y(padre2, herencia_x1, corte2_p2)   ; //se estrae herencia del otro padre
    vector <int> hijo1 = this->crear_hijo(herencia_x1, herencia_y1, corte1_p1, corte2_p1) ; //se crea la secuencia del hijo
    Individuo* h1 = this->generar_individuo(individuo1, hijo1, instancia)                 ; //se convierte al hijo en individuo

    if (h1 != NULL){
      hijos.push_back(h1)                                                                 ; //se agrega el hijo al vector
    }
  }
  
  if (hijos.size() < cant_hijos){
    vector <int> herencia_x2 = this->extraer_herencia_x(padre2, corte1_p2, corte2_p2)     ; //se extrae herencia de un padre
    vector <int> herencia_y2 = this->extraer_herencia_y(padre1, herencia_x2, corte2_p1)   ; //se estrae herencia del otro padre
    vector <int> hijo2 = this->crear_hijo(herencia_x2, herencia_y2, corte1_p2, corte2_p2) ; //se crea la secuencia del hijo
    Individuo* h2 = this->generar_individuo(individuo2, hijo2, instancia)                 ; //se convierte al hijo en individuo

    if (h2 != NULL){
      hijos.push_back(h2)                                                                 ; //se agrega el hijo al vector
    }
  }

  return hijos ;
}





