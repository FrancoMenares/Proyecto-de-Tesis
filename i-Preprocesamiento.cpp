
#include "i-Preprocesamiento.h"


//--------------- preprocesamiento ---------------
void Preprocesamiento::preprocesar_red(Red* red, Instancia* instancia, float frecuencia){
  bool debug = false                                                                  ;
  int ruta                                                                            ;

  clock_t t_inicial = clock()                                                         ;
  
  //------------- calculo costos y tiempos de viaje -------------
  TDDijkstra* rutas = new TDDijkstra()                                                ; //se crea un objeto de tipo TDDijkstra
  Costos* costos = new Costos()                                                       ; //se crea un objeto de tipo Costos

  int cant_salidas = red->get_fin_periodo(red->get_cant_periodos()-1) / frecuencia    ; //se calculan las salidas del preprocesamiento
  instancia->set_cant_salidas(cant_salidas)                                           ; //se setea la cantidad de salidas en la instancia

  if (debug) { ruta=0; }

  for (Cliente* aux1: instancia->get_clientes()){                                       //para cada nodo
    aux1->set_tam_costo_hasta(instancia->get_cant_clientes()+1, cant_salidas)         ; //se setea el tamaño de la matriz de costos
    aux1->set_tam_tiempo_hasta(instancia->get_cant_clientes()+1, cant_salidas)        ; //se setea el tamaño de la matriz de tiempo

    for (int salida=0; salida<cant_salidas; salida++){                                  //para cada salida
      float hora_inicio = salida*frecuencia                                           ; //se calcula la hora de inicio de la salida
      rutas->td_ruta_mas_corta(red, costos, aux1->get_id_nodo(), hora_inicio)         ; //se calculan todas las rutas desde cada cliente

      for (Cliente* aux2: instancia->get_clientes()){                                                                          //para cada cliente
        aux1->set_costo_hasta(aux2->get_id_cliente(), salida, red->get_nodo(aux2->get_id_nodo())->get_costo())               ; //se setea costo viaje
        aux1->set_tiempo_hasta(aux2->get_id_cliente(), salida, red->get_nodo(aux2->get_id_nodo())->get_tiempo()-hora_inicio) ; //se setea tiempo viaje
        
        if (debug) {
          rutas->imprimir_ruta(red, aux1->get_id_nodo(), aux2->get_id_nodo(), ruta)   ;
          ruta++                                                                      ;
        }
      }
      red->reiniciar_nodos() ; //se reinician los nodos de la red de carreteras a su estado original
    }
  }

  //------------- calculo costos de atencion -------------
  for (int i=0; i<instancia->get_cant_clientes(); i++){
    for (int j=0; j<red->get_cant_periodos(); j++){
      float tiempo = red->get_tiempo_aten(instancia->get_cliente(i)->get_id_nodo(), j)/60 ; //se identifica tiempo de atencion
      instancia->get_cliente(i)->agregar_tiempo_aten(tiempo)                              ; //se setea tiempo de atencion
      instancia->get_cliente(i)->agregar_costo_aten(costos->costo_total_nodo(tiempo))     ; //se calcula y setea costo de atencion
      
      float tasa = red->get_tasa_fallo(instancia->get_cliente(i)->get_id_nodo(), j)       ; //se identifica tasa fallo
      instancia->get_cliente(i)->agregar_tasas_fallo(tasa)                                ; //se setea tasa de fallo
    }
  }

  this->tiempo_ejecucion = difftime(clock(), t_inicial)/CLOCKS_PER_SEC  ; //se setea el tiempo de ejecucion
  instancia->set_frec_salidas(frecuencia)                               ; //se setea la frecuencia de salida
}


//--------------- impresiones ---------------
void Preprocesamiento::imprimir_tiempo_ejecucion(void){
  cout << "================================================================================" << endl ;
  cout << "Tiempo Preprocesamiento: " << this->tiempo_ejecucion                                      ;
  cout << " seg." << endl                                                                            ;
  cout << "================================================================================" << endl ;
  cout << endl                                                                                       ;
}



