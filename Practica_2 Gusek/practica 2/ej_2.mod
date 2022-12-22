/*
Ejercicio_2
*/
# Definición de las variables
var x1 >= 0, integer;
var x2 >= 0;
var x3 >= 0;
# Función objetivo
minimize z: -3*x1 + 2*x2 - x3;
# Restricciones
r1: 2*x1 + x2 - x3 = 8;
r2: -2*x1 + 2*x2 + x3 = 6;
# Lo solucionamos y mostramos los resultados
solve;
display x1, x2, x3;
end;