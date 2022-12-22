/*
Ejercicio_3
*/
# Definición de las variables
var x1 >= 0;
var x2 >= 0;
var x3 >= 0;
var x4 >= 0;
# Función objetivo
minimize  z: + x1 - 3*x2 + 3*x3 - 4*x4;
# Restricciones
r1: 5*x2 + x3 + 5*x4 = 49;
r2: 2*x1 - x2 - 2*x4 = 15;
r3: x1 + 3*x2 + 4*x3 + 4*x4 = 81;
# Lo solucionamos y mostramos los resultados
solve;
display x1, x2, x3, x4;
end;