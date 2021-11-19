#!/bin/bash


dir3="Resultados"
FrentesM="FrentesModelo"
FrentesA="FrentesAlgoritmo"
FrentesG="FrentesGrafico"
Hiper="HiperVolumen"
RutasA="RutasAlgoritmo"
SolucionesA="SolucionesAlgoritmo"
TiemposA="TiemposAlgoritmo"

Frente="Frente.txt"
Individuos="Individuos.txt"
Punto="PuntoRef.txt"
Rutas="Rutas.txt"
Seguimiento="Seguimiento.txt"


rm -r rm ${dir3}/${FrentesA}/* ${dir3}/${FrentesG}/* ${dir3}/${Hiper}/* ${dir3}/${RutasA}/* ${dir3}/${SolucionesA}/* ${dir3}/${TiemposA}/* 
rm ${dir3}/${Frente} ${dir3}/${Individuos} ${dir3}/${Punto} ${dir3}/${Rutas} ${dir3}/${Seguimiento} nohup.out
clear