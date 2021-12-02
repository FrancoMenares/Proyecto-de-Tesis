#!/bin/bash

Red="Red-Carreteras/Red-Carreteras-3.txt"
dir1="Instancias/InstanciasChicas"
dir2="Instancias/InstanciasGrandes"

Instancias_chicas="a-Instancia7.txt"
Instancias_grandes="e-Instancia50.txt"

#Instancias_chicas=$(ls ${dir1})
#Instancias_grandes=$(ls ${dir2})

#Semillas="624 472 685 103 328 467 432 191 779 510"
Semillas="624"

Frec_salidas_chicas="60.0"
Frec_salidas_grandes="15.0"

Lambda="200"
P_aceptacion="80"
P_cruce="90"
P_mutacion="90"
Generaciones="100000"

dir3="Resultados"
FrentesM="FrentesModelo"
FrentesA="FrentesAlgoritmo"
FrentesG="FrentesGrafico"
Hiper="HiperVolumen"
RutasA="RutasAlgoritmo"
SolucionesA="SolucionesAlgoritmo"
TiemposA="TiemposAlgoritmo"

FrentesRE="FrentesReRuteo"
SolucionesRE="SolucionesReRuteo"


make


for instancia in ${Instancias_chicas}; do

  mkdir -p ${dir3}/${FrentesA}/${instancia:0:-4}
  mkdir -p ${dir3}/${RutasA}/${instancia:0:-4}
  mkdir -p ${dir3}/${SolucionesA}/${instancia:0:-4}

  mkdir -p ${dir3}/${FrentesRE}/${instancia:0:-4}
  mkdir -p ${dir3}/${SolucionesRE}/${instancia:0:-4}

  rm ${dir3}/${TiemposA}/${instancia}

  for frec_salidas in ${Frec_salidas_chicas}; do
    for semilla in ${Semillas}; do
      for lambda in ${Lambda}; do
        for p_aceptacion in ${P_aceptacion}; do
          for p_cruce in ${P_cruce}; do
            for p_mutacion in ${P_mutacion}; do
              for generaciones in ${Generaciones}; do

                ./ProyectoTesis ${Red} ${dir1}/${instancia} ${frec_salidas} ${semilla} ${lambda} ${p_aceptacion} ${p_cruce} ${p_mutacion} ${generaciones} >> ${dir3}/${TiemposA}/${instancia}

              done
            done
          done
        done
      done
    done
  done
done


for instancia in ${Instancias_grandes}; do

  mkdir -p ${dir3}/${FrentesA}/${instancia:0:-4}
  mkdir -p ${dir3}/${RutasA}/${instancia:0:-4}
  mkdir -p ${dir3}/${SolucionesA}/${instancia:0:-4}

  mkdir -p ${dir3}/${FrentesRE}/${instancia:0:-4}
  mkdir -p ${dir3}/${SolucionesRE}/${instancia:0:-4}

  rm ${dir3}/${TiemposA}/${instancia}

  for frec_salidas in ${Frec_salidas_grandes}; do
    for semilla in ${Semillas}; do
      for lambda in ${Lambda}; do
        for p_aceptacion in ${P_aceptacion}; do
          for p_cruce in ${P_cruce}; do
            for p_mutacion in ${P_mutacion}; do
              for generaciones in ${Generaciones}; do
              
                ./ProyectoTesis ${Red} ${dir2}/${instancia} ${frec_salidas} ${semilla} ${lambda} ${p_aceptacion} ${p_cruce} ${p_mutacion} ${generaciones} >> ${dir3}/${TiemposA}/${instancia}

              done
            done
          done
        done
      done
    done
  done
done






#a-Instancia1.txt a-Instancia2.txt a-Instancia3.txt a-Instancia4.txt a-Instancia5.txt a-Instancia6.txt a-Instancia7.txt a-Instancia8.txt a-Instancia9.txt a-Instancia10.txt b-Instancia11.txt b-Instancia12.txt b-Instancia13.txt b-Instancia14.txt b-Instancia15.txt b-Instancia16.txt b-Instancia17.txt b-Instancia18.txt b-Instancia19.txt b-Instancia20.txt c-Instancia21.txt c-Instancia22.txt c-Instancia23.txt c-Instancia24.txt c-Instancia25.txt c-Instancia26.txt c-Instancia27.txt c-Instancia28.txt c-Instancia29.txt c-Instancia30.txt d-Instancia31.txt d-Instancia32.txt d-Instancia33.txt d-Instancia34.txt d-Instancia35.txt d-Instancia36.txt d-Instancia37.txt d-Instancia38.txt d-Instancia39.txt d-Instancia40.txt e-Instancia41.txt e-Instancia42.txt e-Instancia43.txt e-Instancia44.txt e-Instancia45.txt e-Instancia46.txt e-Instancia47.txt e-Instancia48.txt e-Instancia49.txt e-Instancia50.txt