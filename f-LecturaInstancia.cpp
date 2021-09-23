
#include "f-LecturaInstancia.h"


Instancia *LecturaInstancia::lectura_instancia(void){
  Instancia *problema = new Instancia()                ; //se crea una Instancia
  this->fs = fstream( this->nombre_instancia)          ; //Ejecuta la lectura para la variable fs

  if ( ! this->fs ){                                     //Si la dirección está vacía, tira error 
		cerr << "No se puede abrir archivo: "<< this->nombre_instancia << endl;
		exit(0)                                            ;
	}

  string linea                                         ; //Se crea una línea de tipo string 
  
  
  //-------------- cant clientes --------------
  getline(this->fs,linea)                              ; //Se obtiene la primera linea 
  problema->set_cant_clientes(atoi(linea.c_str()));
  
  
  //-------------- clientes --------------
  for (int i=0; i<problema->get_cant_clientes(); i++){
    this->fs >> this->cadena                           ; //Se lee el id de nodo de cada cliente
    Cliente* temp = new Cliente()                      ; //Se crea un cliente temporal
    temp->set_id_cliente(i)                            ; //Se setea el id de cliente
    temp->set_id_nodo(atoi(cadena.c_str())-1)          ; //Se setea el id de nodo
    problema->agregar_cliente(temp)                    ; //Se agrega al vector de clientes de la instancia 
  }
  getline(this->fs,linea)                              ; //Se deja de leer la linea
  
  
  //-------------- deposito --------------
  getline(this->fs,linea)                              ; //Se obtiene la nueva linea 
  Cliente* temp = new Cliente()                        ; //Se crea un nodo temporal
  temp->set_id_cliente(problema->get_cant_clientes())  ; //Se setea el numero de cliente
  temp->set_id_nodo(atoi(linea.c_str())-1)             ; //Se setea el numero de nodo
  problema->agregar_cliente(temp)                      ; //se agrega el deposito al final de la lista de clientes
  
  
  //-------------- cant camiones --------------
  getline(this->fs,linea)                              ; //Se obtiene la nueva linea 
  problema->set_cant_camiones(atoi(linea.c_str()))     ; //Se setea la cantidad de camiones


  //-------------- cap camiones --------------
  getline(this->fs,linea)                              ; //Se obtiene la linea 
  problema->set_cap_camiones(atoi(linea.c_str()))      ; //Se setea la capacidad de los camiones


  //-------------- inicio horizonte --------------
  getline(this->fs,linea)                              ; //Se obtiene la linea 
  problema->set_inicio(atof(linea.c_str()))            ; //Se setea el inicio del horizonte de planificacion


  //-------------- termino horizonte --------------
  getline(this->fs,linea)                              ; //Se obtiene la linea 
  problema->set_termino(atof(linea.c_str()))           ; //Se setea el termino del horizonte de planificacion


  //-------------- retorno de la la lectura --------------
  return problema                                      ;
}


