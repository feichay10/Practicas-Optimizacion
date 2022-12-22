/* Transportation Problem */

#Parámetros del problema:

param m, integer, > 0;  # número de almacenes

param n, integer, > 0;  # número de clientes

set I := 1..m; # conjunto de almacenes

set J := 1..n; # conjunto de clientes

param a{i in I}, >= 0; #suministro de los almacenes

param b{j in J}, >= 0; #demanda de los clientes

param c{i in I, j in J}, >= 0; # costo de transportar una unidad de producto del almacén i al cliente j


#Variables:

var x{i in I, j in J}, >= 0; # x[i,j] = cantidad de producto que se transporta desde el almacén i al cleitnes j
                           
# var x{i in I, j in J}, >= 0, <= 30;                           
 
#Modelo:

minimize obj: sum{i in I, j in J} c[i,j] * x[i,j];

s.t. suministro{i in I}: sum{j in J} x[i,j] <= a[i];
s.t. demanda{j in J}: sum{i in I} x[i,j] >= b[j];
/* The demand of destination j is b[j]  */

#Resolvemos el model y mostramos los resultados:

solve;

printf "\n";
printf "El coste total de transporte es %d\n",
   sum{i in I, j in J} c[i,j] * x[i,j];
printf "\n";
printf "Origin Destination Trans. Cost/u.   Total\n";
printf{i in I, j in J: x[i,j] > 0} "%6d %11d %6g %7g %7g\n", i, j, x[i,j], c[i,j], x[i,j] * c[i,j] ;
printf "-----------------------------------------\n";
printf "Total:                         %10g\n", sum{i in I, j in J} c[i,j] * x[i,j];
printf "\n";

data;

/* These data correspond to an example from [Christofides]. */

/* Optimal solution is 76 */

param m := 8;

param n := 8;

param a := 
      1  8
      2  5
      3  2
      4  9  
      5  3
      6  3
      7  3
      8  3;

param b :=
      1  4
      2  4
      3  4
      4  4  
      5  4
      6  4
      7  4
      8  8;

param c : 1  2  3  4  5  6  7  8 :=
      1  13 21 20 12  8 26 22 11
      2  12 36 25 41 40 11  4  8
      3  35 32 13 36 26 21 13 37
      4  34 54  7  8 12 22 11 40
      5  21  6 45 18 24 34 12 48
      6  42 19 39 15 14 16 28 46
      7  16 34 38  3 34 40 22 24
      8  26 20  5 17 45 31 37 43 ;

end;
