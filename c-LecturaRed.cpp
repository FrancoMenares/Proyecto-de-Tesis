
#include "c-LecturaRed.h"


Red *LecturaRed::lectura_red(){
  Red *grafo = new Red()                        ; //se crea una red
  this->fs = fstream( this->nombre_red)         ; //Ejecuta la lectura para la variable fs

  if ( ! this->fs ){                              //Si la dirección está vacía, tira error 
		cerr << "No se puede abrir el archivo: "<< this->nombre_red << endl;
		exit(0)                                     ;
	}

	string linea                                  ; //Se crea una línea de tipo string 
  
  //-------------- cant nodos --------------
  getline(this->fs,linea)                       ; //Se obtiene la primera linea 
  grafo->set_cant_nodos(atoi(linea.c_str()))    ; //Se setea la cantidad de nodos
  
  //-------------- cant arcos --------------
  getline(this->fs,linea)                       ; //Se obtiene la nueva linea 
  grafo->set_cant_arcos(atoi(linea.c_str()))    ; //Se setea la cantidad de arcos

  //-------------- cant periodos --------------
  getline(this->fs,linea)                       ; //Se obtiene la nueva linea 
  grafo->set_cant_periodos(atoi(linea.c_str())) ; //Se setea la cantidad de periodos

  //-------------- nodos --------------
  for (int i=0; i<grafo->get_cant_nodos(); i++){  //Se crea un objeto nodo para cada nodo de la red
    Nodo * temp = new Nodo()                    ; //se crea un nodo temporal
    temp->set_id(i)                             ; //se setea el id
    temp->set_costo(0)                          ; //se setea el costo
    temp->set_tiempo(0)                         ; //setea el tiempo
    temp->set_padre(0)                          ; //setea el padre
    grafo->agregar_nodo(temp)                   ; //Se agrega a la lista de nodos de la red
  }

  //-------------- Matriz de adyacencia --------------
  grafo->agregar_fils(grafo->get_cant_nodos())            ; //Se hace espacio para los nodos en la matriz de adyacencia
  for (int i=0; i<grafo->get_cant_nodos(); i++){            //Se secorre la matriz de adyacencia
    this->fs >> this->cadena                              ; //Se lee la cantidad de nodos adayacentes de cada nodo
    grafo->agregar_cols(i, 2+atoi(cadena.c_str())*(grafo->get_cant_periodos()+2) ); //Se hace espacio para la información de cada nodo adayacente
    grafo->set_matriz_ady(i, 0, float(i))                 ; //Se agrega un nodo
    grafo->set_matriz_ady(i, 1, atof(cadena.c_str()))     ; //Se agrega la cantidad de nodos adyacentes
  }
  
  int h1 = 0                                              ; //Contador de arcos a la que se ha guardado su información
  while (h1<grafo->get_cant_arcos()){
    this->fs >> this->cadena                              ; //Se realiza lectura por cadena de texto encontrada
    int i = atoi(cadena.c_str()) - 1                      ; //Se identifica el nodo al cual se setean sus adyacentes
    for (int j=0; j<grafo->get_matriz_ady(i, 1); j++){      //Se repite el proceso para cada nodo adyecente
      if (j>0){                                             //Se evita que se agregue el nodo seteado otra vez
        this->fs >> this->cadena                          ; //se lee la nueva linea
      }
      int amplitud = grafo->get_cant_periodos()+2         ; //Se identifica frecuencia con la que se agrega un nuevo nodo adyacente
      int h2 = j*amplitud;                                  //Se idientifica la posicion donde se agrega el nodo adyacente o su inforcion
      while (h2 < (grafo->get_cant_periodos()+2)*(j+1)){    //Se agrega la información del nodo adyacente
        this->fs >> this->cadena                          ; //se lee la nueva linea
        float aux = atof(cadena.c_str())                  ;
        if (h2 == j*amplitud){                              //cuando se encuentra un nuevo nodo adyacente se ajusta su posicion/id
          aux--                                           ;
        }
        grafo->set_matriz_ady(i, h2+2, aux)               ; //se agrega informacion en la matriz de adyacencia
        h2++                                              ;
      }
      h1++                                                ;
    }
  }
  
  //-------------- Tasas Fallo --------------
  grafo->set_tam_tasas_fallo(grafo->get_cant_nodos(), grafo->get_cant_periodos()) ; //Se crea matriz para guarda tasas de fallo
  for (int i=0; i<grafo->get_cant_nodos(); i++){                                    //Se recorre cada nodo
    for (int j=0; j<grafo->get_cant_periodos(); j++){                               //Se recorre cada periodo de tiempo
      this->fs >> this->cadena                                                    ; //se lee la nueva linea
      grafo->set_tasa_fallo(i, j, atof(cadena.c_str()))                           ; //Se agrega la tasa a la matriz
    }
  }

  //-------------- limites periodos --------------
  grafo->set_tam_periodos(grafo->get_cant_periodos()) ; //Se crea matriz para guardar los limites de cada periodo
  for (int i=0; i<grafo->get_cant_periodos(); i++){
    this->fs >> this->cadena                          ; //se lee la nueva linea
    grafo->set_periodo(i, 1, atof(cadena.c_str()))    ; //se setea el limite inferior
  }

  for (int i=0; i<grafo->get_cant_periodos(); i++){
    this->fs >> this->cadena                          ; //se lee la nueva linea
    grafo->set_periodo(i, 2, atof(cadena.c_str()))    ; //se seta el limite superior
  }
  
  //-------------- Tiempos atencion nodos --------------
  grafo->set_tam_tiempos_aten(grafo->get_cant_nodos(), grafo->get_cant_periodos()) ; //Se crea matriz para guardar tiempos de atencion
  for (int i=0; i<grafo->get_cant_nodos(); i++){                                     //Se recorre cada nodo
    for (int j=0; j<grafo->get_cant_periodos(); j++){                                //Se recorre cada periodo de tiempo
      this->fs >> this->cadena                                                     ; //se lee la nueva linea
      grafo->set_tiempo_aten(i, j, atof(cadena.c_str()))                           ; //Se agrega el tiempo a la matriz
    }
  }

  //-------------- retorno de la la lectura --------------
  return grafo                                        ;
}



