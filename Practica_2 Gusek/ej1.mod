/*
Ej1.mod: Primer progama
*/

#definici�n de variables
var x1 >= 0, integer;
var x2 >= 0;
var x3 >= 0;

#funci�n objetivo
minimize z: 4*x1 - 2*x2 + 2*x3;
#restricciones
r1: 6*x2 + x3 = 4;
r2: x1 - x2 =2;

#lo resovemos y mostramos los resultados
solve;
display x1, x2, x3;
end;