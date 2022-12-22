/*
 *  PG3.CPP - Actividad III de Optimiza!cion.
 *
 *
 *               Autores : Antonio Sedeno Noda, Sergio Alonso.
 *               Fecha : Marzo-2020
 * Compilar con g++ -g grafo_.cpp pg3_.cpp -o (nombre)
 */

#include <string.h>
#include "grafo.h"
#define PAUSE system("pause")

using namespace std;

void clrscr() //No funciona en todos los sistemas: opcional
{
    system("cls");
}

void menu(unsigned dirigido, char &opcion)
//Expresion del menu de opciones segun sea un grafo dirigido o no dirigido
{
    //Cumplimentar por alumnado según pantallas de opciones en el guión u otras equivalentes

    cout << "Actividad III, Optimiza!cion: el arbol generador de minimo coste, Kruskal" << endl;
    cout << "c. [c]argar grado desde fichero" << endl;
    cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
    if (dirigido == 1)
    {
        cout << "s. Mostrar la lista de [s]ucesores del grafo" << endl;
        cout << "p. Mostrar la lista de [p]redecesores del grafo" << endl;
        cout << "d. Caminos minimos: [d]ijkstra" << endl;
        cout << "b. Caminos minimos: [b]ellman-Ford-Moore." << endl;
    }
    if (dirigido == 0)
    {
        cout << "a. Mostrar la lista de [a]dyacencia del grafo" << endl;
        cout << "o. Mostrar c[o]mponentes conexas del grafo" << endl;
        cout << "k. Mostral arbol generador minimo coste, [k]ruskal" << endl;
    }
    cout << "q. Finalizar el programa" << endl;
    cout << "Introduce la letra de la accion a ejecutar > ";
    cin >> opcion;
    clrscr();
    cout << endl;
}

// El principal es simplemente un gestor de menu, diferenciando acciones para grafo dirigido y para no dirigido
int main(int argc, char *argv[])
{
    int error_apertura;
    char nombrefichero[85], opcion;

    clrscr();
    //Cargamos por defecto el fichero que se pasa como argumento del ejecutable
    if (argc > 1)
    {
        cout << "Cargando datos desde el fichero dado como argumento" << endl;
        strcpy(nombrefichero, argv[1]);
    }
    else
    {
        cout << "Introduce el nombre completo del fichero de datos" << endl;
        cin >> nombrefichero;
        clrscr();
    }
    GRAFO G(nombrefichero, error_apertura);
    if (error_apertura == 1)
    {
        cout << "Error en la apertura del fichero: revisa nombre y formato" << endl;
    }
    else
    {
        do
        {
            menu(G.Es_dirigido(), opcion);
            int l;
            switch (opcion)
            {
            //Situar aquí el código de gestión de las opciones, según sea el grafo dirigido o no dirigido
            case 'c':
                cout << "Introduce el nombre del nuevo fichero: ";
                cin >> nombrefichero;
                G.actualizar(nombrefichero, error_apertura);
                break;
            case 'i':
                G.Info_Grafo();
                break;
                if (G.Es_dirigido() == 1)
                {
                case 's':
                    l = 1;
                    G.Mostrar_Listas(l);
                    break;
                case 'p':
                    l = -1;
                    G.Mostrar_Listas(l);
                    break;
                case 'd':
                    G.Dijkstra();
                    break;
                case 'b':
                    G.BellmanEndFord();
                    break;
                }
                if (G.Es_dirigido() == 0)
                {
                case 'a':
                    l = 0;
                    G.Mostrar_Listas(l);
                    break;
                case 'o':
                    G.ComponentesConexas();
                    break;
                case 'k':
                    G.Kruskal();
                    break;
                case 'q':
                    break;
                }
            default:
                cout << "Opcion no encontrada. Intentalo de nuevo" << endl
                     << endl;
            }
            PAUSE;
            clrscr();
        } while (opcion != 'q');
    }
    cout << "Fin del programa";
    cout << endl;
    return (0);
}
