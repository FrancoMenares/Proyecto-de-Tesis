
dir="Instancias"



Red="Red-Carreteras-3.txt"
Instancias="a-Instancia1.txt a-Instancia2.txt"
#Instancias="a-Instancia1.txt a-Instancia2.txt a-Instancia3.txt a-Instancia4.txt a-Instancia5.txt a-Instancia6.txt a-Instancia7.txt a-Instancia8.txt a-Instancia9.txt a-Instancia10.txt b-Instancia11.txt b-Instancia12.txt b-Instancia13.txt b-Instancia14.txt b-Instancia15.txt b-Instancia16.txt b-Instancia17.txt b-Instancia18.txt b-Instancia19.txt b-Instancia20.txt c-Instancia21.txt c-Instancia22.txt c-Instancia23.txt c-Instancia24.txt c-Instancia25.txt c-Instancia26.txt c-Instancia27.txt c-Instancia28.txt c-Instancia29.txt c-Instancia30.txt d-Instancia31.txt d-Instancia32.txt d-Instancia33.txt d-Instancia34.txt d-Instancia35.txt d-Instancia36.txt d-Instancia37.txt d-Instancia38.txt d-Instancia39.txt d-Instancia40.txt e-Instancia41.txt e-Instancia42.txt e-Instancia43.txt e-Instancia44.txt e-Instancia45.txt e-Instancia46.txt e-Instancia47.txt e-Instancia48.txt e-Instancia49.txt e-Instancia50.txt"
Semillas="624 472 685 103 328 467 432 191 779 510"
frec_salidas="60.0"
lambda="50"
p_aceptacion="90"
p_cruce="90"
p_mutacion="90"
generaciones="10000"



for instancia in ${Instancias}; do
  echo "Ejecutando instancia: ${instancia}" 
done