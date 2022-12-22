#Ej2.mod

#definimos los parámetros
param c{1..3};
param A{1..2,1..3};
param b{1..2};

#definimos las variables
var x{1..3}, >= 0;

#función objetivo
minimize z: sum{j in 1..3} c[j]*x[j];

#restriciones:
s.t. retric{i in 1..2}: sum{j in 1..3} A[i,j] * x[j] = b[i];


#los resolvemos y mostramos
solve;
display x;

#propocionamos los parámetros del problema
data;
param c:= 
1 4
2 -2
3 2;
param A:
  1  2 3 :=
1 0  6 1
2 1 -1 0;
param b:=
1 4
2 2;
end;