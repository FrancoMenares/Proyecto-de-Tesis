
#include "t-ReRuteo.h"



Instancia* ReRuteo::crear_instancia_de_reruteo(Individuo* individuo, Instancia* instancia){

  Instancia* inst = new Instancia() ; //se crea una nueva instancia
  Cliente* cliente                  ; //se crea un puntero a cliente

  for (Ruta* r: individuo->get_rutas()){               //se recorren las rutas de la solucion
    for (int j=0; j<r->get_segmentos().size()-1; j++){ //se recorren los segmentos de la ruta
      Segmento* s = r->get_segmento(j) ;               //se idetifica el segmento

      float prob = (float)(rand()%(100 + 1))/100                ; //se genera probabilidad de fallo
      float tasa = int((s->get_tasa_t() - s->get_tasa_i())*100) ; //se calcula tasa de fallo
      tasa = float(tasa/100)                                    ; //se trunca
      
      if (prob < (tasa + 0.001)){
        cliente = new Cliente()                                 ; //se crea un nuevo cliente
        cliente->set_id_nodo(s->get_cliente_j()->get_id_nodo()) ; //se setea el id del nodo en la red
        cliente->set_id_cliente(inst->get_clientes().size())    ; //se setea el id de cliente en la instancia

        inst->agregar_cliente(cliente)                          ; //se agrega el nuevo cliente a la nueva instancia
      }
    }
  }
  cliente = new Cliente()                                                                     ; //se crea nuevo cliente para el deposito
  cliente->set_id_nodo(instancia->get_cliente(instancia->get_cant_clientes())->get_id_nodo()) ; //se setea el id del nodo en la red
  cliente->set_id_cliente(inst->get_clientes().size())                                        ; //se setea el id de cliente en la instancia
  inst->agregar_cliente(cliente)                                                              ; //se agrega el deposito a la instancia

  inst->set_cant_clientes(inst->get_clientes().size()-1)  ; //se setea la cantidad de clientes a rerutear
  inst->set_cant_camiones(instancia->get_cant_camiones()) ; //se setea la cantidad de camiones disponibles
  inst->set_cap_camiones(instancia->get_cap_camiones())   ; //se setea la capacidad de cada camion
  inst->set_inicio(instancia->get_inicio())               ; //se setea el inicio del horizonte de planificacion
  inst->set_termino(instancia->get_termino())             ; //se setea el termino del horizonte de planificacion
  inst->set_cant_salidas(instancia->get_cant_salidas())   ; //se setea la cantidad de salidas(periodos de tiempo)
  inst->set_frec_salidas(instancia->get_frec_salidas())   ; //se setea la duracion de cada periodo de tiempo

  
  //for (Cliente* p: inst->get_clientes()){
  //  p->imprimir_cliente();
  //}
  //instancia->imprimir_instancia() ;
  //inst->imprimir_instancia()      ;

  return inst ;
}
