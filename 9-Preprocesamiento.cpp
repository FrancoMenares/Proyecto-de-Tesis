
#include "9-Preprocesamiento.h"


void Preprocesamiento::preprocesar_red(Red* red, Instancia* instancia, float frecuencia){
  //------------- calculo costos y tiempos de viaje -------------
  TDDijkstra* rutas = new TDDijkstra()                                                ; //se crea un objeto de tipo TDDijkstra
  Costos* costos = new Costos()                                                       ; //se crea un objeto de tipo Costos

  int cant_salidas = red->get_fin_periodo(red->get_cant_periodos()-1) / frecuencia    ; //se calculan las salidas del preprocesamiento
  instancia->set_cant_salidas(cant_salidas)                                           ; //se setea la cantidad de salidas en la instancia

  for (Cliente* aux1: instancia->get_clientes()){                                       //para cada nodo
    aux1->set_tam_costo_hasta(instancia->get_cant_clientes()+1, cant_salidas)         ; //se setea el tamaño de la matriz de costos
    aux1->set_tam_tiempo_hasta(instancia->get_cant_clientes()+1, cant_salidas)        ; //se setea el tamaño de la matriz de tiempo

    for (int salida=0; salida<cant_salidas; salida++){                                  //para cada salida
      float hora_inicio = salida*frecuencia                                           ; //se calcula la hora de inicio de la salida
      rutas->ruta_mas_corta(red, instancia, costos, aux1->get_id_nodo(), hora_inicio) ; //se calculan todas las rutas desde cada cliente

      for (Cliente* aux2: instancia->get_clientes()){                                                                          //para cada cliente
        aux1->set_costo_hasta(aux2->get_id_cliente(), salida, red->get_nodo(aux2->get_id_nodo())->get_costo())               ; //se setea costo viaje
        aux1->set_tiempo_hasta(aux2->get_id_cliente(), salida, red->get_nodo(aux2->get_id_nodo())->get_tiempo()-hora_inicio) ; //se setea tiempo viaje
        //cout << red->get_nodo(aux2->get_id_nodo())->get_tiempo()-hora_inicio << " " ;
        //cout << red->get_nodo(aux2->get_id_nodo())->get_costo() << " "              ;
      }
      red->reiniciar_nodos() ; //se reinician los nodos de la red de carreteras a su estado original
    }
  }

  //------------- calculo costos de atencion -------------
  red->set_tam_costos_aten(red->get_cant_nodos(), red->get_cant_periodos())           ; 
  for (int i=0; i<red->get_cant_nodos(); i++){
    for (int j=0; j<red->get_cant_periodos(); j++){
      red->set_costo_aten(i, j, costos->costo_total_nodo(red->get_tiempo_aten(i, j))) ;
    }
  }
}






