
#include <math.h>

#include "7-Costos.h"


Costos::Costos(){
  this->valorC  = 501.0    ;  
  this->rend    = 3.18     ; 
  this->sueldoC = 598000.0 ;   
  this->diasC   = 24.0     ;    
  this->horasC  = 9.0      ;   
  this->valorN  = 112700.0 ;   
  this->vidaUN  = 45000.0  ;   
  this->cantN   = 4.0      ;   
  this->valorCA = 59900.0  ;   
  this->distCA  = 10000.0  ;   
}

float Costos::get_valorC(void)  { return this->valorC  ;} 
float Costos::get_rend(void)    { return this->rend    ;} 
float Costos::get_sueldoC(void) { return this->sueldoC ;} 
float Costos::get_diasC(void)   { return this->diasC   ;}  
float Costos::get_horasC(void)  { return this->horasC  ;} 
float Costos::get_valorN(void)  { return this->valorN  ;} 
float Costos::get_vidaUN(void)  { return this->vidaUN  ;}  
float Costos::get_cantN(void)   { return this->cantN   ;} 
float Costos::get_valorCA(void) { return this->valorCA ;} 
float Costos::get_distCA(void)  { return this->distCA  ;} 

//------------- costos nodo -------------
float Costos::costo_combustible_nodo(float tiemp){
  return this->rend * tiemp * this->valorC                                           ;
}

float Costos::costo_conductor_nodo(float tiemp){
  return (this->sueldoC/(this->diasC * this->horasC)) * tiemp                        ;
}

float Costos::costo_total_nodo(float tiemp){
  return this->costo_combustible_nodo(tiemp) + this->costo_conductor_nodo(tiemp)     ;
}

//------------- costos arco -------------
float Costos::costo_combustible_arco(float vel, float dist){
  if (vel <= 47){
    return ((1425.2 * pow(vel,-0.7593))/850) * dist * this->valorC                   ;
  } 
  else{
    return (( 0.0082 * pow(vel,2) - 0.043 * vel + 60.12 )/850) * dist * this->valorC ;
  }
}

float Costos::costo_conductor_arco(float tiemp){
  return (this->sueldoC/(this->diasC * this->horasC)) * tiemp                        ;
}

float Costos::costo_desgaste_neumatico(float dist){
  return (this->valorN/this->vidaUN) * this->cantN * dist                            ;
}

float Costos::costo_cambio_aceite(float dist){
  return (this->valorCA/this->distCA) * dist                                         ;
}

float Costos::costo_total_arco(float vel, float dist, float tiemp){
  return this->costo_combustible_arco(vel, dist) + this->costo_conductor_arco(tiemp) + this->costo_desgaste_neumatico(dist) + this->costo_cambio_aceite(dist) ;
}

//------------- impresiones -------------
void Costos::imprimir_detalle_costos(void){
  cout << "Precio Combustible      : \t" << this->valorC  << endl ;  
  cout << "Consumo Ralenti         : \t" << this->rend    << endl ; 
  cout << "Sueldo Conductor        : \t" << this->sueldoC << endl ;   
  cout << "Dias Trabajo Mes        : \t" << this->diasC   << endl ;    
  cout << "Horas Trabajo Dia       : \t" << this->horasC  << endl ;   
  cout << "Precio Neumatico        : \t" << this->valorN  << endl ;   
  cout << "Vida Util Nuematico     : \t" << this->vidaUN  << endl ;   
  cout << "Cantidad Neumaticos     : \t" << this->cantN   << endl ;   
  cout << "Precio Cambio Aceite    : \t" << this->valorCA << endl ;   
  cout << "Distancia Cambio Aceite : \t" << this->distCA  << endl ; 
  cout << endl                                                    ;
}

void Costos::imprimir_costos_nodo(float tiemp){
  cout << "Consumo Combustible : \t" << this->costo_combustible_nodo(tiemp)      << endl ;     
  cout << "Tiempo Conductor    : \t" << this->costo_conductor_nodo(tiemp)        << endl ;
  cout << "Total               : \t" << this->costo_total_nodo(tiemp)            << endl ; 
  cout << endl                                                                           ;
}

void Costos::imprimir_costos_arco(float vel, float dist, float tiemp){
  cout << "Consumo Combustible : \t" << this->costo_combustible_arco(vel, dist)  << endl ;     
  cout << "Tiempo Conductor    : \t" << this->costo_conductor_arco(tiemp)        << endl ; 
  cout << "Desgaste Nuematicos : \t" << this->costo_desgaste_neumatico(dist)     << endl ;     
  cout << "Cambio Aceite       : \t" << this->costo_cambio_aceite(dist)          << endl ; 
  cout << "Total               : \t" << this->costo_total_arco(vel, dist, tiemp) << endl ;  
  cout << endl                                                                           ;
}

